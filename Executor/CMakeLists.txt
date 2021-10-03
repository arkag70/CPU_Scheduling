cmake_minimum_required(VERSION 3.16)

include_directories(inc)
include_directories(${CMAKE_SOURCE_DIR}/Task/inc)
file(GLOB SOURCES "src/*.cpp")
add_executable(executor ${SOURCES})
target_link_libraries(executor pthread)