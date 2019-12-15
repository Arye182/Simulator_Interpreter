//
// Created by arye on 15/12/2019.
//

#ifndef EX3_ME__COMMAND_H_
#define EX3_ME__COMMAND_H_
using namespace std;

/*
 * this is the command interface
 *
 * */
class Command {
 public:
  virtual double execute() = 0;
};
#endif //EX3_ME__COMMAND_H_
