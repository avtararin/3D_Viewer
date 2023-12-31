#include "3d_viewer.h"

Data parse_file(char *filename, Data *data3d) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "No such file");
  } else {
    *data3d = parse_counting(*file, data3d);
    fclose(file);

    file = fopen(filename, "r");
    *data3d = parse_values(*file, data3d);
    *data3d = find_minMax_points(data3d);
    *data3d = center_values(data3d);
    *data3d = scale(data3d, 0.4);
  }
  return *data3d;
}

//посчитать количество вершин, записать координаты, найти Мин| Макс по каждой
//координате

Data parse_counting(FILE filename, Data *data3d) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int count_vertex = 0, count_polygon = 0;

  while ((read = getline(&line, &len, &filename)) != -1) {
    if (line[0] == 'v' && line[1] == ' ')
      count_vertex++;
    else if (line[0] == 'f' && line[1] == ' ')
      count_polygon++;
  }
  points *coords = malloc(sizeof(points) * count_vertex);
  data3d->v->coord = coords;
  data3d->v->amount_vert = count_vertex;

  polygon *p = malloc(sizeof(polygon) * count_polygon);
  data3d->p = p;
  data3d->amount_polygon = count_polygon;
  free(line);
  return *data3d;
}

Data parse_values(FILE filename, Data *data3d) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int count_vertex = 0, count_polygon = 0;

  while ((read = getline(&line, &len, &filename)) != -1) {
    if (line[0] == 'v' && line[1] == ' ') {
      read_point_value(data3d, line, len, count_vertex);
      count_vertex++;
    } else if (line[0] == 'f' && line[1] == ' ') {
      read_polygon_value(data3d, line, len, count_polygon);
      count_polygon++;
    }
  }
  free(line);

  // for (int i = 0; i < data3d->v->amount_vert; i++) {
  //   printf("%lf %lf %lf \n", data3d->v->coord[i].x, data3d->v->coord[i].y,
  //          data3d->v->coord[i].z);
  // }
  //   for (int i = 0; i < data3d->amount_polygon; i++) {
  //     printf("\npolygon %d", i);
  //     for(int j = 0; j < 3; j++){
  //       printf("%d |", data3d->p[i].p[j]);
  //     }
  // }

  return *data3d;
}

Data read_point_value(Data *data3d, char *line, int len, int num_of_coord) {
  int counter = 0, sign = 1;
  for (int i = 0; i < 32; i++) {
    if (line[i] == '-') {
      sign *= -1;
    } else if ((line[i] >= '0' && line[i] <= '9')) {
      double value = 0;
      bool dec_num = false;
      int cnt = 0;
      while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.' ||
             line[i] == ',') {
        if (line[i] == ',' || line[i] == '.') {
          dec_num = true;
        } else {
          value = value * 10 + (line[i] - '0');
          if (dec_num) {
            cnt++;
          }
        }
        i++;
      }
      if (dec_num) {
        value = value * pow(10, -cnt);
      }
      i--;
      value *= sign;
      sign *= sign;

      if (counter == 0) {
        data3d->v->coord[num_of_coord].x = value;
        counter++;
      } else if (counter == 1) {
        data3d->v->coord[num_of_coord].y = value;
        counter++;
      } else
        data3d->v->coord[num_of_coord].z = value;
    }
  }
  return *data3d;
}

Data read_polygon_value(Data *data3d, char *line, int len, int num_of_polygon) {
  int counter = 0, sign = 1;
  int polygon_values[100];
  for (int i = 0; i < 32; i++) {
    if (line[i] == '-') {
      sign *= -1;
    } else if ((line[i] >= '0' && line[i] <= '9')) {
      double value = 0;
      bool dec_num = false;
      int cnt = 0;
      while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.' ||
             line[i] == ',') {
        if (line[i] == ',' || line[i] == '.') {
          dec_num = true;
        } else {
          value = value * 10 + (line[i] - '0');
          if (dec_num) {
            cnt++;
          }
        }
        i++;
      }
      if (dec_num) {
        value = value * pow(10, -cnt);
      }
      i--;
      value *= sign;
      sign *= sign;

      if (counter == 0) {
        polygon_values[0] = (int)value;
        counter++;
      } else if (polygon_values[counter - 1] != (int) value) {
        polygon_values[counter] = (int) value;
        counter++;
        //printf("\npolygon_values[%d] = %d, value = %lf\n", counter, polygon_values[counter], value);
      }
    }
  }
  data3d->p[num_of_polygon].amount_p = counter;
  int *p = malloc(sizeof(int) * counter);
  data3d->p[num_of_polygon].p = p;
  for(int i = 0; i <= counter; i++){
    data3d->p[num_of_polygon].p[i] = polygon_values[i];
  }
  return *data3d;
}

Data find_minMax_points(Data *data3d){
  double 
  minx = data3d->v->coord[0].x,
  maxx = data3d->v->coord[0].x,
  miny = data3d->v->coord[0].y,
  maxy = data3d->v->coord[0].y,
  maxz = data3d->v->coord[0].z,
  minz = data3d->v->coord[0].z;

  for (int i = 0; i < data3d->v->amount_vert; i++){
    if (data3d->v->coord[i].x < minx) minx = data3d->v->coord[i].x;
    if (data3d->v->coord[i].x > maxx) maxx = data3d->v->coord[i].x;
    if (data3d->v->coord[i].y < miny) miny = data3d->v->coord[i].y;
    if (data3d->v->coord[i].y > maxy) maxy = data3d->v->coord[i].y;
    if (data3d->v->coord[i].z < minz) minz = data3d->v->coord[i].z;
    if (data3d->v->coord[i].z > maxz) maxz = data3d->v->coord[i].z;
  }
  data3d->v->minMaxX[0] = minx;
  data3d->v->minMaxX[1] = maxx;
  data3d->v->minMaxY[0] = miny;
  data3d->v->minMaxY[1] = maxy;
  data3d->v->minMaxZ[0] = minz;
  data3d->v->minMaxZ[1] = maxz;
  return *data3d;
}

Data center_values(Data *data3d){
  double centerX = data3d->v->minMaxX[0] + (data3d->v->minMaxX[1] - data3d->v->minMaxX[0]) / 2;
  double centerY = data3d->v->minMaxY[0] + (data3d->v->minMaxY[1] - data3d->v->minMaxY[0]) / 2;
  double centerZ = data3d->v->minMaxZ[0] + (data3d->v->minMaxZ[1] - data3d->v->minMaxZ[0]) / 2;

  for (int i = 0; i < data3d->v->amount_vert; i++){
    data3d->v->coord[i].x -= centerX;
    data3d->v->coord[i].y -= centerY;
    data3d->v->coord[i].z -= centerZ;
  }
  return *data3d;
}

Data scale(Data *data3d, double scale){
  double dx, dy, dz, dmax;
  dx = data3d->v->minMaxX[1] - data3d->v->minMaxX[0];
  dy = data3d->v->minMaxY[1] - data3d->v->minMaxY[0];
  dz = data3d->v->minMaxZ[1] - data3d->v->minMaxZ[0];
  dmax = fmax(dx, fmax(dy, dz));
  scale = (scale - (scale*(-1))) / dmax;
  for (int i = 0; i < data3d->v->amount_vert; i++){
    data3d->v->coord[i].x *= scale;
    data3d->v->coord[i].y *= scale;
    data3d->v->coord[i].z *= scale;
  }
  return *data3d;
}