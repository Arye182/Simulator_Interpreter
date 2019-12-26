//
// Created by arye on 19/12/2019.
//

#ifndef SIMULATOR_INTERPRETER__IFCOMMAND_H_
#define SIMULATOR_INTERPRETER__IFCOMMAND_H_

#include "Command.h"
#include "ConditionParser.h"
#include "Condition.h"

class IfCommand : public ConditionParser {
 public:
  IfCommand(vector<string> condition_arg,
            vector<Command *> commands_pointers_arg,
            vector<vector<string>> commands_strings_arg);
  double execute() override ;
};

#endif //SIMULATOR_INTERPRETER__IFCOMMAND_H_
