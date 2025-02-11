cmake_minimum_required(VERSION 3.23)

set(project "myalphabet")
project(${project})

set(CMAKE_CXX_STANDARD 17)

set(${project}_SOURCES
    myalphabet.cpp)

set(${project}_HEADERS
    myalphabet.h)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES}
        ${${project}_HEADERS})

add_library(${project}
        STATIC
        ${${project}_SOURCE_LIST})
