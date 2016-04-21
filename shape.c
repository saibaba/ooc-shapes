#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "shape.h"

static char * _get_name(Shape *this)
{
  return this->name;
}

static void _free(Shape *this)
{
  printf("Shape free called");
  free(this);
}

static void _dtor(Shape *this)
{
  printf("Shape dtor called\n");
}

static Shape_Vtable Global_Shape_Vtable;

void Shape_init(Shape_Vtable *p_shape_vtable)
{ 
  p_shape_vtable->p_dtor = _dtor;
  p_shape_vtable->p_free = _free;
  p_shape_vtable->p_area = NULL;
  p_shape_vtable->p_get_name = _get_name;
}

void Shape_ctor(Shape *this, const char *name)
{
  static int init_done = 0;
  memset(this, 0x00, sizeof(Shape));
  if (!init_done) {
    Shape_init(&Global_Shape_Vtable);
    init_done = 1;
  }
  this->p_vtable = &Global_Shape_Vtable;
  strlcpy(this->name, name, 10);
}

Shape * new_shape(const char *name)
{
  Shape * p = malloc(sizeof(Shape));
  Shape_ctor(p, name);
  return p;
}

void shape_dtor(Shape *this)
{
  _dtor(this);
  // this->p_vtable->p_dtor(this);  ---> this will cause infinite recursion
}

