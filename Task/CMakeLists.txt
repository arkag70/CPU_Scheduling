cmake_minimum_required(VERSION 3.16)

include_directories(inc)
file(GLOB SOURCES "src/*.cpp")
add_executable(task ${SOURCES})