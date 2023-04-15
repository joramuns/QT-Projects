#include "pars.h"

int main() {
  int exit_code = 0;
  char *filename = "coub.obj";
  FILE *obj = fopen(filename, "r");
  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int count_vertex = 0;
  int count_side = 0;
  int count_vertex_array = 0;
  float point_array[32] = {0};
  int count_side_array = 0;
  int side_array[24] = {0};
  if (obj == NULL) {
    exit_code = 1;
  } else {
    while ((read = getline(&line, &len, obj)) != -1) {
      if (line[0] == 'v' && line[1] == ' ') {
        char *token = strtok(line, " ");
        while (token) {
          if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            point_array[count_vertex_array] = my_atof(token);
            count_vertex_array++;
          }
          token = strtok(NULL, " ");
        }
        count_vertex++;
      } else if (line[0] == 'f' && line[1] == ' ') {
        char *token_f = strtok(line, " ");
        while (token_f) {
          if (isdigit(token_f[0])) {
            side_array[count_side_array] = my_atoi(token_f);
            count_side_array++;
          }
          token_f = strtok(NULL, " ");
        }
        count_side++;
      }
    }
  }
  printf("Count vertex  - %d\n", count_vertex);
  printf("Count side  - %d\n", count_side);
  for (int i = 0; i < count_vertex_array; i++) {
    printf("%f ", point_array[i]);
  }
  printf("\n");
  for (int i = 0; i < count_side_array; i++) {
    printf("%d ", side_array[i]);
  }
  printf("\n");

  // float sorted_array[96] = {0};

  // for (int i = 0; i < count_side_array; i++) {
  //   for (int j = 0; j < 4; j++) {
  //     sorted_array[i * 4 + j] = point_array[side_array[i] + j];
  //   }
  // }

  // for (int i = 0; i < count_side_array * 4; i++) {
  //   printf("%f ", sorted_array[i]);
  // }
  // printf("\n");

  if (line)
    free(line);
  return exit_code;
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