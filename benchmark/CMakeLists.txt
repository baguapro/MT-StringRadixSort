cmake_minimum_required(VERSION 3.10)
project(RadixSort)

set(CMAKE_CXX_STANDARD 17)

# Download and unpack googlebenchmark at configure time
configure_file(CMakeLists.txt.in googlebenchmark-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googlebenchmark-download )
if(result)
  message(FATAL_ERROR "CMake step for googlebenchmark failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googlebenchmark-download )
if(result)
  message(FATAL_ERROR "Build step for googlebenchmark failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF CACHE BOOL "Disable Google Test in benchmark" FORCE)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "Disable Google Test in benchmark" FORCE)
set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type Release" FORCE)

# Add googlebenchmark directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googlebenchmark-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googlebenchmark-build
                 EXCLUDE_FROM_ALL)

include_directories(${CMAKE_SOURCE_DIR}/../src)

file(GLOB benchmark_sources ./*.cpp)

add_executable(RadixSortBenchmarkNoOpt ${benchmark_sources})
target_link_libraries(RadixSortBenchmarkNoOpt benchmark pthread)
set_target_properties(RadixSortBenchmarkNoOpt PROPERTIES COMPILE_FLAGS "-O0")

add_executable(RadixSortBenchmarkO1 ${benchmark_sources})
target_link_libraries(RadixSortBenchmarkO1 benchmark pthread)
set_target_properties(RadixSortBenchmarkO1 PROPERTIES COMPILE_FLAGS "-O1")

add_executable(RadixSortBenchmarkO2 ${benchmark_sources})
target_link_libraries(RadixSortBenchmarkO2 benchmark pthread)
set_target_properties(RadixSortBenchmarkO2 PROPERTIES COMPILE_FLAGS "-O2")

add_executable(RadixSortBenchmarkOs ${benchmark_sources})
target_link_libraries(RadixSortBenchmarkOs benchmark pthread)
set_target_properties(RadixSortBenchmarkOs PROPERTIES COMPILE_FLAGS "-Os")

add_custom_target(run_benchmarks
    COMMAND RadixSortBenchmarkNoOpt
    COMMAND RadixSortBenchmarkO1
    COMMAND RadixSortBenchmarkO2
    COMMAND RadixSortBenchmarkOs
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running unit benchmarks..."
    SOURCES ${benchmark_sources}
)
