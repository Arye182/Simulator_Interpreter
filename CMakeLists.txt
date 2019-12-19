cmake_minimum_required(VERSION 3.15)
project(Simulator_Interpreter)

set(CMAKE_CXX_STANDARD 14)

add_executable(Simulator_Interpreter main.cpp Interpreter.h Interpreter.cpp
        Command.h OpenDataServerCommand.cpp OpenDataServerCommand.h
        ConnectCommand.cpp ConnectCommand.h data_server_tester.cpp
        Expression.h DataBase.cpp DataBase.h Lexer.cpp Lexer.h RunProgramm.cpp RunProgramm.h)