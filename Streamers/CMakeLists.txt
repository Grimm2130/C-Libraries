add_library( ${LIB_STRING_STREAMER} STATIC StringStreamer.c )
target_include_directories( ${LIB_STRING_STREAMER} BEFORE PUBLIC ${DIR_DATA_STRUCTURES} ${DIR_UTILS} )
target_link_libraries( ${LIB_STRING_STREAMER} PUBLIC ${LIB_STACK} ${LIB_MEM_UTILS} )


add_library( ${LIB_STREAMER} STATIC Streamer.c )
target_link_libraries( ${LIB_STREAMER} PUBLIC ${LIB_STRING_STREAMER} )
# target_include_directories( ${LIB_STREAMER} BEFORE PUBLIC ${DIR_UTILS} )