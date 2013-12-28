cmake_minimum_required(VERSION 2.8)

project (GP)
enable_testing()

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -ggdb -Wall -std=c++11 -frtti")
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (GP_SOURCE
    src/Type.cpp
    src/Value.cpp
    src/Exception.cpp
    )

set (GP_TESTS 
    tests/Type.cpp
    )


########################### GTEST
# Enable ExternalProject CMake module
INCLUDE(ExternalProject)
 
# Set default ExternalProject root directory
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/third_party)
 
# Add gtest
# http://stackoverflow.com/questions/9689183/cmake-googletest
ExternalProject_Add(
    googletest
    URL http://googletest.googlecode.com/files/gtest-1.7.0.zip
    # URL ${CMAKE_SOURCE_DIR}/gtest-1.7.0.zip
    # TIMEOUT 10
    # # Force separate output paths for debug and release builds to allow easy
    # # identification of correct lib in subsequent TARGET_LINK_LIBRARIES commands
    # CMAKE_ARGS -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
    #            -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
    #            -Dgtest_force_shared_crt=ON
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG:PATH=DebugLibs
               -DCMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE:PATH=ReleaseLibs
               -Dgtest_force_shared_crt=ON
    # Disable install step
    INSTALL_COMMAND ""
    # Wrap download, configure and build steps in a script to log output
    LOG_DOWNLOAD ON
    LOG_CONFIGURE ON
    LOG_BUILD ON)
 
# Specify include dir
ExternalProject_Get_Property(googletest source_dir)
set(GTEST_INCLUDE_DIR ${source_dir}/include)
 
# Library
ExternalProject_Get_Property (googletest binary_dir)
link_directories (${binary_dir})

include_directories (${GTEST_INCLUDE_DIR} ${GP_SOURCE_DIR}/include)

add_executable (gp-test ${GP_SOURCE} ${GP_TESTS})
add_dependencies (gp-test googletest)
target_link_libraries (gp-test gtest gtest_main)
add_test(NAME gp-main-tests COMMAND gp-test)

add_executable (gp src/main.cpp ${GP_SOURCE})
