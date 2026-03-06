cmake_minimum_required(VERSION 3.28)

# ---- Options ----
option(RUN_TESTS "Run tests if set to true" TRUE)

# Directory Names
set(DIR_UTILS "${CMAKE_SOURCE_DIR}/Utils")
set(DIR_FILE_SYS "${CMAKE_SOURCE_DIR}/FileSystem")
set(DIR_DATA_STRUCTURES "${CMAKE_SOURCE_DIR}/DataStructures")
set(DIR_TESTS "${CMAKE_SOURCE_DIR}/Tests")

# Library Names
set(LIB_MEM_UTILS "MemUtils")
set(LIB_PRINT_UTILS "PrintUtils")

set(LIB_LISTS "List")
set(LIB_TRIE "Trie")
set(LIB_BUFFER "Buffer")
set(LIB_FIXED_SIZE_BUFFER "FixedSizeBuffer")

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
add_subdirectory(${DIR_TESTS})
