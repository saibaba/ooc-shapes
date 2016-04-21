#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rectangle.h"

static Shape_Vtable Global_Rectangle_Vtable;

static int Rectangle_instanceof(const Shape *super)
{
  return (super->p_vtable == &Global_Rectangle_Vtable);
}

static Rectangle * Rectangle_get_by_Shape(const Shape *super)
{
  Rectangle *p_rectangle = NULL;

  if (Rectangle_instanceof(super)) {
    // WARNING
    // DANGER
    // TODO
    // For the typecast to work, the first field of derived class (Rectangle) must be the vtable;
    p_rectangle = (Rectangle *)super;
  } else {
    printf("BUG!!!\n");
    exit(1);
  }
  return p_rectangle;
}

inline Shape *rectangle_shape_get(Rectangle *this)
{
  return &(this->base);
}

static double _area(Shape  *this)
{
  Rectangle *r = Rectangle_get_by_Shape(this);
  printf("Area fn: width=%f, height=%f\n", r->width, r->height);
  return (r->width * r->height);
}

static void _dtor(Shape *this) 
{
  Rectangle *r = Rectangle_get_by_Shape(this);
  shape_dtor(this);
  printf("Rectangle Calling destructor for %p\n", r);
}

static void _free(Shape *this) 
{
  Rectangle *r = Rectangle_get_by_Shape(this);
  printf("Rectangle Freeing memory\n");
  free(r);
}

static void Rectangle_init(Shape_Vtable * p_shape_vtable) 
{
  Shape_init(p_shape_vtable);
  p_shape_vtable->p_area = _area;
  p_shape_vtable->p_dtor = _dtor;
  p_shape_vtable->p_free = _free;
}

void Rectangle_ctor(Rectangle *this, const char * name, double w, double h)
{
  memset(this, 0x00, sizeof(Rectangle));
  Shape_ctor(&this->base, name);
  static int init_done = 0;
  if (!init_done) {
    Rectangle_init(&Global_Rectangle_Vtable);
    init_done = 1;
  }
  (this->base).p_vtable = &Global_Rectangle_Vtable;
  this->width = w;
  this->height = h;
}

Rectangle * new_rectangle(const char *name, double w, double h)
{
  Rectangle *p = malloc(sizeof(Rectangle));
  Rectangle_ctor(p, name, w, h);
  return p;
}
