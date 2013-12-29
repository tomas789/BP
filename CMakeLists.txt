cmake_minimum_required(VERSION 2.8)

option(BUILD_WITH_TESTS "Build with tests." OFF)

project (GP)

# Set the build type if it isn't already
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -ggdb -Wall -std=c++0x -frtti")
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (GP_SOURCE
    src/Type.cpp
    src/Value.cpp
    src/Exception.cpp
  )

set (GP_TESTS 
    tests/Type.cpp
  )

if (BUILD_WITH_TESTS)
    if (EXISTS ${CMAKE_SOURCE_DIR}/gtest-1.7.0)
        set (GTEST_ROOT ${CMAKE_SOURCE_DIR}/gtest-1.7.0)
    endif ()

    if (DEFINED GTEST_ROOT)
        add_subdirectory (${GTEST_ROOT})

        enable_testing ()

        include_directories (${gtest_SOURCE_DIR}/include)
        link_directories (${gtest_BINARY_DIR})

        add_executable (gp-test ${GP_SOURCE} ${GP_TESTS})
        target_link_libraries (gp-test gtest gtest_main)
        add_test(NAME gp-main-tests COMMAND gp-test)
    else ()
        message (WARNING "GTest not found. Compiling without tests")
    endif ()
endif ()

include_directories (${CMAKE_SOURCE_DIR}/include)
 
add_executable (gp src/main.cpp ${GP_SOURCE})
