//
// Created by arye on 19/12/2019.
//

#include <iostream>
#include "PrintCommand.h"

double PrintCommand::execute() {
  // TODO check if the string msg is one of the planes variables - if so
  //  print this var. else print the msg itself. as a string... :)
  cout<< this->message << endl;
  return 0;
}
void PrintCommand::setParameters(vector<string> params) {
  this->message = params[1];
}
