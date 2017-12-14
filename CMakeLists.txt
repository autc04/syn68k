cmake_minimum_required(VERSION 3.9)
project(Syn68K)

set(NONNATIVE "#define NONNATIVE")
configure_file(include/syn68k_private.h.in syn68k_private.h)
configure_file(include/config-cmake.h.in config.h)
include_directories(${CMAKE_CURRENT_DIRECTORY})

if(MSVC)
	add_definitions(-D_CRT_NONSTDC_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS
		/we4311 /we4312)
endif()

add_subdirectory(syngen)
add_subdirectory(runtime)