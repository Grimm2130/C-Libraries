# cmake_minimum_required( VERSION 3.28 )

# project( Tests )

# set( SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
# set( BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}")

# message("Binary Dir: ${CMAKE_CURRENT_BINARY_DIR}")
# message("Source Dir: ${CMAKE_CURRENT_SOURCE_DIR}")

# # Set variable names for libraries and Executables
# set( LIB_MEM_UTILS "MemUtils" )
# set( LIB_PRINT_UTILS "PrintUtils" )
# set( LIB_LIST "List" )
# set( LIB_TRIE "Trie" )
# set( LIB_CMD "Command" )

# # Set variable names for paths
# set( PATH_UTILS "${SRC_DIR}/../Utils")
# set( PATH_GEN_LIBS "${SRC_DIR}/..")

# # Process Sub Dirs
# add_subdirectory( ${PATH_UTILS} "${BIN_DIR}/Utils" )
# add_subdirectory( ${PATH_GEN_LIBS} "${BIN_DIR}/Gen" )

# # Generate Utils Library list
# file( GLOB UTILS "${LIB_MEM_UTILS};${LIB_PRINT_UTILS}" )

# Generate final exe
add_executable(${EXE_TESTS} Test.c)
target_include_directories(${EXE_TESTS} PUBLIC ${DIR_UTILS} ${DIR_DATA_STRUCTURES} ${DIR_FILE_SYS} ${DIR_STREAMERS} )
target_link_libraries(${EXE_TESTS} PRIVATE
    ${LIB_MEM_UTILS}
    ${LIB_PRINT_UTILS}
    ${LIB_BUFFER}
    ${LIB_FIXED_SIZE_BUFFER}
    ${LIB_STACK}
    ${LIB_QUEUE}
    ${LIB_STRING_STREAMER}
    ${LIB_LISTS}
    ${LIB_TRIE}
    ${LIB_FILE}
    ${LIB_DIRECTORY}
    ${LIB_STRING}
)

if(RUN_TESTS)
    message("Running Tests in ./${CMAKE_BINARY_DIR}/Tests/${EXE_TESTS}....")

    # execute_process(
    # COMMAND "./${CMAKE_BINARY_DIR}/Tests/${EXE_TESTS}"
    # WORKING_DIRECTORY .
    # RESULT_VARIABLE RES
    # )
    add_custom_command(TARGET ${EXE_TESTS} POST_BUILD
        COMMAND $<TARGET_FILE:${EXE_TESTS}>
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    )
endif(RUN_TESTS)