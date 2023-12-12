#include <stdio.h>
#include <stdlib.h>

typedef struct points{
  double x;
  double y;
  double z;
} points;

typedef struct vertex {
  int amount_vert;
  points *coord;
  int minMaxX[2];
  int minMaxY[2];
  int minMaxZ[2];
} vertex;

typedef struct polygon{
  int *p;
  int amount_p;
} polygon;

typedef struct Data {
  vertex *v;
  polygon *p;
  int *amount_polygon;
} Data;

int parse_vertex(FILE filename, Data *data3d);
int parse_polygon(FILE filename, Data *data3d);
int parse_file(char *filename, Data *data3d);