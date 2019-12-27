//
// Created by arye on 19/12/2019.
//

#include <iostream>
#include <ostream>
#include "SleepCommand.h"

double SleepCommand::execute() {
  //cout<<"i am sleeping now for " <<
  //this->time_to_sleep_string << " milliseconds!" << endl;
  std::this_thread::sleep_for(chrono::milliseconds(this->milliseconds));
  return 0;
}

void SleepCommand::setParameters(vector<string> params) {
  this->time_to_sleep_string = params[1];
  this->milliseconds = stod(this->time_to_sleep_string);
}
