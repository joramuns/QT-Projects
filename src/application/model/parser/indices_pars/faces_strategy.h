/*!
\file
\brief Заголовочный файл с описанием классов стратегии парсера индексов вершин
*/
#ifndef CPP4_3DVIEWER_V2_MODEL_PARSER_FACES_STRATEGY_H
#define CPP4_3DVIEWER_V2_MODEL_PARSER_FACES_STRATEGY_H
#include <OpenGL/gl.h>
// #include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
/// @brief Родительский абстрактный класс, который описывает базовое поведение
/// для всех наследников.
class FacesStrategy {
public:
  /// @brief Конструктор по умолчанию - удален.
  FacesStrategy() = delete;

  /// @brief Конструктор с входными параметрами
  /// @param file Файловый поток из которого мы читаем данные
  /// @param file_pos  Позиция с которой начинается считывание данных
  FacesStrategy(std::ifstream *file, const int file_pos);

  /// @brief Виртуальный деструктор
  virtual ~FacesStrategy(){};

  /// @brief Модификатор доступа
  /// @return Вектор индексов вершин
  std::vector<GLint> GetVertices() const noexcept;

  /// @brief Модификатор доступа
  /// @return Вектор индексов текстур
  std::vector<GLint> GetTextures() const noexcept;

  /// @brief Модификатор доступа
  /// @return Вектор индексов нормалей
  std::vector<GLint> GetNormals() const noexcept;

  /// @brief Core функция, выполняющая считывание данных и сохранение, для
  /// дальнейшего использования
  /// @return Позицию в потоке на которой закончилось считывание
  virtual int Pars() = 0;

protected:
  /// @brief Функция отвечает за теселяцию индексов полигонов, организовывает
  /// правильный порядок индексов в векторе
  /// @param indexes Исходный вектор индексов
  /// @param type_of_indexes Целевой(преобразованный) вектор индексов
  void TesselationFill(const std::vector<GLint> &indexes,
                       std::vector<GLint> &type_of_indexes) noexcept;

protected:
  std::ifstream
      *file_; ///< Файловый поток, из которого происходит чтение данных

  std::vector<GLint>
      vertices_; ///< Целевой(преобразованный) вектор индексов вершин
  std::vector<GLint>
      texutres_; ///< Целевой(преобразованный) вектор индексов текстур
  std::vector<GLint>
      normals_; ///< Целевой(преобразованный) вектор индексов нормалей

private:
};

/// @brief Класс наследник обеспечивающий работу с индексами ВЕРШИН
class VertexStrategy : public FacesStrategy {
public:
  /// @brief Конструктор с входными параметрами
  /// @param file Файловый поток из которого мы читаем данные
  /// @param file_pos  Позиция с которой начинается считывание данных
  VertexStrategy(std::ifstream *file, const int file_pos);

  /// @brief Core функция, выполняющая считывание данных и сохранение, для
  /// дальнейшего использования
  /// @return Позицию в потоке на которой закончилось считывание
  int Pars() noexcept override;
};

/// @brief Класс наследник, обеспечивающий работу с индексами ВЕРШИН и ТЕКСТУР
class VertexTexturesStrategy : public FacesStrategy {
public:
  /// @brief Конструктор с входными параметрами
  /// @param file Файловый поток из которого мы читаем данные
  /// @param file_pos  Позиция с которой начинается считывание данных
  VertexTexturesStrategy(std::ifstream *file, const int file_pos);

  /// @brief Core функция, выполняющая считывание данных и сохранение, для
  /// дальнейшего использования
  /// @return Позицию в потоке на которой закончилось считывание
  int Pars() noexcept override;
};

/// @brief Класс наследник, обеспечивающий работу с индексами ВЕРШИН и НОРМАЛЕЙ
class VertexNormalsStrategy : public FacesStrategy {
public:
  /// @brief Конструктор с входными параметрами
  /// @param file Файловый поток из которого мы читаем данные
  /// @param file_pos  Позиция с которой начинается считывание данных
  VertexNormalsStrategy(std::ifstream *file, const int file_pos);

  /// @brief Core функция, выполняющая считывание данных и сохранение, для
  /// дальнейшего использования
  /// @return Позицию в потоке на которой закончилось считывание
  int Pars() noexcept override;
};

/// @brief Класс наследник, обеспечивающий работу с индексами ВЕРШИН, ТЕКСТУР и
/// НОРМАЛЕЙ
class VertexTexturesNormalsStrategy : public FacesStrategy {
public:
  /// @brief Конструктор с входными параметрами
  /// @param file Файловый поток из которого мы читаем данные
  /// @param file_pos  Позиция с которой начинается считывание данных
  VertexTexturesNormalsStrategy(std::ifstream *file, const int file_pos);

  /// @brief Core функция, выполняющая считывание данных и сохранение, для
  /// дальнейшего использования
  /// @return Позицию в потоке на которой закончилось считывание
  int Pars() noexcept override;
};

} // namespace s21
#endif // CPP4_3DVIEWER_V2_MODEL_PARSER_FACES_STRATEGY_H