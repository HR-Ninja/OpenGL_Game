cmake_minimum_required(VERSION 3.15)

project(MyGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB SRC
    ${CMAKE_SOURCE_DIR}/*.cpp
    ${CMAKE_SOURCE_DIR}/*.c
    ${CMAKE_SOURCE_DIR}/Libaries/includes/glad/*.c
)

file(GLOB HEADERS
    ${CMAKE_SOURCE_DIR}/*.h
    ${CMAKE_SOURCE_DIR}/*.hpp
)

add_executable(${PROJECT_NAME}
    ${SRC}
    ${HEADERS}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/Libaries/includes
)

target_link_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_SOURCE_DIR}/Libaries/lib
)

target_link_libraries(${PROJECT_NAME}
    glfw3.lib
    opengl32.lib
)

source_group("headers" FILES HEADERS)
source_group("src" FILES SRC)