#include "parser.h"
#include <iostream>
const std::string kPath = "/home/mammiemi/Desktop/Project/CPP4_3DViewer_v2.0-2/data-samples/";

int main(){
    // std::cout << "kek\n";
    s21::Parser test(kPath + "empty.obj");
    s21::Parser test_two(kPath + "empty_vertex.obj");
    s21::Parser lol(kPath + "empty_textures.obj");
    // s21::Parser kek(kPath + "empty_normals.obj");
    // s21::Parser test_ver(kPath + "test_vertex.obj");
    // for (const auto b : test_ver.GetCoordinates()) {
    //     for (const auto d : b) {
    //         std::cout << d << " ";
    //     }
    // }
    // s21::Parser beb(kPath + "empty_inidices.obj");
    return 0;
}