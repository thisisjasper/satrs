cmake_minimum_required(VERSION 3.20)

add_library(satrsLib STATIC)
target_include_directories(satrsLib PUBLIC ".")
target_sources(satrsLib PUBLIC
	"GameWindow.h"
	"SpriteShader.h"
	"Shader.h"
	"GameWindow.cc"
	"SpriteShader.cc"
	"Shader.cc"
)
target_link_libraries(satrsLib PUBLIC spdlog::spdlog)
target_link_libraries(satrsLib PUBLIC SDL2::SDL2)
