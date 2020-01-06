//
// Created by arye on 19/12/2019.
//

#include <iostream>
#include "PrintCommand.h"
#include "DataBase.h"

static DataBase *data = DataBase::getInstance();

/**
 * execute the print command - just print the message
 * @return
 */
double PrintCommand::execute() {
  if (data->getInVarMap()->find(this->message) != data->getInVarMap()->end()) {
    cout << data->getInVarMap()->find(this->message)->first <<
         ": " << data->getInVarMap()->find(this->message)->second->calculate()
         << endl;
  } else {
    cout << this->message << endl;
  }
  return 0;
}

/**
 * set parameters of print command
 * @param params
 */
void PrintCommand::setParameters(vector<string> params) {
  this->message = params[1];
}
