//
// Created by arye on 20/12/2019.
//

#include "ConditionParser.h"

double ConditionParser::execute() {
  int i = 0;
  for (Command *c : commands_pointers) {
    vector<string> command_string_vector = this->commands_strings[i];
    c->setParameters(command_string_vector);
    c->execute();
    ++i;
  }
  return 0;
}

ConditionParser::ConditionParser(string condition_arg, vector<Command *>
    commands_pointers_arg, vector<vector<string>> commands_strings_arg) {
  this->condition = condition_arg;
  this->commands_pointers = commands_pointers_arg;
  this->commands_strings = commands_strings_arg;
}

void ConditionParser::setParameters(vector<string> params) {
  this->condition = params[1];
}


