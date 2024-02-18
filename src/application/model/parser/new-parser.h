/*!
\file
\brief Заголовочный файл с описанием класса.

Данный файл содержит в себе определения класса парсера, считывающего и
сортирующего данные из файла obj формата, для работы с ними в  OpenGL
*/
#ifndef CPP4_3DVIEWER_V2_MODEL_PARSER_NEWPARSER_H
#define CPP4_3DVIEWER_V2_MODEL_PARSER_NEWPARSER_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#endif // __APPLE__

#ifdef __linux__
#include <GL/glut.h>
#endif // __linux__

#include <fstream>
#include <sstream>
#include <vector>
#include <string>

//for debug
#include <iostream>


namespace s21 {
class NewParser {
    public:

    explicit NewParser(const std::string &filename);

    ~NewParser();

    std::vector < std::vector<GLfloat> > GetCoordinates() const noexcept;

    private:

    bool IsCorrectFileFormat(const std::string &filename) const noexcept;
    bool IsFileExist(const std::string &filename) const noexcept;

    void DataRead(const std::string &filename) const noexcept;
};
} // namespace s21