cmake_minimum_required(VERSION 3.10)

project(libyardland)

add_library(${PROJECT_NAME} 
    ${CMAKE_CURRENT_SOURCE_DIR}/libyardland/hardware/ioDevice.cpp
)

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
