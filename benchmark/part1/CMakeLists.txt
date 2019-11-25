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

include_directories(${CMAKE_SOURCE_DIR}/../../src)
include_directories(${CMAKE_SOURCE_DIR}/../..)

add_executable(VolumeBenchmark VolumeBenchmark.cpp)
target_link_libraries(VolumeBenchmark benchmark pthread)
set_target_properties(VolumeBenchmark PROPERTIES COMPILE_FLAGS "-O0")

add_executable(WordLengthBenchmark WordLengthBenchmark.cpp)
target_link_libraries(WordLengthBenchmark benchmark pthread)
set_target_properties(WordLengthBenchmark PROPERTIES COMPILE_FLAGS "-O0")

add_executable(VolumeBenchmark02 VolumeBenchmark.cpp)
target_link_libraries(VolumeBenchmark02 benchmark pthread)
set_target_properties(VolumeBenchmark02 PROPERTIES COMPILE_FLAGS "-O2")

add_executable(WordLengthBenchmark02 WordLengthBenchmark.cpp)
target_link_libraries(WordLengthBenchmark02 benchmark pthread)
set_target_properties(WordLengthBenchmark02 PROPERTIES COMPILE_FLAGS "-O2")

add_custom_target(run_benchmarks
    COMMAND VolumeBenchmark
    COMMAND VolumeBenchmark02
    COMMAND WordLengthBenchmark
    COMMAND WordLengthBenchmark02
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Running unit benchmarks..."
    SOURCES ${benchmark_sources}
)
