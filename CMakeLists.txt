project (gp)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -ggdb -Wall -std=c++11 -frtti")

set (GP_SOURCE
    src/main.cpp
    src/Type.cpp
    src/Value.cpp
    )

add_executable (gp ${GP_SOURCE})
