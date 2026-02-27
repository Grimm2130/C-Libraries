add_library( ${LIB_FILE} STATIC File.c )
target_include_directories( ${LIB_FILE} BEFORE PRIVATE ${DIR_UTILS} )
target_link_libraries( ${LIB_FILE} PUBLIC ${LIB_MEM_UTILS} )


add_library( ${LIB_DIRECTORY} STATIC Directory.c )
target_include_directories( ${LIB_DIRECTORY} BEFORE PRIVATE ${DIR_UTILS} )
target_link_libraries( ${LIB_DIRECTORY} PUBLIC ${LIB_MEM_UTILS} ${LIB_PRINT_UTILS} )