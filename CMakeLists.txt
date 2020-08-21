cmake_minimum_required(VERSION 3.17)

project(SnailActionsQt LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(RapidJSON)
find_package(fmt)

set(SnailActions_SRC
  main.cpp
  util.cpp
  util.h
  slider.cpp
  slider.h
  action.cpp
  action.h
  button.cpp
  button.h
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  res/resource.qrc
)

if(ANDROID)
  add_library(SnailActions SHARED
    ${SnailActions_SRC}
  )
else()
  add_executable(SnailActions
    ${SnailActions_SRC}
  )
endif()

target_link_libraries(SnailActions PRIVATE Qt5::Widgets fmt)
