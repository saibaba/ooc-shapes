#ifndef SHAPE_H
#define SHAPE_H

typedef struct Shape Shape;

typedef void (Shape_dtor)(Shape *);
typedef double (Shape_area)(Shape *);
typedef char * (Shape_get_name)(Shape *this);
typedef void (Shape_free)(Shape *);

typedef struct Shape_Vtable {
  Shape_dtor     *p_dtor;
  Shape_free     *p_free;
  Shape_area     *p_area;
  Shape_get_name *p_get_name;
} Shape_Vtable;

struct Shape {
  Shape_Vtable *p_vtable;
  char name[10];
};

void Shape_init(Shape_Vtable *p_shape_vtable); // needed for sub-classes to init their vtable before overriding
void Shape_ctor(Shape *this, const char *name);

Shape * new_shape(const char *name);

static inline double shape_area(Shape *this)
{
  return this->p_vtable->p_area(this);
}

static inline char * shape_get_name(Shape *this)
{
  return this->p_vtable->p_get_name(this);
}

void shape_dtor(Shape *this);

static inline void shape_delete(Shape *this)
{
  this->p_vtable->p_dtor(this);
  this->p_vtable->p_free(this);
}
  
#endif
