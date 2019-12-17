//
// Created by Arye Amsalem on 04/11/2019.
//

#ifndef SIMULATUR_INTERPRETER_MATHINTERPRETER_H
#define SIMULATUR_INTERPRETER_MATHINTERPRETER_H
#include <stack>
#include <queue>
#include <list>
#include <map>
#include"Expression.h"
using namespace std;

// classes that inherit from Expression class
class BinaryOperator : public Expression {
 protected:
  Expression *left;
  Expression *right;
 public:
  BinaryOperator(Expression *leftE, Expression *rightE);
  virtual ~BinaryOperator() override;
};
class UnaryOperator : public Expression {
 protected:
  Expression *exp;
 public:
  explicit UnaryOperator(Expression *expression);
  virtual ~UnaryOperator() override;
};
class Value : public Expression {
 private:
  const double value; // const for making it immutable
 public:
  explicit Value(double v);
  virtual ~Value() override = default;
  double calculate() override;
};
class Variable : public Expression {
 private:
  double value;
  string name;
 public:
  Variable(string s, double v);
  virtual ~Variable() override = default;
  double calculate() override;
  // the functions below are operator overloading
  Variable &operator++();
  Variable &operator++(int);
  Variable &operator--();
  Variable &operator--(int);
  Variable &operator+=(double num);
  Variable &operator-=(double num);
};

// classes that inherit from BinaryOperator
class Plus : public BinaryOperator {
 public:
  double calculate() override;
  Plus(Expression *leftE, Expression *rightE) : BinaryOperator(leftE, rightE) {}
  virtual ~Plus() override = default;
};
class Minus : public BinaryOperator {
 public:
  double calculate() override;
  Minus(Expression *leftE, Expression *rightE) : BinaryOperator(leftE,
                                                                rightE) {}
  virtual ~Minus() override = default;
};
class Mul : public BinaryOperator {
 public:
  double calculate() override;
  Mul(Expression *leftE, Expression *rightE) : BinaryOperator(leftE, rightE) {}
  virtual ~Mul() override = default;
};
class Div : public BinaryOperator {
 public:
  double calculate() override;
  Div(Expression *leftE, Expression *rightE) : BinaryOperator(leftE, rightE) {}
  virtual ~Div() override = default;
};

// classes that inherit from UnaryOperator
class UPlus : public UnaryOperator {
 public:
  double calculate() override;
  explicit UPlus(Expression *expression) : UnaryOperator(expression) {}
  virtual ~UPlus() override = default;
};
class UMinus : public UnaryOperator {
 public:
  double calculate() override;
  explicit UMinus(Expression *expression) : UnaryOperator(expression) {}
  virtual ~UMinus() override = default;
};

// iterator class
class MathInterpreter {
 private:
  map<string, double> *varMap; // save variables
  queue<string> *outputQueue; // output from shunting yard
  stack<string> *operatorsStack; // part of shunting yard
  stack<string> *finalStack; // switching the output queue to stack
  list<string> *tokenList; // list of operators and operands to shunting yard
 public:
  MathInterpreter();
  ~MathInterpreter();
  // function that returns if a string is a binary operator
  bool isBinaryOperator(string token);
  // function that returns id a char is a digit or no
  bool isDigit(char token);
  // function that returns if a char is a letter or not
  bool isChar(char token);
  // function that checks if a string is a valid floating number
  bool isValidNumber(string token);
  // function that helps shunting yard to check operators precedences
  bool isStackTopOperatorGreaterOrEqualIt(string iterator);
  // function that saves variables in a map
  void setVariables(string vars);
  // helper for set variables
  void setVariablesHelper(string var);
  // step one of the interpretation - from string in infix to a list of strings
  void fromStringToList(string expression);
  // the algorithm shunting yard - enhanced
  void shuntingYard();
  // switching queue to stack
  void createFinalStack();
  // taking a stack in polish notation and switch it to expression* in
  // recursion
  Expression *fromPolishToTree();
  // the process itself of interpreting
  Expression *interpret(string expression);
};
#endif //SIMULATUR_INTERPRETER_MATHINTERPRETER_H
