cmake_minimum_required(VERSION 3.16)

project(yardland VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

option(NO_GRAPHICAL_INTERFACE "Compile without any gui support." OFF)
option(NO_DOCS_GENERATION "Avoid compiling docs subdirectory." OFF)

include(CPM)

if(${NO_GRAPHICAL_INTERFACE} EQUAL OFF)
    find_package(SDL2)
    find_package(SDL2_ttf)
    find_package(SDL2_gfx)

    CPMAddPackage("gh:H4ck-Software/libsdl2-gui#main@0.1.0-alpha.1")
else()
    add_compile_definitions(NO_GRAPHICAL_INTERFACE)
endif()

add_library( yardland SHARED
    ${PROJECT_SOURCE_DIR}/libyardland/mmu-tlb.cpp
    ${PROJECT_SOURCE_DIR}/libyardland/memory.tpp
)

add_library(yardland::libyardland ALIAS yardland)

if(${NO_GRAPHICAL_INTERFACE} EQUAL OFF)
    target_include_directories( yardland
        PUBLIC ${PROJECT_SOURCE_DIR}
        PRIVATE ${SDL2-GUI_INCLUDE_DIR}
        PRIVATE ${SDL2_INCLUDE_DIR}
    )
else()
    target_include_directories( yardland
        PUBLIC ${PROJECT_SOURCE_DIR}
    )
endif()

if (${NO_GRAPHICAL_INTERFACE} EQUAL OFF)
    target_link_libraries( yardland
        SDL2::GFX
        SDL2::TTF
        SDL2::GUI
        SDL2::Core
    )
endif()

if(${NO_DOCS_GENERATION} EQUAL OFF)
    add_subdirectory(docs)
endif()

add_executable( yardland-bin
    ${PROJECT_SOURCE_DIR}/yardland/main.cpp
)

set_target_properties( yardland-bin PROPERTIES
    OUTPUT_NAME yardland
)

add_executable( yardland::yardland ALIAS yardland-bin)

target_include_directories( yardland-bin
    PUBLIC ${PROJECT_SOURCE_DIR}
)

if (${NO_GRAPHICAL_INTERFACE} EQUAL OFF)
    target_link_libraries( yardland-bin
        SDL2::Main
        yardland::libyardland
    )
else()
    target_link_libraries( yardland-bin
        yardland::libyardland
    )
endif()
