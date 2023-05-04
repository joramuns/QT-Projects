#include "pars.h"

/*!
  \brief Парсит входной поток в массив координат точек в трехмерном
  пространстве, выстраивая правильный порядок этих координат в массиве
  \param[in] obj - поток, который необходимо распарсить.
  \param[out] view - указатель на структуру хранящую в себе массив и
  вспомогательные данные.
*/
void array_sort(FILE *obj, Pars_counters *view) {
  if (!obj || !view)
    return;
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

/*!
  \brief Из получаемой на вход строки вычленяет и преобразовывает все
  координаты точек записанные в этой строке, затем записывает их в массив типа
  float, в том порядке, в котором встречает их в строке, при необходимости
  довыделяет память массива для хранения координат
  \param[in] line - указатель на массив символов, который необходимо распарсить.
  \param[in] view - указатель на структуру, которая хранит в себе размер
  выделенной памяти. \param[out] point_array - указатель на указатель типа
  float, массив в который записываются результаты.
*/
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

/*!
  \brief Из получаемой на вход строки вычленяет правильный порядок
  координат точек и записывает в новый массив хранящийся в структуре, в
  правильном порядке. \param[in] line - указатель на массив символов, который
  необходимо распарсить, который содержит в себе информацию о правильном порядке
  координат. \param[out] view - указатель на структуру, которая хранит в себе
  новый массив координат точек и необхдимые счетчики. \param[in] point_array -
  указатель на указатель типа float, массив из которого читаются координаты
  точек.
*/
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
        view->count_edges += 1;
      }
      point_assignment(view, point_array, vertex_number);
      view->count_edges += 1;
      if (counter > 2)
        vertex_number_last = vertex_number;
    }
    token_f = strtok(NULL, " ");
  }
}

/*!
  \brief  При необходимости довыделяет память под массив координат точек.
  \param[in] view - указатель на структуру, которая хранит в себе новый массив
  координат точек и необхдимый размер памяти.
*/
void memory_of_sort_alloc(Pars_counters *view) {
  if (view->size_sort_array == view->size_sort_memory) {
    view->size_sort_memory *= 2;
    view->sorted_array = (float *)realloc(
        view->sorted_array, view->size_sort_memory * sizeof(float));
  }
}

/*!
  \brief В отсортированный массив, в определенное место записывает
  координаты точки из несортированного массива \param[out] view - указатель на
  структуру, которая хранит в себе новый массив координат точек и необхдимый
  размер памяти. \param[in] point_array - указатель на массив неотсортированных
  координат точки. \param[in] index_of_point - позиция точки.
*/
void point_assignment(Pars_counters *view, float *point_array,
                      int index_of_point) {
  for (int i = 0; i < 4; i++) {
    view->sorted_array[view->size_sort_array++] =
        point_array[index_of_point * 4 + i];
  }
}

/*!
  \brief Выполняет нормализацию массива координат точек для корректного
   отображения модели.
  \param[out] view - указатель на структуру в которой хранится массив.
*/
void normalize(Pars_counters *view) {
  float maximum = maxpoint(view);
  scaling(1 / maximum, view->sorted_array, view->size_sort_array);
}

/*!
  \brief Находит максимальное значение из массива координат точек и возвращает
  его. \return Максимальное значение в массиве.
*/
float maxpoint(Pars_counters *view) {
  float maximum = view->sorted_array[0];
  for (int i = 0; i < view->size_sort_array; i++) {
    if ((fabsf(view->sorted_array[i]) - fabsf(maximum)) > S21_EPS) {
      maximum = view->sorted_array[i];
    }
  }
  return fabsf(maximum);
}

/*!
  \brief Преобразовывет входную строку в число типа float и возвращает его.
  \return Преобразованное число.
*/
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
  if (str[i] == 'e') {
    i++;
    int flag = 0;
    if (str[i] == '-') {
      flag = -1;
    } else if (str[i] == '+') {
      flag = 1;
    }
    i++;
    int scale = my_atoi(str + i);
    value = value * powf(10, scale * flag);
  }
  return sign * value;
}

/*!
  \brief Преобразовывет входную строку в число типа int и возвращает его.
  \return Преобразованное число.
*/
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
