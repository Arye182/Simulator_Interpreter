
#ifndef PROJECT_EXPRESSION_H
#define PROJECT_EXPRESSION_H

using namespace std;
/**
 * Expression Interface
 */
class Expression {

 public:
  virtual double calculate() = 0;
  virtual ~Expression() = default;
};

#endif //PROJECT_EXPRESSION_H
