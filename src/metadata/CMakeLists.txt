cmake_minimum_required(VERSION 3.23)
project(metadata)

configure_file(config.h.in ${CMAKE_CURRENT_BINARY_DIR}/config.h)
include_directories(${PROJECT_BINARY_BIN})

add_library(${PROJECT_NAME} STATIC version.cpp version.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
