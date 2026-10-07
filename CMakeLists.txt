cmake_minimum_required(VERSION 3.20)

project(ass2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ass2
        src/image.cpp
        include/ImageTransformation.h
        src/ImageTransformation.cpp
        src/ImageTransfromation_test.cpp
)

target_include_directories(ass2 PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)