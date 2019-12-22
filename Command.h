//
// Created by arye on 15/12/2019.
//

#ifndef SIMULATUR_INTERPRETER__COMMAND_H_
#define SIMULATUR_INTERPRETER__COMMAND_H_
#include <string>
#include <vector>
using namespace std;

/*
 * this is the command interface
 *
 * */
class Command {
 public:
  virtual double execute() = 0;
  virtual void setParameters(vector<string> params) = 0;
};
#endif //SIMULATUR_INTERPRETER__COMMAND_H_
