cmake_minimum_required(VERSION 3.23)
project(NetworkApi)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC NetworkApi.cpp NetworkApi.h)

target_link_libraries(${PROJECT_NAME} PRIVATE restclient-cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE base64)
target_link_libraries(${PROJECT_NAME} PUBLIC jsoncpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})