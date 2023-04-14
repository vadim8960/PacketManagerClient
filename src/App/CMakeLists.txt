cmake_minimum_required(VERSION 3.23)
project(App)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC App.cpp App.h)

target_link_libraries(${PROJECT_NAME} PUBLIC cxxopts)
target_link_libraries(${PROJECT_NAME} PUBLIC metadata)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})