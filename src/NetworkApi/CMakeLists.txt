cmake_minimum_required(VERSION 3.23)
project(NetworkApi)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC NetworkApi.cpp NetworkApi.h)

target_link_libraries(${PROJECT_NAME} PUBLIC restclient-cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})