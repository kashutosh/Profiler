set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (profiler)
add_executable (profiler scope.cc ObjectStorage.cc Object.cc)
