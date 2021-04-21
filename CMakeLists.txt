cmake_minimum_required(VERSION 3.16)

project(yardland VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

option(YARDLAND_GFXSUPPORT "Compile with Graphics support (Requires SDL2, SDL2_gfx, SDL2_ttf and libsdl2-gui)." ON)
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

include(CPM)

if(UNIX)
    add_compile_definitions(UNIX)
endif()

if(${YARDLAND_GFXSUPPORT})
    find_package(SDL2 REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(SDL2_gfx REQUIRED)

    CPMAddPackage("gh:H4ck-Software/libsdl2-gui#main@0.1.0")
endif()

add_library( yardland SHARED
    #${PROJECT_SOURCE_DIR}/libyardland/cpu/cpu-65816.cpp
    ${PROJECT_SOURCE_DIR}/libyardland/video/video.cpp
    #${PROJECT_SOURCE_DIR}/libyardland/mmio/mmio-6551.cpp
    #${PROJECT_SOURCE_DIR}/libyardland/mmu/mmu-tlb.cpp
    ${PROJECT_SOURCE_DIR}/libyardland/memory/memory.tpp
    ${PROJECT_SOURCE_DIR}/libyardland/binary-file/binary-file.cpp
    #${PROJECT_SOURCE_DIR}/libyardland/utils/buffers/fifo.cpp
)

target_include_directories( yardland
    PUBLIC ${PROJECT_SOURCE_DIR}
)

target_link_libraries( yardland
    SDL2::GFX
    SDL2::TTF
    #SDL2::GUI
    SDL2::Core
)

add_library(yardland::libyardland ALIAS yardland)

add_executable( yardland-bin
    ${PROJECT_SOURCE_DIR}/yardland/main.cpp
)

# Set executable name

if(WIN32)
    set_target_properties( yardland-bin PROPERTIES
        OUTPUT_NAME yardland.exe
    )
else()
    set_target_properties( yardland-bin PROPERTIES
        OUTPUT_NAME yardland
    )
endif()

target_include_directories( yardland-bin
    PUBLIC ${PROJECT_SOURCE_DIR}
)

target_link_libraries( yardland-bin
    SDL2::Main
    yardland::libyardland
)

add_executable( yardland::yardland ALIAS yardland-bin)

##
## Tests
##

add_executable( yardland-tests
    ${PROJECT_SOURCE_DIR}/libyardland/cpu/cpu-65816.test.cpp
    #${PROJECT_SOURCE_DIR}/libyardland/mmio/mmio-6551.test.cpp
    ${PROJECT_SOURCE_DIR}/libyardland/binary-file/binary-file.test.cpp
)

target_link_libraries( yardland-tests
    yardland::libyardland
    gtest_main
)

add_test(
    NAME yardland-tests
    COMMAND yardland-tests
)

##
## Compile Documentation
##

if(${YARDLAND_BUILDDOCS})
    add_subdirectory(docs)
endif()
