#include "3d_viewer.h"

int parse_file(char *filename, Data *data3d) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "No such file");
  } else {
    parse_vertex(*file, data3d);
    parse_polygon(*file, data3d);
    fclose(file);
  }
}

int parse_vertex(FILE filename, Data *data3d){
    
}