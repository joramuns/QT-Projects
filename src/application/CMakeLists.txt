cmake_minimum_required(VERSION 3.16)

project(3DViewer VERSION 2.0 LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra  -g")

message(STATUS "Project \"${PROJECT_NAME}\" compiled with C++ standard ${CMAKE_CXX_STANDARD}")

set(SOURCES
  main.cc
  view/view.cc
  view/transformwidgets/tbutton.cc
  view/transformwidgets/transform_buttons.cc
  view/transformwidgets/transform_tab.cc
  view/transformwidgets/scale_buttons.cc
  view/settingswidgets/settings.cc
  view/settingswidgets/settingstab.cc
  view/mainwidgets/app_management.cc
  controller/controller.cc

  model/object_model.cc
  model/parser/parser.cc
  model/parser/OBJ_Loader.h
  model/parser/indices_pars/faces_strategy.cc
  model/parser/packer/coordinate_packer.cc
  model/facade/facade.cc
  model/context/glwidget.cc
  model/context/gif.cc
  model/buffer/glbuffer.cc
  model/buffer/glbuffer2.cc
  model/buffer/transform_class.cc
  model/settings_singleton.cc
)

set(RESOURCES
  resources.qrc
)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets PrintSupport OpenGLWidgets)

add_executable(${PROJECT_NAME}
  ${SOURCES} ${RESOURCES}
)

target_link_libraries(3DViewer PRIVATE Qt6::Core Qt6::Widgets Qt6::OpenGLWidgets)

set_target_properties(3DViewer PROPERTIES
  MACOSX_BUNDLE ON)

