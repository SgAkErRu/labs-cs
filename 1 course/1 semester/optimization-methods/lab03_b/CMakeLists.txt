cmake_minimum_required(VERSION 3.5)

project(lab03_b LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab03_b main.cpp)

install(TARGETS lab03_b
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
