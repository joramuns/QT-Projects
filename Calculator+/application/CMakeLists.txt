cmake_minimum_required(VERSION 3.16)

project(Calculator VERSION 2.0 LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(STATUS "Project \"${PROJECT_NAME}\" compiled with C++ standard ${CMAKE_CXX_STANDARD}")

set(COMMON_SOURCES
  application/main.cc
  application/view/calcwindow.cc
  application/view/operatorbutton.cc
  application/view/creditwindow.cc
  application/view/depositwindow.cc
  application/controller/controller.cc
  application/model/model.cc
  application/model/element.cc
  application/model/infix.cc
  application/model/postfix.cc
  application/model/credit.cc
  application/model/deposit.cc
)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets PrintSupport)

qt_add_library(QCustomPlot SHARED
  application/libs/qcustomplot/qcustomplot.cc
)
target_link_libraries(QCustomPlot PUBLIC Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(QCustomPlot PUBLIC Qt${QT_VERSION_MAJOR}::PrintSupport)
# Compile needed definitions
target_compile_definitions(QCustomPlot PRIVATE QCUSTOMPLOT_COMPILE_LIBRARY)

qt_add_executable(Calculator
  ${COMMON_SOURCES}
)

# qt_add_executable(asan
#   ${COMMON_SOURCES}
# )

# target_compile_options(asan PRIVATE -fsanitize=address)
# target_link_options(asan PRIVATE -fsanitize=address)

target_link_libraries(Calculator PRIVATE Qt6::Core Qt6::Widgets)
target_link_libraries(Calculator PRIVATE QCustomPlot)
# target_link_libraries(asan PRIVATE Qt6::Core Qt6::Widgets)

set_target_properties(Calculator PROPERTIES
  MACOSX_BUNDLE ON)
