cmake_minimum_required(VERSION 3.17)

project(SnailActions LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(RapidJSON)
find_package(fmt)

set(SnailActions_SRC
  src/main.cpp
  src/util.cpp
  src/util.h
  src/actionwidgets/slider.cpp
  src/actionwidgets/slider.h
  src/actionwidgets/actionwidget.cpp
  src/actionwidgets/actionwidget.h
  src/actionwidgets/button.cpp
  src/actionwidgets/button.h
  src/mainwindow.cpp
  src/mainwindow.h
  src/mainwindow.ui
  res/resource.qrc
)

if(ANDROID)
  add_library(snail-actions SHARED
    ${SnailActions_SRC}
  )
else()
  add_executable(snail-actions
    ${SnailActions_SRC}
  )
endif()

target_link_libraries(snail-actions PRIVATE Qt6::Widgets fmt)

install(TARGETS snail-actions)
