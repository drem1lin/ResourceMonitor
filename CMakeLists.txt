cmake_minimum_required(VERSION 3.16)
project(monitor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_subdirectory(core)
#add_subdirectory(platform)
add_subdirectory(monitord)
#add_subdirectory(cli)
add_subdirectory(tests)
