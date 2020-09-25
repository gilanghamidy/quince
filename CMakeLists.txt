cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(libquince VERSION 0.1)

find_package(Boost 1.71.0 REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


add_library(quince SHARED)
target_include_directories(quince
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(quince
    boost_date_time
    boost_filesystem
    boost_thread
    pthread
)

target_compile_options(quince PRIVATE -Wall -Wextra -pedantic -Werror)
add_subdirectory (core)

## Make this conditionally enabled

find_library(SQLITE_LIB sqlite3)
if(NOT SQLITE_LIB)
  message(FATAL_ERROR "sqlite3 library not found")
endif()

add_library(quince-sqlite SHARED ${LIBQUINCE_SOURCES})
target_include_directories(quince-sqlite
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_include_directories(quince-sqlite
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(quince-sqlite quince sqlite3)

add_subdirectory (binding/sqlite)

add_library(quince-postgresql SHARED ${LIBQUINCE_SOURCES})
target_include_directories(quince-postgresql
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_include_directories(quince-postgresql
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(quince-postgresql quince pq)

add_subdirectory (binding/postgresql)
