//
// Created by arye on 19/12/2019.
//

#ifndef SIMULATOR_INTERPRETER__RUNPROGRAMM_H_
#define SIMULATOR_INTERPRETER__RUNPROGRAMM_H_

#include <iostream>
#include "Interpreter.h"
#include "OpenDataServerCommand.h"
#include "Lexer.h"
//#include "DataBase.h"
#include <vector>


class RunProgramm {
 private:
  string file_name;
  //DataBase data_base;
 public:
  RunProgramm(string file);
  /**
 * Run the program
 * activates the lexer, and parser (interpreter class) the parser runs
 * the commands of flight.
 * @param file_name is the file name to read from.
 */
  void run();
};

#endif //SIMULATOR_INTERPRETER__RUNPROGRAMM_H_
