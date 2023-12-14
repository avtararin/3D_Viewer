#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct points {
  double x;
  double y;
  double z;
} points;

typedef struct vertex {
  int amount_vert;
  points *coord;
  double minMaxX[2];
  double minMaxY[2];
  double minMaxZ[2];
} vertex;

typedef struct polygon {
  int *p;
  int amount_p;
} polygon;

typedef struct Data {
  vertex *v;
  polygon *p;
  int amount_polygon;
} Data;

Data parse_counting(FILE filename, Data *data3d);
Data parse_values(FILE filename, Data *data3d);
Data parse_file(char *filename, Data *data3d);
Data read_point_value(Data *data3d, char *line, int len, int num_of_coord);
Data read_polygon_value(Data *data3d, char *line, int len, int num_of_polygon);
Data find_minMax_points(Data *data3d);