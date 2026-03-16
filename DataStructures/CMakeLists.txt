add_library(${LIB_LISTS} STATIC List.c)
target_include_directories(${LIB_LISTS} BEFORE PUBLIC ${DIR_UTILS})
target_link_libraries(${LIB_LISTS} PUBLIC ${LIB_MEM_UTILS})

add_library(${LIB_TRIE} STATIC Trie.c)

add_library(${LIB_BUFFER} STATIC Buffer.c)
target_include_directories(${LIB_BUFFER} BEFORE PUBLIC ${DIR_UTILS})
target_link_libraries(${LIB_BUFFER} PUBLIC ${LIB_MEM_UTILS} ${LIB_PRINT_UTILS})

add_library(${LIB_FIXED_SIZE_BUFFER} STATIC FixedSizeBuffer.c)
target_include_directories(${LIB_FIXED_SIZE_BUFFER} BEFORE PUBLIC ${DIR_UTILS} )
target_link_libraries(${LIB_FIXED_SIZE_BUFFER} PUBLIC ${LIB_BUFFER} ${LIB_MEM_UTILS} ${LIB_PRINT_UTILS})

add_library(${LIB_STACK} STATIC Stack.c)
target_link_libraries(${LIB_STACK} PUBLIC ${LIB_FIXED_SIZE_BUFFER})

add_library(${LIB_QUEUE} STATIC Queue.c)
target_link_libraries(${LIB_QUEUE} PUBLIC ${LIB_FIXED_SIZE_BUFFER})

add_library(${LIB_STRING} STATIC String.c)
target_include_directories(${LIB_STRING} BEFORE PUBLIC ${DIR_UTILS} )
target_link_libraries(${LIB_STRING} PUBLIC ${LIB_FIXED_SIZE_BUFFER})
