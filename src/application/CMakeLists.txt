cmake_minimum_required(VERSION 3.16)

project(3DViewer VERSION 2.0 LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Werror -Wextra)
add_link_options(-Wall -Werror -Wextra)

message(STATUS "Project \"${PROJECT_NAME}\" compiled with C++ standard ${CMAKE_CXX_STANDARD}")

set(COMMON_SOURCES
  main.cc
  view/view.cc
  view/transform_buttons.cc
  view/settings.cc
  view/app_management.cc
  view/opengl/glwidget.cc
)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets PrintSupport OpenGLWidgets)

qt_add_executable(3DViewer
  ${COMMON_SOURCES}
)

target_link_libraries(3DViewer PRIVATE Qt6::Core Qt6::Widgets Qt6::OpenGLWidgets)

set_target_properties(3DViewer PROPERTIES
  MACOSX_BUNDLE ON)

