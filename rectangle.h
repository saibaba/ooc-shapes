#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

typedef struct Rectangle {
  struct Shape base; // must be the first field ... see DANGER
  double width;
  double height;
} Rectangle;

Shape *rectangle_shape_get(Rectangle *this);
void Rectangle_ctor(Rectangle *this, const char * name, double w, double h);
Rectangle * new_rectangle(const char *name, double w, double h);

#endif
