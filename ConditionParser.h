//
// Created by arye on 20/12/2019.
//

#ifndef SIMULATOR_INTERPRETER__CONDITIONPARSER_H_
#define SIMULATOR_INTERPRETER__CONDITIONPARSER_H_

#include "Command.h"
#include <vector>
#include <string>
#include"Condition.h"

using namespace std;

class ConditionParser : public Command {

 protected:
  string condition;
  vector<string> condition_vector;
  vector<vector<string>> commands_strings;
  vector<Command *> commands_pointers;

 public:
  ConditionParser(vector<string> condition_arg, vector<Command *>
  commands_pointers_arg,
                  vector<vector<string>> commands_strings_arg);
  double execute() override;
  void setParameters(vector<string> params) override;
  ~ConditionParser() override = default;
};

#endif //SIMULATOR_INTERPRETER__CONDITIONPARSER_H_
