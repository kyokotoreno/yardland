cmake_minimum_required(VERSION 3.10)

# set the project name
project(yardland)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "C:/mingw-w64/mingw64/cmake/")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(libyardland)
add_subdirectory(libyardland-gui)
# add_subdirectory(libyardland-wrapper)
add_subdirectory(doc)
