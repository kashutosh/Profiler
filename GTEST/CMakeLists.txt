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
add_executable(  testscopeprofiler  TestScopeProfiler.cc ../scope.cc ../ObjectStorage.cc ../MyObject.cc ../Object.cc)
add_executable(  testobjectstorage TestObjectStorage.cc ../ObjectStorage.cc ../Object.cc)
add_executable(  testkeyvaluestore TestKeyValueStore.cc ../KeyValueStore.cc)
add_executable(  testhashtable TestHashtable.cc ../Instrument_Functions/hashtable.cc)
add_executable(  testlinkedlists TestLinkedListOfFrames.cc ../Instrument_Functions/LinkedListOfFrames.cc ../Instrument_Functions/Stack.cc ../Instrument_Functions/FunctionTracer.cc ../Instrument_Functions/hashtable.cc ../Instrument_Functions/Trace.cc ../Instrument_Functions/Aggregate_Stacks.cc)
add_executable(  testbenchmark TestBenchmark.cc ../Instrument_Functions/LinkedListOfFrames.cc ../Instrument_Functions/Stack.cc ../Instrument_Functions/FunctionTracer.cc ../Instrument_Functions/hashtable.cc ../Instrument_Functions/Trace.cc ../Instrument_Functions/Benchmark_Overhead.cc ../Instrument_Functions/Aggregate_Stacks.cc)
#add_executable(  testaggregator TestAggregator.cc ../Instrument_Functions/Aggregate_Stacks.cc)


target_link_libraries(hello gtest_main)
target_link_libraries(teststack gtest_main)
target_link_libraries(testscopeprofiler gtest_main)
target_link_libraries(testobjectstorage gtest_main)
target_link_libraries(testkeyvaluestore gtest_main)
target_link_libraries(testhashtable gtest_main)
target_link_libraries(testlinkedlists gtest_main dl )
target_link_libraries(testbenchmark gtest_main dl)
#target_link_libraries(testaggregator gtest_main)

include(GoogleTest)
gtest_discover_tests(hello)

