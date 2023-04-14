cmake_minimum_required(VERSION 3.23)
project(App)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC App.cpp App.h)

target_link_libraries(${PROJECT_NAME} PRIVATE cxxopts)
target_link_libraries(${PROJECT_NAME} PRIVATE metadata)
target_link_libraries(${PROJECT_NAME} PRIVATE Utils)
target_link_libraries(${PROJECT_NAME} PRIVATE tomlplusplus_tomlplusplus)
target_link_libraries(${PROJECT_NAME} PRIVATE filereader)
target_link_libraries(${PROJECT_NAME} PRIVATE NetworkApi)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})