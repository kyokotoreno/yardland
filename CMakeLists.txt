cmake_minimum_required(VERSION 3.16)

project(yardland VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

include(GoogleTest)
include(CPM)

find_package(SDL2)
find_package(SDL2_ttf)
find_package(SDL2_gfx)

CPMAddPackage(
    NAME libsdl2-gui
    VERSION 0.1.0
    GIT_TAG main
    GITHUB_REPOSITORY H4ck-Software/libsdl2-gui
)

add_library( yardland
    ${PROJECT_SOURCE_DIR}/libyardland/mmu-tlb.cpp
)

target_include_directories( yardland
    PUBLIC ${PROJECT_SOURCE_DIR}
    PRIVATE ${LIBSDL2-GUI_SOURCE_DIR}
    PRIVATE ${SDL2_INCLUDE_DIR}
)

target_link_libraries( yardland
    ${SDL2MAIN_LIBRARY}
    ${SDL2_GFX_LIBRARY}
    ${SDL2_TTF_LIBRARY}
    ${LIBSDL2-GUI_LIBRARY}
)

add_subdirectory(docs)
