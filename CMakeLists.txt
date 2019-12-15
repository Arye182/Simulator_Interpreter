cmake_minimum_required(VERSION 3.15)
project(EX3_ME)

set(CMAKE_CXX_STANDARD 14)

add_executable(EX3_ME main.cpp interpreter.h interpreter.cpp var.cpp var.h command.h dataServer.cpp dataServer.h)