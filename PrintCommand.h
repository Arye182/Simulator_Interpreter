//
// Created by arye on 19/12/2019.
//

#ifndef SIMULATOR_INTERPRETER__PRINTCOMMAND_H_
#define SIMULATOR_INTERPRETER__PRINTCOMMAND_H_

#include <string>
#include "Command.h"


class PrintCommand : public Command{
 private:
  string message;
 public:
  PrintCommand() = default;
  double execute() override ;
  void setParameters(vector<string> params) override ;
};

#endif //SIMULATOR_INTERPRETER__PRINTCOMMAND_H_
