//
// Created by arye on 15/12/2019.
//

#ifndef SIMULATUR_INTERPRETER__COMMAND_H_
#define SIMULATUR_INTERPRETER__COMMAND_H_

#include <string>
#include <vector>
using namespace std;

/**
 * this is the Command interface, a lot of classes implement this interface
 * and it is our heart of the program.
 * in order that execute will not have arguments we added the set parameters
 * method to make things easier.
 *
 */
class Command {
 public:
  virtual double execute() = 0;
  virtual void setParameters(vector<string> params) = 0;
  virtual ~Command() = default;
};

#endif //SIMULATUR_INTERPRETER__COMMAND_H_
