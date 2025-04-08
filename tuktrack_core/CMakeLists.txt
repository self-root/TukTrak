cmake_minimum_required(VERSION 3.16)

project(tuktrack_core LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(tuktrack_core SHARED
  tuktrack_core_global.h
  corecontroller.cpp
  corecontroller.h
)

target_include_directories(tuktrack_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(tuktrack_core PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(tuktrack_core PRIVATE TUKTRACK_CORE_LIBRARY)
