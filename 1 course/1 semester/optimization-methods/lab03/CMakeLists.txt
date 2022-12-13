cmake_minimum_required(VERSION 3.5)

project(lab03 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab03 main.cpp)

install(TARGETS lab03
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
