#include "3d_viewer.h"

int parse_file(char *filename, Data *data3d) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "No such file");
  } else {
    parse_vertex(*file, data3d);
    //parse_polygon(*file, data3d);
    fclose(file);
  }
}
//посчитать количество вершин, записать координаты, найти Мин| Макс по каждой координате
int parse_vertex(FILE filename, Data *data3d){
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    size_t count_vertex = 0;

   while ((read = getline(&line, &len, &filename)) != -1) {
        // printf("Retrieved line of length %zu :\n", read);
        // printf("%s", line);
        if (line[0] == 'f' && line[1] == ' '){
          count_vertex++;
        }
    }
    printf("\nnum of vertexes - %d\n", count_vertex);
   free(line);
   exit(EXIT_SUCCESS);
}