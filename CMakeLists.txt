cmake_minimum_required(VERSION 3.9)
project(Syn68K)

set(SYN68K_NONDIRECT ON CACHE BOOL "Use standard switch instead of computed goto - saves compile time with clang")

include_directories(${CMAKE_CURRENT_DIRECTORY})

if(MSVC)
	add_definitions(-D_CRT_NONSTDC_NO_WARNINGS -D_CRT_SECURE_NO_WARNINGS
		/we4311 /we4312)
endif()

option(TWENTYFOUR "Use twenty-four bit addressing")

add_library(syn68k-common INTERFACE)
target_include_directories(syn68k-common INTERFACE include)

if(TWENTYFOUR)
	target_compile_definitions(syn68k-common INTERFACE TWENTYFOUR_BIT_ADDRESSING)
endif()

add_custom_target(syn68k-common-headers SOURCES
    include/syn68k_private.h
    include/syn68k_public.h include/safe_alloca.h)

set(SYN68K_CONFIG_FLAGS NONNATIVE $<$<BOOL:${SYN68K_NONDIRECT}>:NONDIRECT>)

add_subdirectory(syngen)
add_subdirectory(runtime)


