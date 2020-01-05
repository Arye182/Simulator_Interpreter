//
// Created by miri on 20.12.2019.
//
#include <iostream>
#include "Expression.h"
#include <regex>
#include <string>
#include <map>
#include <iterator>
#include "Math.h"
#define EXPECT_OPERAND 1
#define EXPECT_OPERATOR 0
//Value
Value::Value(const double value_arg) : value(value_arg) {}
double Value::calculate() {
  return this->value;
}

//Variable
Variable::Variable(string name_arg) {
  this->name = name_arg;
  this->m_sim = "0";
  this->m_bind_to = "0";
}

Variable::Variable(string name_arg, double value_arg) {
  this->name = name_arg;
  this->value = value_arg;
  this->m_sim = "0";
  this->m_bind_to = "0";
}
Variable::Variable(string name_arg, string bind_to, string sim) {
  this->name = name_arg;
  this->m_bind_to = bind_to;
  this->m_sim = sim;
}
double Variable::calculate() {
  return this->value;
}
Variable &Variable::operator++() {
  this->value = this->value + 1;
  return *this;
}
Variable &Variable::operator--() {
  this->value = this->value - 1;
  return *this;
}
Variable &Variable::operator+=(double number) {
  this->value = this->value + number;
  return *this;
}
Variable &Variable::operator-=(double number) {
  this->value = this->value - number;
  return *this;
}
Variable &Variable::operator++(int) {
  return this->operator++();
}
Variable &Variable::operator--(int) {
  return this->operator--();
}
void Variable::setValue(double new_value) {
  this->value = new_value;
}
string Variable::getSim() {
  if (this->m_sim == "0") {
    throw "variable has no sim variable";
  } else {
    return this->m_sim;
  }
}

string Variable::getBindSimbol() {
  if (this->m_bind_to == "0") {
    throw "var in not bind to sim";
  } else {
    return this->m_bind_to;
  }
}
string Variable::getName() {
  return this->name;
}
double Variable::getValue() {
  return this->value;
}

//BinaryOperator
BinaryOperator::BinaryOperator(Expression *left_arg, Expression *right_arg) {
  this->left = left_arg;
  this->right = right_arg;
}
BinaryOperator::~BinaryOperator() {
  if (this->left == nullptr) {
    delete this->left;
  }
  this->left = nullptr;
  if (this->right == nullptr) {
    delete this->right;
  }
  this->right = nullptr;
}

//UnaryOperator
UnaryOperator::UnaryOperator(Expression *ex_arg) {
  this->ex = ex_arg;
}
UnaryOperator::~UnaryOperator() {
  if (this->ex == nullptr) {
    delete this->ex;
  }
  this->ex = nullptr;
}

//Plus
double Plus::calculate() {
  return this->left->calculate() + this->right->calculate();
}

//Minus
double Minus::calculate() {
  return this->left->calculate() - this->right->calculate();
}

//Mul
double Mul::calculate() {
  return this->left->calculate() * this->right->calculate();
}

//Div
double Div::calculate() {
  if (this->right->calculate() == 0)
    throw ("division by zero");
  return this->left->calculate() / this->right->calculate();
}

//UPlus
double UPlus::calculate() {
  return this->ex->calculate();
}

//UMinus
double UMinus::calculate() {
  return -(this->ex->calculate());
}

//MathInterpreter: interprete internal variables only(not sim variables)
MathInterpreter::MathInterpreter(map<string, Variable *> *data) {
  this->input = new list<string>();
  this->variables = data;
  this->operator_stack = new stack<string>();
  this->postfix_expression = new deque<string>();
}

MathInterpreter::~MathInterpreter() {
  if (this->input == nullptr) {
    delete this->input;
  }
  this->input = nullptr;
  if (this->operator_stack == nullptr) {
    delete this->operator_stack;
  }
  this->operator_stack = nullptr;
  if (this->postfix_expression == nullptr) {
    delete this->postfix_expression;
  }
  this->postfix_expression = nullptr;

}
void MathInterpreter::insertVariables(string variable) {
  int p = variable.find("=");
  string name = variable.substr(0, p);
  Expression
      *e = this->interpret(variable.substr(p + 1, variable.length()).c_str());
  double value = e->calculate();
  delete e;
  if (this->variables->find(name) != this->variables->end()) {
    this->variables->at(name)->setValue(value);
  } else {
    throw ("assign to unexist variable\n");
  }
}

Expression *MathInterpreter::interpret(string input_arg) {
  this->separateInput(input_arg);
  this->fromInfixToPostfix();
  Expression *e = this->fromStringToExpression();
  delete this->input;
  this->input = new list<string>();
  return e;
}
void MathInterpreter::separateInput(string input_arg) {//-rol/70
  string temp = "";
  unsigned int start = 0, count = 0;
  //check negative number in begining of string
  if ((input_arg[start] == '-') && (input_arg.size() > 1)
      && (input_arg[1] <= '9') && (input_arg[1] >= '0')) {
    temp += input_arg[start];
    start++;
    while ((start < input_arg.size())
        && (((input_arg[start] <= '9') && (input_arg[start] >= '0'))
            || (input_arg[start] == '.'))) {
      if (input_arg[start] == '.') {
        count++;
      }
      temp += input_arg[start];
      start++;
    }
    if (count > 1) {
      throw ("Invalid input");
    }
    this->input->push_back(temp);
    temp = "";
  }
  while (start < input_arg.size()) {
    if (((input_arg[start] <= 'z') && (input_arg[start] >= 'a'))
        || ((input_arg[start] <= 'Z') && (input_arg[start] >= 'A'))) {
      temp += input_arg[start];
      start++;
      while (start < input_arg.size()
          && (((input_arg[start] <= 'z') && (input_arg[start] >= 'a'))
              || ((input_arg[start] <= 'Z') && (input_arg[start] >= 'A'))
              || (input_arg[start] == '_')
              || ((input_arg[start] <= '9') && (input_arg[start] >= '0')))) {
        temp += input_arg[start];
        start++;
      }
    } else if ((input_arg[start] <= '9') && (input_arg[start] >= '0')) {
      temp += input_arg[start];
      start++;
      while ((start < input_arg.size())
          && (((input_arg[start] <= '9') && (input_arg[start] >= '0'))
              || (input_arg[start] == '.'))) {
        if (input_arg[start] == '.') {
          count++;
        }
        temp += input_arg[start];
        start++;
      }
      if (count > 1) {
        throw ("invalid input_arg3");
      }
    } else if ((input_arg[start] == '(') || (input_arg[start] == ')')
        || (input_arg[start] == '+') || (input_arg[start] == '-')
        || (input_arg[start] == '*') || (input_arg[start] == '/')) {
      //check for negative number in input_arg
      if ((input_arg[start] == '-') && (input_arg.size() > start + 1)
          && (start > 0) && (input_arg[start - 1] == '(')
          && (input_arg[start + 1] <= '9') && (input_arg[start + 1] >= '0')) {
        temp += (input_arg[start]);
        start++;
        temp += (input_arg[start]);
        start++;
        while ((start < input_arg.size())
            && (((input_arg[start] <= '9') && (input_arg[start] >= '0'))
                || (input_arg[start] == '.'))) {
          if (input_arg[start] == '.') {
            count++;
          }
          temp += input_arg[start];
          start++;
        }
      } else {
        temp += input_arg[start];
        start++;
      }
    } else {
      throw ("invalid input_arg2");
    }
    this->input->push_back(temp);
    temp = "";
  }
}

void MathInterpreter::fromInfixToPostfix() {
  int state_machine = EXPECT_OPERAND;
  string temp = "";
  for (list<string>::iterator i = this->input->begin(); i != this->input->end();
       ++i) {
    if (isNumber(*i)) {
      if (state_machine) {
        this->postfix_expression->push_back(*i);
        state_machine = EXPECT_OPERATOR;
      } else {
        throw ("Invalid input4");
      }
    } else if (isVariable((*i))) {
      if (state_machine) {
        this->postfix_expression->push_back((*i));
        state_machine = EXPECT_OPERATOR;
      } else {
        throw ("illegal math expression");
      }
    } else if (((((*i) == "+") || (*i) == "-")) && isUnary(i)) {
      if (state_machine) {
        //@ for UPlus
        if (((*i) == "+")) {
          this->operator_stack->push("@");
        } else {
          //$ for UMinus
          this->operator_stack->push("$");
        }
        state_machine = EXPECT_OPERAND;
      }
    } else if (((*i) == "*") || ((*i) == "/") || ((*i) == "+")
        || ((*i) == "-")) {
      if (state_machine) {
        throw ("illegal math expression");
      } else {
        while ((!(this->operator_stack->empty()))
            && (inLowerPrecedence((*i), (this->operator_stack->top())))) {
          this->postfix_expression->push_back(this->operator_stack->top());
          this->operator_stack->pop();
        }
        this->operator_stack->push((*i));
        state_machine = EXPECT_OPERAND;
      }
    } else if ((*i) == "(") {
      if (state_machine) {
        this->operator_stack->push((*i));
        state_machine = EXPECT_OPERAND;
      } else {
        throw ("illegal math expression");
      }
    } else if ((*i) == ")") {
      if (state_machine) {
        throw ("illegal math expression");
      } else {
        while ((!(this->operator_stack->empty()))
            && (this->operator_stack->top() != "(")) {
          this->postfix_expression->push_back(this->operator_stack->top());
          this->operator_stack->pop();
        }
        if (!(this->operator_stack->empty())) {
          this->operator_stack->pop();
        }
        state_machine = EXPECT_OPERATOR;
      }
    }
  }
  while (!(this->operator_stack->empty())) {
    if ((this->operator_stack->top() == "(")
        || (this->operator_stack->top()) == ")") {
      throw ("mismatched parenthesis");
    } else {
      this->postfix_expression->push_back(this->operator_stack->top());
      this->operator_stack->pop();
    }
  }
}
bool MathInterpreter::isUnary(list<string>::iterator it) {//
  list<string>::iterator temp_it = it;
  if (it == this->input->begin()) {
    it++;
    if ((*(it) == "(") || (isVariable(*(it)))) {
      return true;
    }
  } else {
    if (!(it == this->input->end())) {
      if (((*(--temp_it)) == "(") && ((*(++it)) == "(")) {
        return true;
      }
    }
  }
  return false;
}

bool MathInterpreter::isNumber(string s) {
  unsigned int i = 1, count = 0;
  if (((s[0] <= '9') && (s[0] >= '0')) || ((s[0] <= 'Z') && (s[0] >= 'A'))
      || (s[0] == '-')) {
    while ((i < s.size())
        && (((s[i] <= '9') && (s[i] >= '0')) || (s[i] == '.'))) {
      if (s[i] == '.') {
        count++;
      }
      i++;
    }
    if (((s.size() >= 2) && (!((s[0] == '-') && (s[1] == '.'))))
        || ((s.size() < 2) && (!(s[0] == '-')))) {
      if ((i == s.size()) && (count <= 1)) {
        return true;
      }
    }
  }
  return false;
}
bool MathInterpreter::isVariable(string s) {
  unsigned int i = 0;
  std::size_t size = s.size();
  if (((s[i] <= 'z') && (s[i] >= 'a')) || ((s[i] <= 'Z') && (s[i] >= 'A'))) {
    i++;
    while (i < size && (((s[i] <= 'z') && (s[i] >= 'a'))
        || ((s[i] <= 'Z') && (s[i] >= 'A')) || (s[i] == '_')
        || ((s[i] <= '9') && (s[i] >= '0')))) {
      i++;
    }
    if (i == size) {
      return true;
    }
  }
  return false;
}

bool MathInterpreter::inLowerPrecedence(string binary_operator1,
                                        string binary_operator2) {

  if ((binary_operator1 == "+") || (binary_operator1 == "-")) {
    if ((binary_operator2 == "*") || (binary_operator2 == "/")) {
      return true;
    }
    return false;
  }
  return false;
}
Expression *MathInterpreter::fromStringToExpression() {
  string temp;
  Expression *right, *left;
  temp = this->postfix_expression->back();
  this->postfix_expression->pop_back();
  if (isNumber(temp)) {
    return new Value(atof(temp.c_str()));
  } else if (isVariable(temp)) {
    if (this->variables->find(temp) == this->variables->end()) {
      throw ("illegal use of variable!");
    }
    return new Variable(temp, this->variables->at(temp)->calculate());
  } else if (temp == "@") {
    return new UPlus(fromStringToExpression());
  } else if (temp == "$") {
    return new UMinus(fromStringToExpression());
  } else if (temp == "+") {
    right = fromStringToExpression();
    left = fromStringToExpression();
    return new Plus(left, right);
  } else if (temp == "-") {
    right = fromStringToExpression();
    left = fromStringToExpression();
    return new Minus(left, right);
  } else if (temp == "*") {
    right = fromStringToExpression();
    left = fromStringToExpression();
    return new Mul(left, right);
  } else if (temp == "/") {
    right = fromStringToExpression();
    left = fromStringToExpression();
    return new Div(left, right);
  }
  return nullptr;
}


