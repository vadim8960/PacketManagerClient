cmake_minimum_required(VERSION 3.23)
project(PacketManagerClient)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs)
add_subdirectory(src)

find_package(jsoncpp REQUIRED)
find_package(ZLIB REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC cxxopts)
target_link_libraries(${PROJECT_NAME} PUBLIC App)
target_link_libraries(${PROJECT_NAME} PUBLIC NetworkApi)
target_link_libraries(${PROJECT_NAME} PUBLIC ZLIB::ZLIB)