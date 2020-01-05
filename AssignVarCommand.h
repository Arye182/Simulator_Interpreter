//
// Created by miri on 21.12.2019.
//

#ifndef SIMULATOR_INTERPRETER__ASSIGNVARCOMMAND_H_
#define SIMULATOR_INTERPRETER__ASSIGNVARCOMMAND_H_

#include "Command.h"
#include <string>
#include <vector>
#include "DataBase.h"

class AssignVarCommand : public Command {
 private:
  vector<string> param_v;
  MathInterpreter *i = nullptr;

 public:
  AssignVarCommand();
  virtual void setParameters(vector<string>) override;
  virtual double execute() override;
  virtual ~AssignVarCommand() override;
};

#endif //SIMULATOR_INTERPRETER__ASSIGNVARCOMMAND_H_
