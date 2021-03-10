cmake_minimum_required(VERSION 3.10)

project(libyardland-gui)

find_package(SDL2 REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_library(${PROJECT_NAME} 
    ${CMAKE_CURRENT_SOURCE_DIR}/libyardland/gui/gui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/libyardland/gui/texture.cpp
)

target_link_libraries(${PROJECT_NAME}
    ${SDL2MAIN_LIBRARY}
    ${SDL2_GFX_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    ${SDL2_LIBRARY}
)

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${SDL2_INCLUDE_DIR}
)
