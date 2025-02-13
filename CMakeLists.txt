cmake_minimum_required(VERSION 3.23)

set(project "lab2")
project(${project})

set(CMAKE_CXX_STANDARD 17)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/sunsys.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

set(${project}_SOURCES main.cpp)

add_subdirectory(planet)

set(${project}_SOURCE_LIST ${${project}_SOURCES})

add_executable(${project} ${${project}_SOURCE_LIST})

target_link_libraries(${project} planet)
