#include "3d_viewer.h"
#include <stdio.h>

int main() {
  Data *data3d = malloc(sizeof(Data));
  data3d->v = malloc(sizeof(vertex));
  char filename[100] = "skull.obj";
  *data3d = parse_file(filename, data3d);
  printf("\nvertexes = %d polygons = % d\n", data3d->v->amount_vert,
         data3d->amount_polygon);
  for (int i = 0; i < data3d->v->amount_vert; i++) {
    printf("%f %f %f \n", data3d->v->coord[i].x, data3d->v->coord[i].y,
           data3d->v->coord[i].z);
  }

  return 0;
}