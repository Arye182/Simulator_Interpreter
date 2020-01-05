//
// Created by miri on 20.12.2019. from ex1


#ifndef EX3__MATH_H_
#define EX3__MATH_H_
#include "Expression.h"
#include <string>
#include <iterator>
#include <map>
#include <list>
#include <stack>
using namespace std;
//Exceptions

class Value : public Expression {
  const double value;
 public:
  Value(const double value_arg);
  virtual double calculate() override;
  virtual ~Value() override = default;
};

class Variable : public Expression {
  string name;
  double value;
  string m_bind_to;
  string m_sim;

 public:
  //defoult
  Variable(string name_arg, double value_arg);
  Variable(string name_arg);
  Variable(string name_arg, string bind_to_arg, string sim_arg);
  virtual ~Variable() override = default;
  virtual double calculate() override;
  Variable &operator++();
  Variable &operator--();
  Variable &operator+=(double number_arg);
  Variable &operator-=(double number_arg);
  Variable &operator++(int);
  Variable &operator--(int);
  void setValue(double new_value_arg);
  string getSim();
  string getBindSimbol();
  string getName();
  double getValue();

};

class BinaryOperator : public Expression {
 protected:
  Expression *left = nullptr;
  Expression *right = nullptr;

 public:
  BinaryOperator(Expression *left_arg, Expression *right_arg);
  //virtual double calculate() override ;
  virtual ~BinaryOperator() override;

};

class UnaryOperator : public Expression {
 protected:
  Expression *ex = nullptr;

 public:
  UnaryOperator(Expression *ex_arg);
  //virtual double calculate() override;
  virtual ~UnaryOperator() override;
};

class Plus : public BinaryOperator {
 public:
  Plus(Expression *left_arg, Expression *right_arg) : BinaryOperator(left_arg,
                                                                     right_arg) {}
  virtual double calculate() override;
  virtual ~Plus() {}
};

class Minus : public BinaryOperator {
 public:
  Minus(Expression *left_arg, Expression *right_arg) : BinaryOperator(left_arg,
                                                                      right_arg) {}
  virtual double calculate() override;
  virtual ~Minus() {}
};

class Mul : public BinaryOperator {
 public:
  Mul(Expression *left_arg, Expression *right_arg) : BinaryOperator(left_arg,
                                                                    right_arg) {}
  virtual double calculate() override;
  virtual ~Mul() {}
};

class Div : public BinaryOperator {
 public:
  Div(Expression *left_arg, Expression *right_arg) : BinaryOperator(left_arg,
                                                                    right_arg) {}
  double calculate() override;
  virtual ~Div() {}
};

class UPlus : public UnaryOperator {
 public:
  UPlus(Expression *ex_arg) : UnaryOperator(ex_arg) {};
  virtual double calculate() override;
  virtual ~UPlus() {}
};

class UMinus : public UnaryOperator {
 public:
  UMinus(Expression *ex_arg) : UnaryOperator(ex_arg) {};
  virtual double calculate() override;
  virtual ~UMinus() {}
};

class MathInterpreter {
  map<string, Variable *> *variables;
  list<string> *input = nullptr;
  stack<string> *operator_stack = nullptr;
  deque<string> *postfix_expression = nullptr;
 public:
  MathInterpreter(map<string, Variable *> *data_arg);
  ~MathInterpreter();
  void setVariables(string input_arg);
  Expression *interpret(string input_arg);
  void insertVariables(string variable_arg);
  void separateInput(string input_arg);
  //help
  void print();
  void fromInfixToPostfix();
  bool isUnary(list<string>::iterator it);
  bool isNumber(string s);
  bool isVariable(string s);
  bool inLowerPrecedence(string binary_operator1, string binary_operator2);
  Expression *fromStringToExpression();
};

#endif