//
// Created by miri on 23.12.2019.
//

#include "DefineVarCommand.h"

/**
 * this is the set parameters of the command define var command
 * @param params - the parameters of the command
 */
void DefineVarCommand::setParameters(vector<string> params) {
  this->type_data = params;
}

/**
 * execute implementation of DefineVarCommand - creates a new variable in the
 * map in the data base and updates its fields.
 *
 */
double DefineVarCommand::execute() {
  if (!(this->type_data[0] == "var")) {
    printf("failed definning var : wrong input");
  } else {
    Variable *v;
    if ((this->type_data[2] == "->") || (this->type_data[2] == "<-")) {
      v = new Variable(type_data[1], type_data[2], type_data[4]);
      d->getInVarMap()->insert({this->type_data[1], v});
      d->getSimVarMap()->insert({this->type_data[4], v});
    }
    if ((this->type_data[2] == "=") && (this->type_data.size() == 4)) {
      v = new Variable(this->type_data[1]);
      d->getInVarMap()->insert({this->type_data[1], v});
      MathInterpreter *mi = new MathInterpreter(d->getInVarMap());
      mi->insertVariables(type_data[1] + type_data[2] + type_data[3]);
      delete mi;
    }
  }
  return 0;
}