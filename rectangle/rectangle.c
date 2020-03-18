#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct rectangle rectangle;
typedef struct point point;

struct point { double x, y; };
point* point_constructor(double x, double y){
  point* p = (point *)malloc(sizeof(point));
  p->x =  x;
  p->y =  y;
  return p;
}

void point_destructor(point* p){ free(p); }


struct rectangle {  point ul;  point br;  };

void rectangle_update_cooridnates(rectangle* r, point* ul_r, point* br_r){
  // give the rectangle new coordinates
  r->ul.x = ul_r->x;
  r->ul.y = ul_r->y;
  r->br.x = br_r->x;
  r->br.y = br_r->y;
}

rectangle* rectangle_constructor(point* ul, point* br){
  rectangle* rect = (rectangle *)malloc(sizeof(rectangle));
  rectangle_update_cooridnates(rect, ul, br);
  return rect;
}

double length_(rectangle* r){ return fabs(r->ul.x - r->br.x); }
double width_(rectangle* r){ return fabs(r->ul.y - r->br.y); }

void rectangle_destructor(rectangle* r){ free(r); }

void rectangle_move(rectangle* r, double alpha, double beta){
  // move the rectangle horizontally by a constant alpha
  // move the rectangl vertically by a constant beta
  r->ul.x+=alpha;
  r->ul.y+=beta;
  r->br.x+=alpha;
  r->br.y+=beta;
}
void rectangle_expandby(rectangle* r, double lambda){
  // dialate the rectangle by a constant lambda
  r->ul.x*=lambda;
  r->ul.y*=lambda;
  r->br.x*=lambda;
  r->br.y*=lambda;
}

double rectangle_area(rectangle* r){
  // compute the area of the rectangle in R^2
  return (length_(r) * width_(r));
}

double rectangle_perimeter(rectangle* r){
  // compute the perimeter of the rectangle in R^2
  return 2 * (length_(r)+width_(r));
}

void rectangle_repr(rectangle* r){
  printf("Upper left: (%g, %g)\nBottom right: (%g, %g)", 
          r->ul.x, r->ul.y, r->br.x, r->br.y);
}

int main(){
  point* upper = point_constructor(0, 1);
  point* bottom = point_constructor(2, 0);
  rectangle* r = rectangle_constructor(upper, bottom);
  rectangle_repr(r);
  rectangle_destructor(r);
  point_destructor(upper);
  point_destructor(bottom);
  return 0;
}
