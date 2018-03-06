cmake_minimum_required(VERSION 3.10)

project(SerialPort)

set(CMAKE_BUILD_TYPE Release)
set(LIBRARY_OUTPUT_PATH ../lib/${CMAKE_BUILD_TYPE})

file(GLOB_RECURSE SOURCE src/*.cpp)
file(GLOB_RECURSE INCLUDE include/*.h)

include_directories("include")

add_library(${CMAKE_PROJECT_NAME} ${SOURCE} ${INCLUDE})
target_link_libraries(${CMAKE_PROJECT_NAME})
