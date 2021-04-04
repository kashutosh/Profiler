cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


set(CMAKE_BINARY_DIR binary_tests/)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})



enable_testing()

add_executable(  hello  hello.cc ../mylib.cc)
add_executable(  teststack  TestStack.cc ../Instrument_Functions/Stack.cc)
add_executable(  testobjectstorage TestObjectStorage.cc ../ObjectStorage.cc ../Object.cc)
target_link_libraries(hello gtest_main)
target_link_libraries(teststack gtest_main)
target_link_libraries(testobjectstorage gtest_main)

include(GoogleTest)
gtest_discover_tests(hello)

