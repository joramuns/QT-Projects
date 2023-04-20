#include "pars.h"

/* int main() { */
/*   pars_counters A = {0, 0, 0, 0, 0}; */
/*   float *array = */
/*       array_sort("/Users/mammiemi/Desktop/C8_3DViewer_v1.0-2/src/3D_Viewer/" */
/*                  "c-function/core/coub.obj", */
/*                  &A); */
/*   for (int i = 0; i < A.size_sort_array; i++) { */
/*     if (i % 4 == 0) { */
/*       printf("\n"); */
/*     } */
/*     printf("%f ", array[i]); */
/*   } */
/*   printf("\ncount vertex - %d\n\ncount side - %d\n", A.count_vertex, */
/*          A.count_side); */
/*   if (array != NULL) { */
/*     free(array); */
/*   } */
/*   return 0; */
/* } */

float *array_sort(char *filename, pars_counters *View) {
  FILE *obj = fopen(filename, "r");
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  View->size_unsort_memory = 4;
  View->size_sort_memory = 4;

  float *point_array = (float *)calloc(View->size_unsort_memory, sizeof(float));
  float *sorted_array = (float *)calloc(View->size_sort_memory, sizeof(float));

  if (obj == NULL) {
    free(sorted_array);
    sorted_array = NULL;
  } else {
    while ((read = getline(&line, &len, obj)) != -1) {
      if (line[0] == 'v' && line[1] == ' ') {
        char *token = strtok(line, " ");
        for (int i = 0; i < 5; i++) {
          if (View->count_vertex == View->size_unsort_memory) {
            View->size_unsort_memory *= 2;
            point_array = (float *)realloc(point_array,
                                           View->size_unsort_memory * sizeof(float));
          }
          if (i == 4 && (token == NULL || token[0] == '\n')) {
            point_array[View->count_vertex++] = 1.0;
          } else if (isdigit(token[0]) ||
                     (token[0] == '-' && isdigit(token[1]))) {
            point_array[View->count_vertex++] = my_atof(token);
          }
          token = strtok(NULL, " ");
        }
      } else if (line[0] == 'f' && line[1] == ' ') {
        char *token_f = strtok(line, " ");
        while (token_f) {
          if (isdigit(token_f[0])) {
            if (View->size_sort_array == View->size_sort_memory) {
              View->size_sort_memory *= 2;
              sorted_array = (float *)realloc(sorted_array,
                                              View->size_sort_memory * sizeof(float));
            }
            int vertex_number = my_atoi(token_f) - 1;
            for (int i = 0; i < 4; i++) {
              sorted_array[View->size_sort_array++] =
                  point_array[vertex_number * 4 + i];
            }
          }
          token_f = strtok(NULL, " ");
        }
        View->count_side += 1;
      }
    }
  }
  View->count_vertex /= 4;
  if (point_array) {
    free(point_array);
  }
  if (line)
    free(line);
  if (obj)
    fclose(obj);
  return sorted_array;
}

float my_atof(char *str) {
  float value = 0.0;
  int sign = 1;
  int i = 0;
  while (isspace(str[i])) {
    i++;
  }

  if (str[i] == '-') {
    sign = -1;
    i++;
  } else if (str[i] == '+') {
    i++;
  }

  while (isdigit(str[i])) {
    value = value * 10.0 + (str[i] - '0');
    i++;
  }

  if (str[i] == '.') {
    float factor = 1.0;
    i++;
    while (isdigit(str[i])) {
      factor *= 0.1;
      value = value + (str[i] - '0') * factor;
      i++;
    }
  }
  return sign * value;
}

int my_atoi(const char *str) {
  int result = 0;
  int sign = 1;

  while (*str == ' ') {
    str++;
  }

  if (*str == '-') {
    sign = -1;
    str++;
  } else if (*str == '+') {
    str++;
  }

  while (*str >= '0' && *str <= '9') {
    result = result * 10 + (*str - '0');
    str++;
  }

  return sign * result;
}
