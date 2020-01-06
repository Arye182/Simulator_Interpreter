//
// Created by arye on 19/12/2019.
//

#ifndef SIMULATOR_INTERPRETER__RUNPROGRAMM_H_
#define SIMULATOR_INTERPRETER__RUNPROGRAMM_H_

#include <iostream>
#include "Interpreter.h"
#include "OpenDataServerCommand.h"
#include "Lexer.h"
#include <vector>

class RunProgramm {
 private:
  string file_name;
  Lexer *lexer = nullptr;
  Interpreter *parser = nullptr;

 public:
  RunProgramm(string file);
  void run();
  ~RunProgramm();
};

#endif //SIMULATOR_INTERPRETER__RUNPROGRAMM_H_
