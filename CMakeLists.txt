cmake_minimum_required(VERSION 3.28)

# ---- Options ----
option(RUN_TESTS "Run tests if set to true" TRUE)


# Directory Names
set(DIR_GIT_MODULES "${CMAKE_CURRENT_SOURCE_DIR}/ExternalModules" )
set(DIR_UTILS "${CMAKE_CURRENT_SOURCE_DIR}/Utils")
set(DIR_FILE_SYS "${CMAKE_CURRENT_SOURCE_DIR}/FileSystem")
set(DIR_DATA_STRUCTURES "${CMAKE_CURRENT_SOURCE_DIR}/DataStructures")
set(DIR_STREAMERS "${CMAKE_CURRENT_SOURCE_DIR}/Streamers")
set(DIR_TESTS "${CMAKE_CURRENT_SOURCE_DIR}/Tests")
set(DIR_CLIBS "${DIR_GIT_MODULES}/Clibs" )

# Library Names
set(LIB_MEM_UTILS "MemUtils")
set(LIB_PRINT_UTILS "PrintUtils")

set(LIB_LISTS "List")
set(LIB_TRIE "Trie")
set(LIB_BUFFER "Buffer")
set(LIB_FIXED_SIZE_BUFFER "FixedSizeBuffer")
set(LIB_STACK "Stack")
set(LIB_QUEUE "Queue")
set(LIB_STRING_STREAMER "StringStreamer")
set(LIB_STREAMER "Streamer" )
set(LIB_STRING "String")

set(LIB_FILE "File")
set(LIB_DIRECTORY "Directory")

set(EXE_TESTS "All")

project("CLibrary"
    VERSION 1.0.0
    DESCRIPTION "C based helper data structures and algorithms"
    LANGUAGES C CXX
)

add_subdirectory(${DIR_UTILS})
add_subdirectory(${DIR_DATA_STRUCTURES})
add_subdirectory(${DIR_FILE_SYS})
add_subdirectory(${DIR_STREAMERS})
add_subdirectory(${DIR_TESTS})