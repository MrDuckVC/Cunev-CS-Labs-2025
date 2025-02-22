cmake_minimum_required(VERSION 3.20)

project(lab3)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fraction.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/fraction.h
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES} ${HEADERS})

if(ENABLE_DEBUG)
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -g)
endif()
