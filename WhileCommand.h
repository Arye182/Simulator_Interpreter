//
// Created by arye on 19/12/2019.
//

#ifndef SIMULATOR_INTERPRETER__WHILECOMMAND_H_
#define SIMULATOR_INTERPRETER__WHILECOMMAND_H_

#include "Command.h"
#include "ConditionParser.h"

class WhileCommand : public ConditionParser {
 public:
  WhileCommand(vector<string> condition_arg,
               vector<Command *> commands_pointers_arg,
               vector<vector<string>> commands_strings_arg);
  double execute() override;
  ~WhileCommand() override = default;
};

#endif //SIMULATOR_INTERPRETER__WHILECOMMAND_H_
