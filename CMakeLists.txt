# Command For VERBOSE build
# cmake --build . -- VERBOSE=1 

cmake_minimum_required(VERSION 3.8.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(VERSION 0.2)

# C++ won't work on below line
set(LANGUAGES CXX)
set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_C++_COMPILER /usr/bin/g++)
set(CMAKE_BUILD_TYPE Release)
enable_language( C CXX )

set(CMAKE_BINARY_DIR target/)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

SET(CMAKE_CXX_FLAGS "-g -O3 -Wall -Wpedantic -rdynamic -ldl")

project (profiler LANGUAGES ${LANGUAGES} VERSION ${VERSION})
add_executable (scopeprofiler scope.cc scope_main.cc ObjectStorage.cc Object.cc MyObject.cc )
add_executable (backtracer backtrace.cc backtrace_main.cc ObjectStorage.cc Object.cc )

#add_library (objects SHARED Object.cc ObjectStorage.cc)
