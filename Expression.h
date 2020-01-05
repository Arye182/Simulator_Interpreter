
#ifndef SIMULATOR_INTERPRETER_EXPRESSION_H
#define SIMULATOR_INTERPRETER_EXPRESSION_H

using namespace std;
/**
 * Expression Interface
 */
class Expression {

 public:
  virtual double calculate() = 0;
  virtual ~Expression() = default;
};

#endif //SIMULATOR_INTERPRETER_EXPRESSION_H
