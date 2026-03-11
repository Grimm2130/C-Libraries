add_library( ${LIB_STRING_STREAMER} STATIC StringStreamer.c )
target_include_directories( ${LIB_STRING_STREAMER} BEFORE PRIVATE ${DIR_DATA_STRUCTURES} ${DIR_UTILS} )
target_link_libraries( ${LIB_STRING_STREAMER} PUBLIC ${LIB_MEM_UTILS} )


# add_library( ${LIB_DIRECTORY} STATIC Directory.c )
# target_include_directories( ${LIB_DIRECTORY} BEFORE PRIVATE ${DIR_UTILS} )
# target_link_libraries( ${LIB_DIRECTORY} PUBLIC ${LIB_MEM_UTILS} ${LIB_PRINT_UTILS} )