#include "pars.h"

float *array_sort(float *sorted_array, char *filename, int *count_vertex,
                  int *count_side, int *size_sort_array) {
  FILE *obj = fopen(filename, "r");
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  *count_vertex = 0;
  *count_side = 0;

  int count_vertex_array = 0;
  int index_sorted_array = 0;

  int size_unsort_memory = 4;
  int size_sort_memory = 4;

  float *point_array = (float *)calloc(size_unsort_memory, sizeof(float));
  sorted_array = (float *)calloc(size_sort_memory, sizeof(float));

  if (obj == NULL) {
    printf("lol\n");
    sorted_array = NULL;
  } else {
    while ((read = getline(&line, &len, obj)) != -1) {
      if (line[0] == 'v' && line[1] == ' ') {
        char *token = strtok(line, " ");
        for (int i = 0; i < 5; i++) {
          if (count_vertex_array == size_unsort_memory) {
            memory_alloc(point_array, &size_unsort_memory);
          }
          if (i == 4 && (token == NULL || token[0] == '\n')) {
            point_array[count_vertex_array] = 1.0;
            count_vertex_array++;
          } else if (isdigit(token[0]) ||
                     (token[0] == '-' && isdigit(token[1]))) {
            point_array[count_vertex_array] = my_atof(token);
            count_vertex_array++;
          }
          token = strtok(NULL, " ");
        }
        *count_vertex += 1;
      } else if (line[0] == 'f' && line[1] == ' ') {
        char *token_f = strtok(line, " ");
        while (token_f) {
          if (isdigit(token_f[0])) {
            if (count_vertex_array == size_sort_memory) {
              memory_alloc(sorted_array, &size_sort_memory);
            }
            int vertex_number = my_atoi(token_f) - 1;
            for (int i = 0; i < 4; i++) {
              sorted_array[index_sorted_array] =
                  point_array[vertex_number * 4 + i];
              index_sorted_array++;
            }
          }
          token_f = strtok(NULL, " ");
        }
        *count_side += 1;
      }
    }
  }
  *size_sort_array = index_sorted_array;
  if (point_array) {
    free(point_array);
  }
  if (line)
    free(line);
  return sorted_array;
}

void memory_alloc(float *array, int *size) {
  *size *= 2;
  array = (float *)realloc(array, *size);
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