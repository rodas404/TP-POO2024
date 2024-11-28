cmake_minimum_required(VERSION 3.30)
project(projeto)

set(CMAKE_CXX_STANDARD 20)

add_executable(projeto main.cpp
        Buffer/Buffer.cpp
        Buffer/Buffer.h
        Buffer/Cursor.cpp
        Buffer/Cursor.h)
