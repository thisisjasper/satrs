cmake_minimum_required(VERSION 3.20)

add_library(satrs_lib STATIC)
target_include_directories(satrs_lib PUBLIC ".")
target_sources(satrs_lib PUBLIC
	GameWindow.cpp
)