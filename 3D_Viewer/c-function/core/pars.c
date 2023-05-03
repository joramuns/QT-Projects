#include "pars.h"

void array_sort(FILE *obj, Pars_counters *view) {
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
  normalize(view);
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

  int vertex_number_first = -1;
  int vertex_number_last = -1;
  int counter = 0;

  while (token_f) {
    if (isdigit(token_f[0])) {

      memory_of_sort_alloc(view);

      int vertex_number = my_atoi(token_f) - 1;
      counter++;

      if (vertex_number_first < 0)
        vertex_number_first = vertex_number;
      if (counter > 3) {
        point_assignment(view, point_array, vertex_number_first);
        memory_of_sort_alloc(view);
        point_assignment(view, point_array, vertex_number_last);
        memory_of_sort_alloc(view);
      }
      point_assignment(view, point_array, vertex_number);
      if (counter > 2)
        vertex_number_last = vertex_number;
    }
    token_f = strtok(NULL, " ");
  }
  view->count_side += 1;
}

void memory_of_sort_alloc(Pars_counters *view) {
  if (view->size_sort_array == view->size_sort_memory) {
    view->size_sort_memory *= 2;
    view->sorted_array = (float *)realloc(
        view->sorted_array, view->size_sort_memory * sizeof(float));
  }
}

void point_assignment(Pars_counters *view, float *point_array,
                      int index_of_point) {
  for (int i = 0; i < 4; i++) {
    view->sorted_array[view->size_sort_array++] =
        point_array[index_of_point * 4 + i];
  }
}

void normalize(Pars_counters *view) {
  float maximum = maxpoint(view);
  scaling(1 / maximum, view->sorted_array, view->size_sort_array);
}

float maxpoint(Pars_counters *view) {
  float maximum = view->sorted_array[0];
  for (int i = 0; i < view->size_sort_array; i++) {
    if ((fabsf(view->sorted_array[i]) - fabsf(maximum)) > S21_EPS) {
      maximum = view->sorted_array[i];
    }
  }
  return fabsf(maximum);
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
