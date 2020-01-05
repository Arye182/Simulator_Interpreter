//
// Created by miri on 26.12.2019.
//

#ifndef SIMULATOR_INTERPRETER__CONDITION_H_
#define SIMULATOR_INTERPRETER__CONDITION_H_

#include "Expression.h"
#include "DataBase.h"
#include <regex>

class Condition : public Expression {
  MathInterpreter *m = nullptr;
  vector<string> m_condition;

 public:
  Condition(vector<string> condition);
  double calculate() override;
  virtual ~Condition() override;
};

#endif //SIMULATOR_INTERPRETER__CONDITION_H_
