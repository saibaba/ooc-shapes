#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "circle.h"

static Shape_Vtable Global_Circle_Vtable;

static int Circle_instanceof(const Shape *super)
{
  return (super->p_vtable == &Global_Circle_Vtable);
}

static Circle * Circle_get_by_Shape(const Shape *super)
{
  Circle *p_circle = NULL;

  if (Circle_instanceof(super)) {
    // WARNING
    // DANGER
    // TODO
    // For the typecast to work, the first field of derived class (Circle) must be the vtable;
    p_circle = (Circle *)super;
  } else {
    printf("BUG!!!\n");
    exit(1);
  }
  return p_circle;
}

inline Shape *circle_shape_get(Circle *this)
{
  return &(this->base);
}

static double Circle_area(Shape  *this)
{
  Circle *r = Circle_get_by_Shape(this);
  return (3.14 * r->radius * r->radius);
}

static void Circle_dtor(Shape *this) 
{
  shape_dtor(this);
  Circle *r = Circle_get_by_Shape(this);
  printf("Circle Calling destructor for %p\n", r);
}

static void Circle_free(Shape *this) 
{
  Circle *r = Circle_get_by_Shape(this);
  printf("Circle Freeing memory\n");
  free(r);
}

static void Circle_init(Shape_Vtable * p_shape_vtable) 
{
  Shape_init(p_shape_vtable);
  p_shape_vtable->p_area = Circle_area;
  p_shape_vtable->p_dtor = Circle_dtor;
  p_shape_vtable->p_free = Circle_free;
}

void Circle_ctor(Circle *this, const char * name, double r)
{
  Shape_ctor(&this->base, name);
  static int init_done = 0;
  if (!init_done) {
    Circle_init(&Global_Circle_Vtable);
    init_done = 1;
  }
  (this->base).p_vtable = &Global_Circle_Vtable;
  this->radius = r;
}

Circle * new_circle(const char *name, double r)
{
  Circle *p = malloc(sizeof(Circle));
  Circle_ctor(p, name, r);
  return p;
}
