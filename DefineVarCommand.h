//
// Created by miri on 23.12.2019.
//

#ifndef SIMULATOR_INTERPRETER__DEFINEVARCOMMAND_H_
#define SIMULATOR_INTERPRETER__DEFINEVARCOMMAND_H_
#include "DataBase.h"
#include "Command.h"

static DataBase *d = DataBase::getInstance();

class DefineVarCommand : public Command {
 private:
  vector<string> type_data;
 public:
  DefineVarCommand() {}
  virtual void setParameters(vector<string> params) override;
  virtual double execute() override;
  virtual ~DefineVarCommand() {}
};
#endif //SIMULATOR_INTERPRETER__DEFINEVARCOMMAND_H_
