cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(satrs
	VERSION 0.1
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(satrs src/main.cpp "src/GameWindow.h" "src/GameWindow.cpp")

add_subdirectory(src)

target_link_libraries(satrs PUBLIC satrs_lib)
target_link_libraries(satrs PUBLIC SDL2::SDL2)
target_link_libraries(satrs PUBLIC SDL2::SDL2main)

# cmake bruh