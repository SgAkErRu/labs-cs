cmake_minimum_required(VERSION 3.5)

project(lab01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(lab01 main.cpp)

install(TARGETS lab01
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
