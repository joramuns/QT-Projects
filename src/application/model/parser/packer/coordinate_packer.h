/*!
\file
\brief Заголовочный файл с описанием классов.

Данный файл содержит в себе определения классов упаквощика,
который отвечает за упорядочное расположение координат 3-х мерной модели,
для дальнейшей отрисовки в OpenGL
*/
#ifndef CPP4_3DVIEWER_V2_MODEL_PARSER_PACKER_COORDINATE_PACKER_H
#define CPP4_3DVIEWER_V2_MODEL_PARSER_PACKER_COORDINATE_PACKER_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif  // __APPLE__

#ifdef __linux__
#include <GL/glut.h>
#endif // __linux__

#include <vector>

namespace s21 {
/// @brief Родительский класс упаковщика, который описывает базовое поведение
/// классов наследников
class CoordinatePacker {
public:
  /// @brief Конструктор по умолчанию - удален
  CoordinatePacker() = delete;

  /// @brief Конструктор с параметрами
  /// @param vertices Пара, хранящая в себе вектор векторов(так как модели могут
  /// быть мультиобъектные) координат и вектор векторов индексов точек
  CoordinatePacker(
      const std::pair<std::vector<std::vector<GLfloat>>,
                      std::vector<std::vector<GLint>>> &vertices) noexcept;

  /// @brief Виртуальный деструктор
  virtual ~CoordinatePacker(){};

  /// @brief Модификатор доступа
  /// @return Отсортированный вектор всех точек 3-х мерного объекта
  std::vector<std::vector<GLfloat>> GetCoordinates() const noexcept;

protected:
  /// @brief Core функция отвечающая за сортировку всех значений в корректном
  /// порядке
  virtual void Pack() = 0;
  bool CheckRange(const std::vector<GLfloat> vec, const GLint &index) const noexcept; 

protected:
  std::vector<std::vector<GLfloat>>
      all_coordinates_; ///< Целевой вектор упакованных данных, возвращаемый
                        ///< пользователю для дальнейшей работы с ними в OpenGL

  std::pair<std::vector<std::vector<GLfloat>>, std::vector<std::vector<GLint>>>
      vertices_; ///< Пара векторов векторов координат вершин и векторов
                 ///< векторов соответствующих индексов
  std::pair<std::vector<std::vector<GLfloat>>, std::vector<std::vector<GLint>>>
      textures_; ///< Пара векторов векторов координат текстур и векторов
                 ///< векторов соответствующих индексов
  std::pair<std::vector<std::vector<GLfloat>>, std::vector<std::vector<GLint>>>
      normals_; ///< Пара векторов векторов координат нормалей и векторов
                ///< векторов соответствующих индексов
  bool is_pack_{true};
};

/// @brief Дочерний класс отвечающий за упаковку данных координат ВЕРШИН в
/// соответствии с индексами
class VertexCoordinatePacker : public CoordinatePacker {
public:
  /// @brief Конструктор с параметрами
  /// @param vertices Пара векторов векторов координат вершин и векторов
  /// векторов соответствующих индексов
  VertexCoordinatePacker(
      const std::pair<std::vector<std::vector<GLfloat>>,
                      std::vector<std::vector<GLint>>> &vertices) noexcept;

private:
  /// @brief Core функция отвечающая за сортировку всех значений координат
  /// ВЕРШИН в корректном порядке
  void Pack() noexcept override;
};

/// @brief Дочерний класс отвечающий за упаковку данных координат ВЕРШИН и
/// ТЕКСТУР в соответствии с их индексами
class VertexTexturesCoordinatePacker : public CoordinatePacker {
public:
  /// @brief Конструктор с параметрами
  /// @param vertices Пара векторов векторов координат вершин и векторов
  /// векторов соответствующих индексов
  /// @param textures Пара векторов векторов координат текстур и векторов
  /// векторов соответствующих индексов
  VertexTexturesCoordinatePacker(
      const std::pair<std::vector<std::vector<GLfloat>>,
                      std::vector<std::vector<GLint>>> &vertices,
      const std::pair<std::vector<std::vector<GLfloat>>,
                      std::vector<std::vector<GLint>>> &textures) noexcept;

private:
  /// @brief  Core функция отвечающая за сортировку всех значений координат
  /// ВЕРШИН И ТЕКСТУР в корректном порядке
  void Pack() noexcept override;
};

/// @brief Дочерний класс отвечающий за упаковку данных координат ВЕРШИН и
/// НОРМАЛЕЙ в соответствии с их индексами
class VertexNormalsCoordinatePacker : public CoordinatePacker {
public:
  /// @brief Конструктор с параметрами
  /// @param vertices Пара векторов векторов координат вершин и векторов
  /// векторов соответствующих индексов
  /// @param normals Пара векторов векторов координат нормалей и векторов
  /// векторов соответствующих индексов
  VertexNormalsCoordinatePacker(
      const std::pair<std::vector<std::vector<GLfloat>>,
                      std::vector<std::vector<GLint>>> &vertices,
      const std::pair<std::vector<std::vector<GLfloat>>,
                      std::vector<std::vector<GLint>>> &normals) noexcept;

private:
  /// @brief Core функция отвечающая за сортировку всех значений координат
  /// ВЕРШИН и НОРМАЛЕЙ в корректном порядке
  void Pack() noexcept override;
};

/// @brief Дочерний класс отвечающий за упаковку данных координат ВЕРШИН,
/// ТЕКСТУР и НОРМАЛЕЙ  в соответствии с их индексами
class VertexTexturesNormalsCoordinatePacker : public CoordinatePacker {
public:
  /// @brief Конструктор с параметрами
  /// @param vertices Пара векторов векторов координат вершин и векторов
  /// векторов соответствующих индексов
  /// @param textures Пара векторов векторов координат текстур и векторов
  /// векторов соответствующих индексов
  /// @param normals Пара векторов векторов координат нормалей и векторов
  /// векторов соответствующих индексов
  VertexTexturesNormalsCoordinatePacker(
      const std::pair<std::vector<std::vector<GLfloat>>,
                      std::vector<std::vector<GLint>>> &vertices,
      const std::pair<std::vector<std::vector<GLfloat>>,
                      std::vector<std::vector<GLint>>> &textures,
      const std::pair<std::vector<std::vector<GLfloat>>,
                      std::vector<std::vector<GLint>>> &normals) noexcept;

private:
  /// @brief Core функция отвечающая за сортировку всех значений координат
  /// ВЕРШИН, ТЕКСТУР и НОРМАЛЕЙ в корректном порядке
  void Pack() noexcept override;
};
} // namespace s21

#endif // CPP4_3DVIEWER_V2_MODEL_PARSER_PACKER_COORDINATE_PACKER_H