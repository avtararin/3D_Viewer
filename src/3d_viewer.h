#include <stdio.h>
#include <stdlib.h>

typedef struct Data {
  vertex *v;
  polygon *p;
  int *amount_polygon;
} Data;

// typedef struct Node Node;
// // Определение структуры узла списка
// typedef struct Node {
//   double value;
//   int priority;
//   Node *next;
//   types type;
// } Node;

typedef struct {
  int amount_vert;
  points *coord;
  int minMaxX[2];
  int minMaxY[2];
  int minMaxZ[2];
} vertex;

typedef struct {
  double x;
  double y;
  double z;
} points;

typedef struct {
  int *p;
  int amount_p;
} polygon;

int parse_vertex(FILE filename, Data *data3d);
int parse_polygon(FILE filename, Data *data3d);
int parse_file(char *filename, Data *data3d);