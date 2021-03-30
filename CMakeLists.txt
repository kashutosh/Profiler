set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_FLAGS "-g -O3 -Wall -Wpedantic -rdynamic -ldl")

project (profiler)
add_executable (profiler scope.cc ObjectStorage.cc Object.cc MyObject.cc )
add_executable (backtracer ObjectStorage.cc Object.cc backtrace.cc )
