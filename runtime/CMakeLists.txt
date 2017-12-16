add_custom_command(OUTPUT syn68k.c mapindex.c mapinfo.c profileinfo
    DEPENDS syngen syn68k_header.h 68k.scm 68k.defines.scm
    COMMAND ${CMAKE_COMMAND} -E copy 
        ${CMAKE_CURRENT_SOURCE_DIR}/68k.scm ${CMAKE_CURRENT_SOURCE_DIR}/syn68k_header.h ${CMAKE_CURRENT_SOURCE_DIR}/68k.defines.scm
        ./
    COMMAND syngen 68k.scm
    WORKING_DIRECTORY .
)

add_library(syn68k
    block.c diagnostics.c hash.c rangetree.c translate.c alloc.c
    blockinfo.c trap.c destroyblock.c callback.c init.c interrupt.c
    profile.c dosinterrupts.c deathqueue.c checksum.c native.c
    backpatch.c recompile.c
    mapindex.c mapinfo.c syn68k.c opcode_dummy.c

    syn68k_header.h
)

target_include_directories(syn68k PUBLIC include ../include ${CMAKE_BINARY_DIR})
target_compile_definitions(syn68k PRIVATE -DRUNTIME)
