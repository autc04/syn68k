add_executable(syngen
    main.c token.c hash.c parse.c list.c reduce.c macro.c
    boolean.c error.c defopcode.c bitstring.c generatecode.c
    uniquestring.c 	byteorder.c
    include/boolean.h include/error.h include/reduce.h include/parse.h
    include/bitstring.h include/uniquestring.h include/hash.h
    include/byteorder.h include/tokenlist.h include/common.h
    include/macro.h include/generatecode.h include/list.h include/token.h
    include/defopcode.h)

target_include_directories(syngen PUBLIC include ../include ${CMAKE_BINARY_DIR})
target_compile_definitions(syngen PRIVATE -DSYNGEN)
