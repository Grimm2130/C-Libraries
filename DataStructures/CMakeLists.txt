add_library(${LIB_LISTS} STATIC List.c)
target_include_directories(${LIB_LISTS} BEFORE PRIVATE ${DIR_UTILS})
target_link_libraries(${LIB_LISTS} PRIVATE ${LIB_MEM_UTILS})

add_library(${LIB_TRIE} STATIC Trie.c)

add_library(${LIB_BUFFER} STATIC Buffer.c)
target_include_directories(${LIB_BUFFER} BEFORE PRIVATE ${DIR_UTILS})

add_library(${LIB_FIXED_SIZE_BUFFER} STATIC FixedSizeBuffer.c)
target_include_directories(${LIB_FIXED_SIZE_BUFFER} BEFORE PRIVATE ${DIR_UTILS})
target_link_libraries(${LIB_FIXED_SIZE_BUFFER} PRIVATE ${LIB_MEM_UTILS} ${LIB_PRINT_UTILS})
