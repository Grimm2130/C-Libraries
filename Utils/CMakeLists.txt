add_library( ${LIB_MEM_UTILS} STATIC MemUtils.c )
add_library( ${LIB_PRINT_UTILS} STATIC PrintUtils.c )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
