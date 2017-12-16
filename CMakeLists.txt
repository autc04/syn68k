cmake_minimum_required(VERSION 3.9)
project(Syn68K)

set(NONNATIVE "#define NONNATIVE")
include_directories(${CMAKE_CURRENT_DIRECTORY})

if(MSVC)
	add_definitions(-D_CRT_NONSTDC_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS
		/we4311 /we4312)
endif()

add_library(syn68k-common INTERFACE)
target_include_directories(syn68k-common INTERFACE include)

add_custom_target(syn68k-common-headers SOURCES
    include/syn68k_private.h
    include/syn68k_public.h include/safe_alloca.h)

set(SYN68K_CONFIG_FLAGS -DNONNATIVE -DNONDIRECT)

add_subdirectory(syngen)
add_subdirectory(runtime)


