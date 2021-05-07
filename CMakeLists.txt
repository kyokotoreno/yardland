cmake_minimum_required(VERSION 3.16)

project(yardland VERSION 0.3.0 LANGUAGES CXX)

if(UNIX)
    add_compile_definitions(UNIX)
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
elseif(WIN32)
    add_compile_definitions(WIN32)
    if(MSVC)
        add_compile_definitions(MSVC)
    endif()
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules ${CMAKE_MODULE_PATH})

option(YARDLAND_BUILDDOCS "Compile documentation." OFF)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

enable_testing()

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_library( yardland STATIC

    # 65816 CPU

    ${PROJECT_SOURCE_DIR}/libyardland/cpu/mem816.cpp
    ${PROJECT_SOURCE_DIR}/libyardland/cpu/wdc816.cpp
    ${PROJECT_SOURCE_DIR}/libyardland/cpu/emu816.cpp

    # Zinc Video Adapter

    ${PROJECT_SOURCE_DIR}/libyardland/video/video.cpp

    # Zinc MMU

    ${PROJECT_SOURCE_DIR}/libyardland/zmmu/zmmu.cpp
    ${PROJECT_SOURCE_DIR}/libyardland/zmmu/zmmu-tlb.cpp

    # Memory

    ${PROJECT_SOURCE_DIR}/libyardland/memory/memory.cpp

    # Rom Loader

    ${PROJECT_SOURCE_DIR}/libyardland/rom-loader/rom-loader.cpp

    # FIFO Buffer

    ${PROJECT_SOURCE_DIR}/libyardland/buffers/fifo.cpp
)

target_include_directories( yardland
    PUBLIC ${PROJECT_SOURCE_DIR}
)

target_link_libraries( yardland
    SDL2::TTF
    SDL2::Core
)

add_library(yardland::libyardland ALIAS yardland)

add_executable( yardland-bin
    ${PROJECT_SOURCE_DIR}/yardland/main.cpp
)

# Set executable name

set_target_properties( yardland-bin PROPERTIES
    OUTPUT_NAME yardland
)

target_include_directories( yardland-bin
    PUBLIC ${PROJECT_SOURCE_DIR}
)

target_link_libraries( yardland-bin
    SDL2::Main
    yardland::libyardland
)

add_executable(yardland::yardland ALIAS yardland-bin)

##
## Compile Documentation
##

if(${YARDLAND_BUILDDOCS})
    add_subdirectory(docs)
endif()

##
## Tests
##

add_executable( yardland-tests

    # 65816 CPU

    ${PROJECT_SOURCE_DIR}/libyardland/cpu/cpu-65816.test.cpp

    # Rom Loader

    ${PROJECT_SOURCE_DIR}/libyardland/rom-loader/rom-loader.test.cpp
)

target_link_libraries( yardland-tests
    yardland::libyardland
    gtest_main
)

add_test(
    NAME yardland-tests
    COMMAND yardland-tests
)
