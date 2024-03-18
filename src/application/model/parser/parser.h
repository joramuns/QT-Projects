/*!
\file
\brief Заголовочный файл с описанием класса.

Данный файл содержит в себе определения класса парсера, считывающего и
сортирующего данные из файла obj формата, для работы с ними в  OpenGL
*/
#ifndef CPP4_3DVIEWER_V2_MODEL_PARSER_PARSER_H
#define CPP4_3DVIEWER_V2_MODEL_PARSER_PARSER_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif  // __APPLE__

#ifdef __linux__
#include <GL/glut.h>
#endif // __linux__

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>

#include "indices_pars/faces_strategy.h"
#include "packer/coordinate_packer.h"
#include "struct/coordinatestruct.h"

#define BAD_FILENAME 1

namespace s21 {
/// @brief Класс служит для считывания данных из файла формата obj
class Parser {
public:
  /// @brief Конструктор по умолчанию - удален
  Parser() = delete;

  /// @brief Конструктор с параметром
  /// @param filename Абсолютный путь к файлу формата obj
  explicit Parser(const std::string &filename);

  /// @brief Деструктор класса
  ~Parser();

  /// @brief Аксессор
  /// @return Вектор отсортированных данных для отрисовки 3-х мерной модели в
  /// OpenGL
  std::vector<std::vector<GLfloat>> GetCoordinates() const noexcept;

private:
  /// @brief Открывает файловый поток, считывает и сортирует данные из него
  /// @param filename Абсолютный путь к файлу формата obj
  /// @return Код выполения метода
  int ReadObj(const std::string &filename);

  /// @brief Заполняет all_vertices_ несоритрованными данными считанными из
  /// потока
  void AddPointInArray() noexcept;

  /// @brief Отчищает промежуточные буферы, служащие для заполнения при
  /// считывании
  void DataClear() noexcept;

  /// @brief Считывает данные координат вершин
  /// @param data Строковый поток данных
  void AddPoint(std::istringstream &data) noexcept;

  /// @brief Считывает данные координат текстур
  /// @param data Строковый поток данных
  void AddTexturePoint(std::istringstream &data) noexcept;

  /// @brief Считывает данные координат векторов нормалей
  /// @param data Строковый поток данных
  void AddNormalsPoint(std::istringstream &data) noexcept;

  /// @brief Назначает стратегию парсера для индексов
  /// @param file Файловый поток
  /// @param current_position Позиция в потоке с которой необходимо начать
  /// считывание
  void SetStrategy(std::ifstream *file, int current_position) noexcept;

  /// @brief Заполнение вектора неотсортированных данных из структуры
  /// заполненной данными из потока
  /// @param vertices_struct Структура координат вершин
  void StructFill(const PointCoordinates &vertices_struct) noexcept;

  /// @brief Заполнение вектора координат текстур неотсортированными данными из
  /// структуры заполненной данными из потока
  /// @param textures_struct Структура координат текстур
  void StructFill(const TexturesCoordinates &textures_struct) noexcept;

  /// @brief Заполнение вектора координат нормалей неотсортированными данными из
  /// структуры заполненной данными из потока
  /// @param normals_struct
  void StructFill(const NormalsCoordinate &normals_struct) noexcept;

  /// @brief Получение индексов координат
  void GetIndexes() noexcept;

  /// @brief Сортирует и упаковывает данные в один вектор для дальнейшей
  /// отрисовки 3-х мерной модели в OpenGL
  void Packer() noexcept;

  bool IsVertexData(const std::string &data) const noexcept;

  bool IsTexturesData(const std::string &data) const noexcept;

  bool IsNormalsData(const std::string &data) const noexcept;

  bool IsValidData() const noexcept; 

  void DebugPrint() noexcept;

private:
  /// @brief Вектор координат вершин для одного 3-х мерного объекта(возможна
  /// мультиобъектная модель)
  std::vector<GLfloat> vertex_points_;

  /// @brief Вектор координат текстур для одного 3-х мерного объекта(возможна
  /// мультиобъектная модель)
  std::vector<GLfloat> texture_points_;

  /// @brief Вектор координат нормалей для одного 3-х мерного объекта(возможна
  /// мультиобъектная модель)
  std::vector<GLfloat> normal_points_;

  /// @brief Вектор векторов всех координат вершин для 3-х мерной модели
  std::vector<std::vector<GLfloat>> all_vertices_;

  /// @brief Вектор векторов всех координат текстур для 3-х мерной модели
  std::vector<std::vector<GLfloat>> all_textures_;

  /// @brief Вектор векторов всех координат нормалей для 3-х мерной модели
  std::vector<std::vector<GLfloat>> all_normals_;

  /// @brief Вектор векторов индексов всех координат вершин для 3-х мерной
  /// модели
  std::vector<std::vector<GLint>> vertex_faces_;

  /// @brief Вектор векторов индексов всех координат текстур для 3-х мерной
  /// модели
  std::vector<std::vector<GLint>> texture_faces_;

  /// @brief Вектор векторов индексов всех координат нормалей для 3-х мерной
  /// модели
  std::vector<std::vector<GLint>> normal_faces_;

  /// @brief Отсортированный вектор всех координат для 3-х мерной модели
  std::vector<std::vector<GLfloat>> coordinates_;

  /// @brief Указатель на объект парсера индексов вершин
  FacesStrategy *faces_pars_;
};
} // namespace s21
#endif // CPP4_3DVIEWER_V2_MODEL_PARSER_PARSER_H
