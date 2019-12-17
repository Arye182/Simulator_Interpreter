cmake_minimum_required(VERSION 3.15)
project(EX3_ME)

set(CMAKE_CXX_STANDARD 14)

add_executable(EX3_ME main.cpp interpreter.h interpreter.cpp var.cpp var.h
        Command.h OpenDataServerCommand.cpp OpenDataServerCommand.h
        ConnectCommand.cpp ConnectCommand.h data_server_tester.cpp
        Expression.h MathInterpreter.cpp MathInterpreter.h)