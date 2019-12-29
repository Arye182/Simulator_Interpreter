//
// Created by arye on 19/12/2019.
//

#ifndef SIMULATOR_INTERPRETER__SLEEPCOMMAND_H_
#define SIMULATOR_INTERPRETER__SLEEPCOMMAND_H_

#include "Command.h"
#include "Command.h"
#include "chrono"
#include "thread"

class SleepCommand : public Command {
 private:
  string time_to_sleep_string;
  int milliseconds;
 public:
  SleepCommand() = default;
  double execute() override;
  void setParameters(vector<string> params) override;
  ~SleepCommand() override = default;
};

#endif //SIMULATOR_INTERPRETER__SLEEPCOMMAND_H_
