cmake_minimum_required(VERSION 3.16)

project(Calculator VERSION 2.0 LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_add_executable(Calculator
  main.cc
  view/calcwindow.cc
  controller/controller.cc
  model/model.cc
  model/element.cc
  model/infix.cc
  model/postfix.cc
)

target_link_libraries(Calculator PRIVATE Qt6::Core Qt6::Widgets)

set_target_properties(Calculator PROPERTIES
  MACOSX_BUNDLE ON)
