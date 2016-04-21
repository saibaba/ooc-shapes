#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"

typedef struct Circle {
  struct Shape base; // must be the first field ... see DANGER
  double radius;
} Circle;

Shape *circle_shape_get(Circle *this);
void Circle_ctor(Circle *this, const char * name, double r);
Circle * new_circle(const char *name, double r);

#endif
