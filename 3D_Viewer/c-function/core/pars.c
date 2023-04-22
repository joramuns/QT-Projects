#include "pars.h"

// int main() {
//   pars_counters A = {0, 0, 0, 0, 0};
//   FILE *obj =
//   fopen("/Users/mammiemi/Desktop/C8_3DViewer_v1.0-2/src/3D_Viewer/"
//                     "c-function/core/coub.obj",
//                     "r");
//   float *array = array_sort(obj, &A);
//   for (int i = 0; i < A.size_sort_array; i++) {
//     if (i % 4 == 0) {
//       printf("\n");
//     }
//     printf("%f ", array[i]);
//   }
//   printf("\ncount vertex - %d\n\ncount side - %d\n", A.count_vertex,
//          A.count_side);
//   if (array != NULL) {
//     free(array);
//   }
//   fclose(obj);
//   return 0;
// }

void *array_sort(FILE *obj, Pars_counters *view) {
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  view->size_unsort_memory = 4;
  view->size_sort_memory = 4;

  float *point_array = (float *)calloc(view->size_unsort_memory, sizeof(float));
  view->sorted_array = (float *)calloc(view->size_sort_memory, sizeof(float));

  while ((read = getline(&line, &len, obj)) != -1) {
    if (line[0] == 'v' && line[1] == ' ') {
      unsort_array_fill(line, view, &point_array);
    } else if (line[0] == 'f' && line[1] == ' ') {
      sort_array_fill(line, view, point_array);
    }
  }
  view->count_vertex /= 4;
  if (point_array) {
    free(point_array);
  }
  if (line)
    free(line);
}

void unsort_array_fill(char *line, Pars_counters *view, float **point_array) {
  char *token = strtok(line, " ");
  for (int i = 0; i < 5; i++) {
    if (view->count_vertex == view->size_unsort_memory) {
      view->size_unsort_memory *= 2;
      *point_array = (float *)realloc(*point_array,
                                      view->size_unsort_memory * sizeof(float));
    }
    if (i == 4 && (token == NULL || token[0] == '\n')) {
      (*point_array)[view->count_vertex++] = 1.0;
    } else if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
      (*point_array)[view->count_vertex++] = my_atof(token);
    }
    token = strtok(NULL, " ");
  }
}

void sort_array_fill(char *line, Pars_counters *view, float *point_array) {
  char *token_f = strtok(line, " ");
  while (token_f) {
    if (isdigit(token_f[0])) {
      if (view->size_sort_array == view->size_sort_memory) {
        view->size_sort_memory *= 2;
        view->sorted_array = (float *)realloc(view->sorted_array, view->size_sort_memory *
                                                            sizeof(float));
      }
      int vertex_number = my_atoi(token_f) - 1;
      for (int i = 0; i < 4; i++) {
        view->sorted_array[view->size_sort_array++] =
            point_array[vertex_number * 4 + i];
      }
    }
    token_f = strtok(NULL, " ");
  }
  view->count_side += 1;
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
