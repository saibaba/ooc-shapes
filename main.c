#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "shape.h"
#include "rectangle.h"
#include "circle.h"

// http://dmitryfrank.com/articles/oop_in_c

int main(int argc, char ** argv)
{
  Rectangle * r1 = new_rectangle("r1", 3.5, 1.2);
  Shape *r1s = rectangle_shape_get(r1);

  char *n = shape_get_name(r1s);
  printf("Area of %s: %f\n", n, shape_area(r1s));
  shape_delete(r1s);

  Shape *s1 = new_shape("s1");
  printf("Name of shape1: %s\n", shape_get_name(s1));
  shape_delete(s1);

  Circle *c1 = new_circle("c1", 3.0);
  Shape *c1s = circle_shape_get(c1);
  printf("Area of circle %s: %f\n", shape_get_name(c1s), shape_area(c1s));
  shape_delete(c1s);
  return 0;
}
