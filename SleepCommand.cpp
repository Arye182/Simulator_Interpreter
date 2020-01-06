//
// Created by arye on 19/12/2019.
//

#include <iostream>
#include <ostream>
#include "SleepCommand.h"

/**
 * sleep this thread
 * @return 0
 */
double SleepCommand::execute() {
  std::this_thread::sleep_for(chrono::milliseconds(this->milliseconds));
  return 0;
}

/**
 * set ms for sleep
 * @param params
 */
void SleepCommand::setParameters(vector<string> params) {
  this->time_to_sleep_string = params[1];
  this->milliseconds = stod(this->time_to_sleep_string);
}
