#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct rectangle rectangle;
typedef struct point point;

struct point { double x, y; };
struct rectangle {  point ul;  point br;  };

rectangle* rectangle_init(double ulx, double uly, double brx, double bry){
  rectangle* rect = (rectangle *)malloc(sizeof(rectangle));
  rect->ul.x = ulx;
  rect->ul.y = uly;
  rect->br.x = brx;
  rect->br.y = bry;
  return rect;
}
void rectangle_destructor(rectangle* r){ free(r); }

void rectangle_move(rectangle* r, double x, double y){
  r->ul.x =x;
  r->ul.y =y;
  r->br.x =x;
  r->br.y =y;
}
void rectangle_expandby(rectangle* r, double expandby){
  r->ul.x*=expandby;
  r->ul.y*=expandby;
  r->br.x*=expandby;
  r->br.y*=expandby;

}

double rectangle_area(rectangle* r){
  double l = fabs(r->ul.x - r->br.x);
  double w = fabs(r->ul.y - r->br.y);
  return l * w;
}

double rectangle_perimeter(rectangle* r){
  double l = fabs(r->ul.x - r->br.x);
  double w = fabs(r->ul.y - r->br.y);
  return 2 * (l+w);
}

int main(){
  rectangle* r = rectangle_init(1, 1, 2, 2);
  rectangle_destructor(r);
  return 0;
}
