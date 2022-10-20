cmake_minimum_required(VERSION 3.23)
project(Project_2)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(Project_2
        execute.cc
        execute.h
        inputbuf.cc
        inputbuf.h
        lexer.cc
        lexer.h
        project2.cc
        tasks.cc
        tasks.h)
