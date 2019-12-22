//
// Created by arye on 19/12/2019.
//

#include <iostream>
#include "IfCommand.h"

IfCommand::IfCommand(string condition_arg, vector<Command *>
commands_pointers_arg, vector<vector<string>> commands_strings_arg)
    : ConditionParser(condition_arg, commands_pointers_arg, commands_strings_arg) {

}

double IfCommand::execute() {
  cout<< "executing if command" << endl;
  //Condition *cond = new Condition(this->condition);
//  if (cond.calculate()) {
//    ConditionParser::execute();
//  }
  //delete cond;
  return 0;
}
