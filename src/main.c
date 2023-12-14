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
    // printf("%f %f %f \n", data3d->v->coord[i].x, data3d->v->coord[i].y,
    //        data3d->v->coord[i].z);
  }
  return 0;
}

//   while ((read = getline(&line, &len, &filename)) != -1) {
//     if (line[0] == 'f' && line[1] == ' '){
//       count_vertex++;
//     for (int i = 2; i < len; i++){
//        if ((line[i] >= '0' && line[i] <= '9')) {
//           double value = 0;
//           bool dec_num = false;
//           int cnt = 0;
//           while ((line[i] >= '0' && line[i] <= '9') || line[i] == '.' ||
//           line[i] == ',') {
//     if (line[i] == ',' || line[i] == '.') {
//       dec_num = true;
//     } else {
//       value = value * 10 + (line[i] - '0');
//       if (dec_num) {
//         cnt++;
//       }
//     }
//     i++;
//   }
//   // Если число десятичное, меняем его знак у счетчика и делаем
//   десятичное if (dec_num) {
//     value = value * pow(10, -cnt);
//   }
//   // Помещаем лексему в стек с типом "число" и приоритетом 0
//   data3d->v->coord[100]
//   data3d->v->coord->x = value;
//   i--;
// }
//     }
//     }
// }