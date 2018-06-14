# cmake minimal version
cmake_minimum_required(VERSION 2.6)

# add testing
enable_testing()

# project declaration
project(TestZappyServer)

if (APPLE AND EXISTS /goinfre)

include_directories(
    $ENV{HOME}/.brew/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

link_directories(
    $ENV{HOME}/.brew/lib
    )

else (APPLE AND EXISTS /goinfre)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../src
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    )

endif (APPLE AND EXISTS /goinfre)


# sources list
file(
    GLOB_RECURSE
    sources_files
    src/*
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.c
    )

list(
    REMOVE_ITEM
    sources_files
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/serveur.c
    )

list(
    APPEND
    CMAKE_C_FLAGS
    "-Wall -Werror -Wextra ${CMAKE_C_FLAGS}"
    )

add_executable(
    test_zappy_server
    ${sources_files}
    )

#Configuration de l'édition de liens
if (APPLE)

target_link_libraries(
    test_zappy_server
    check
    )

else (APPLE)

target_link_libraries(
    test_zappy_server
    check
    m
    rt
    pthread
    )

endif (APPLE)

add_test(
    test_zappy_server_functions
    ${CMAKE_CURRENT_BINARY_DIR}/test_zappy_server
    )

add_test(
    test_zappy_server_binary
    ${CMAKE_CURRENT_BINARY_DIR}/test_zappy_server.sh
    )
