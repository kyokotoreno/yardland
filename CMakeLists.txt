cmake_minimum_required(VERSION 3.16)

project(yardland VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

option(NO_GRAPHICAL_INTERFACE "Compile without any gui support." OFF)
option(NO_DOCS_GENERATION "Avoid compiling docs subdirectory." OFF)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)
include(CPM)

if(${NOGRAPHICALINTERFACE} EQUAL OFF)
    find_package(SDL2)
    find_package(SDL2_ttf)
    find_package(SDL2_gfx)

    CPMAddPackage("gh:H4ck-Software/libsdl2-gui@0.1.0-alpha.1")
else()
    add_compile_definitions(NO_GRAPHICAL_INTERFACE)
endif()

add_library( yardland
    ${PROJECT_SOURCE_DIR}/libyardland/mmu-tlb.cpp
    ${PROJECT_SOURCE_DIR}/libyardland/memory.tpp
)

if(${NO_GRAPHICAL_INTERFACE} EQUAL OFF)
    target_include_directories( yardland
        PUBLIC ${PROJECT_SOURCE_DIR}
        PRIVATE ${LIBSDL2-GUI_SOURCE_DIR}
        PRIVATE ${SDL2_INCLUDE_DIR}
    )
else()
    target_include_directories( yardland
        PUBLIC ${PROJECT_SOURCE_DIR}
    )
endif()

if (${NO_GRAPHICAL_INTERFACE} EQUAL OFF)
    target_link_libraries( yardland
        ${SDL2MAIN_LIBRARY}
        ${SDL2_GFX_LIBRARY}
        ${SDL2_TTF_LIBRARY}
        ${LIBSDL2-GUI_LIBRARY}
    )
endif()

if(${NO_DOCS_GENERATION} EQUAL OFF)
    add_subdirectory(docs)
endif()

# add_executable( yardland-exe
#     ${PROJECT_SOURCE_DIR}/yardland/mmio-6551.cpp
# )

# target_include_directories( yardland-exe
#     PUBLIC ${PROJECT_SOURCE_DIR}
# )

# target_link_libraries( yardland-exe
#     yardland
# )

enable_testing()

add_executable( yardland_test
    ${PROJECT_SOURCE_DIR}/yardland/mmio-6551.cpp
    ${PROJECT_SOURCE_DIR}/yardland/mmio-6551.test.cpp
)

target_include_directories( yardland_test
    PUBLIC ${PROJECT_SOURCE_DIR}
)

target_link_libraries( yardland_test
    gtest_main
)

gtest_discover_tests(yardland_test)
