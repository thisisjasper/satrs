cmake_minimum_required(VERSION 3.20)
# Many taken from EndlessSky CMake stuff

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
project(satrs
	VERSION 0.1
)

# Find dependencies
find_package(SDL2 REQUIRED)
find_package(spdlog REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Add lib target representing game
add_subdirectory(src)

# Interface library containing external dependencies
add_library(externalLibraries INTERFACE)
target_link_libraries(satrsLib PUBLIC externalLibraries)

# Link general dependencies
target_link_libraries(externalLibraries INTERFACE SDL2::SDL2 spdlog::spdlog)

# Create satrs target
add_executable(satrs src/main.cc)

# Link game target with libraries
target_link_libraries(satrs PRIVATE externalLibraries satrsLib SDL2::SDL2main)