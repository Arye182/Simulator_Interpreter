//
// Created by Arye Amsalem on 04/11/2019.
//

#include <stdexcept>
#include"Expression.h"
#include "MathInterpreter.h"
using namespace std;

// part 1 of the EX 1:
// implementations of constructors:
Value::Value(const double v) : value(v) {}
Variable::Variable(string s, double v) {
  this->value = v;
  this->name = s;
}
BinaryOperator::BinaryOperator(Expression *leftE, Expression *rightE) {
  this->left = leftE;
  this->right = rightE;
}
UnaryOperator::UnaryOperator(Expression *expression) {
  this->exp = expression;
}

// destructors:
BinaryOperator::~BinaryOperator() {
  delete (this->left);
  delete (this->right);
}
UnaryOperator::~UnaryOperator() {
  delete (this->exp);
}

// implementations of methods:
Variable &Variable::operator++() {
  this->value += 1;
  return *this;
}
Variable &Variable::operator++(int) {
  this->value += 1;
  return *this;
}
Variable &Variable::operator--() {
  this->value -= 1;
  return *this;
}
Variable &Variable::operator--(int) {
  this->value -= 1;
  return *this;
}
Variable &Variable::operator+=(double num) {
  this->value += num;
  return *this;
}
Variable &Variable::operator-=(double num) {
  this->value -= num;
  return *this;
}

// calculate implementations
double Value::calculate() {
  return this->value;
}
double Variable::calculate() {
  return this->value;
}
double Plus::calculate() {
  return (this->left->calculate() + this->right->calculate());
}
double Minus::calculate() {
  return (this->left->calculate() - this->right->calculate());
}
double Mul::calculate() {
  return (this->left->calculate() * this->right->calculate());
}
double Div::calculate() {
  if ((this->right->calculate()) == 0) {
    throw ("divided by zero");
  }
  return (this->left->calculate() / this->right->calculate());
}
double UPlus::calculate() {
  return this->exp->calculate();
}
double UMinus::calculate() {
  return -(this->exp->calculate());
}

// Part 2 of EX1:
// MathInterpreter Part using Shunting Yard Algorithm
MathInterpreter::MathInterpreter() {
  this->outputQueue = new queue<string>();
  this->operatorsStack = new stack<string>;
  this->tokenList = new list<string>();
  this->finalStack = new stack<string>();
  this->varMap = new map<string, double>();
}
MathInterpreter::~MathInterpreter() {
  delete (this->tokenList);
  delete (this->outputQueue);
  delete (this->operatorsStack);
  delete (this->finalStack);
  delete (this->varMap);
}
bool MathInterpreter::isDigit(char token) {
  return (token <= 57 && token >= 48);
}
bool MathInterpreter::isBinaryOperator(string token) {
  return (token == "/" || token == "*"
      || token == "+" || token == "-");
}
bool MathInterpreter::isStackTopOperatorGreaterOrEqualIt(string iterator) {
  if (this->operatorsStack->empty()) {
    return false;
  };
  string top = this->operatorsStack->top();
  if (top == "$" || top == "#") {
    return true;
  }
  if ((top == "+" || top == "-") && (iterator == "*" || iterator == "/")) {
    return false;
  }
  if ((top == "*" || top == "/") && (iterator == "+" || iterator == "-")) {
    return true;
  }
  if ((top == "+" || top == "-") && (iterator == "+" || iterator == "-")) {
    return true;
  }
  return (top == "*" || top == "/") && (iterator == "*" || iterator == "/");
}
void MathInterpreter::setVariables(string vars) {
  string delimiter = ";";
  size_t pos = 0;
  string token;
  while ((pos = vars.find(delimiter)) != string::npos) {
    token = vars.substr(0, pos);
    setVariablesHelper(token);
    vars.erase(0, pos + delimiter.length());
  }
  setVariablesHelper(vars);
}
void MathInterpreter::setVariablesHelper(string var) {
  string delimiter = "=";
  size_t pos = 0;
  string token;
  string varName;
  double varValue;
  while ((pos = var.find(delimiter)) != string::npos) {
    token = var.substr(0, pos);
    varName = token;
    var.erase(0, pos + delimiter.length());
  }

  if (this->isValidNumber(var)) {
    varValue = stod(var);
    std::map<string, double>::iterator it = this->varMap->find(varName);
    if (it != this->varMap->end()) {
      it->second = varValue;
    }
    this->varMap->insert({varName, varValue});
  } else {
    throw "illegal variable";
  }

}
void MathInterpreter::fromStringToList(string expression) {
  // iterate all the chars in the string
  for (unsigned int i = 0, j = 0; i < expression.size(); i++, j++) {
    string token;
    bool isUMinus = false;
    bool isUPlus = false;
    char current = expression[i];
    // if we have number upcoming
    if (this->isDigit(current) || ((j != 0) && (current == '-' && this->isDigit
        (expression[j + 1]) && !this->isDigit(expression[j - 1]) &&
        expression[j - 1] != ')'))) {
      while (this->isDigit(expression[j + 1]) ||
          expression[j + 1] == 46) {
        j++;
      }
    }
    // if we have variable upcoming
    if (this->isChar(current)) {
      while (this->isDigit(expression[j + 1]) ||
          this->isChar(expression[j + 1]) || expression[j + 1] == 95) {
        j++;
      }
    }
    // if we have unary operator
    if (current == '-' && expression[j + 1] == '(') {
      isUMinus = true;
    }
    if (current == '+' && expression[j + 1] == '(') {
      isUPlus = true;
    }
    if (j != 0
        && (this->isDigit(expression[j - 1]) ||
            this->isChar(expression[j - 1]) || expression[j - 1]
            == ')')) {
      isUMinus = false;
      isUPlus = false;
    }
    // preparing to insert to the list
    int tokenLen = j - i + 1;
    for (int k = 0, z = i; k < tokenLen; k++, z++) {
      if (isUMinus) {
        token = '$';
      } else if (isUPlus) {
        token = '#';
      } else {
        token += expression[z];
      }
    }
    this->tokenList->push_back(token);
    if (tokenLen > 1) {
      i = j;
    }
  }
}
/*
 * function : shunting yard:
 * i wrote this code base on shunting yard pseudo code from
 * https://brilliant.org/wiki/shunting-yard-algorithm/#
 * the validation of the correctness of the mathematical expression is used
 * with the help of this pseudo code:
 * https://stackoverflow.com/questions/16380234/
 * handling-extra-operators-in-shunting-yard
 *
 * this way we check the expression during the algorithm itself and by that
 * save run time complexity.
 *
 * */
void MathInterpreter::shuntingYard() {
  // the machine will have 2 states ExpectOperand and ExpectOperator.
  // ExpectOperand == 0 , ExpectOperator == 1;
  int machineState = 0;
  if (this->tokenList->front() == "#" || this->tokenList->front() == "$") {
    machineState = 1;
  }
  // we will use the list iterator :)
  for (list<string>::iterator it = tokenList->begin(); it != tokenList->end();
       ++it) {
    // If it's a number
    if (this->isDigit((*it)[0]) || ((*it)[0] == '-'
        && this->isDigit((*it)[1]))) {
      // if machine expect to get operator and we actually have an operand...
      if (machineState == 1) {
        throw "bad expression";
      }
      // push it to queue
      this->outputQueue->push(*it);
      machineState = 1;
    }

    // If token is a variable.
    if (this->isChar((*it)[0])) {
      // Error if state is not ExpectOperand.
      if (machineState == 1) {
        throw ("bad input");
      }
      // Push token to output queue.
      this->outputQueue->push(*it);
      // Set state to ExpectOperator.
      machineState = 1;
    }
    // If token is a unary operator.
    if (*it == "#" || *it == "$") {
      // Error if the state is not ExpectOperator
      if (machineState == 0) {
        throw ("bad input");
      }
      // Push the token to the operator stack.
      this->operatorsStack->push(*it);
      // Set the state to ExpectOperand.
      machineState = 0;
    }
    //  If it's a binary operator
    if (this->isBinaryOperator(*it)) {
      if (machineState == 0) {
        throw ("bad input - expected operand but gave an "
               "operator");
      }
      // While there's an operator on the top of the stack with greater
      // precedence:
      while (this->isStackTopOperatorGreaterOrEqualIt(*it)) {
        // Pop operators from the stack onto the output queue
        string tmp = operatorsStack->top();
        outputQueue->push(tmp);
        operatorsStack->pop();
      }
      // Push the current operator onto the stack
      this->operatorsStack->push(*it);
      machineState = 0;
    }
    // If it's a left bracket push it onto the stack
    if (*it == "(") {
      if (machineState == 1) {
        throw ("bad input - expected operator, not "
               "parentheses");
      }
      this->operatorsStack->push(*it);
      list<string>::iterator it2 = next(it, 1);
      if (*it2 == "$" || *it2 == "#") {
        machineState = 1;
      } else {
        machineState = 0;
      }

    }
    // If it's a right bracket
    if (*it == ")") {
      if (machineState == 0) {
        throw ("bad input");
      }
      // While there's not a left bracket at the top of the stack:
      while (!(this->operatorsStack->empty()) && !(this->operatorsStack->top()
          == "(")) {
        // Pop operators from the stack onto the output queue.
        string tmp = operatorsStack->top();
        outputQueue->push(tmp);
        operatorsStack->pop();
      }
      // check if there were too many parenthesis
      if (this->operatorsStack->empty()) {
        throw ("bad input - too many parenthesis");
      } else {
        // Pop the left bracket from the stack and discard it
        operatorsStack->pop();
        machineState = 1;
      }
    }
  }
  //  While there are operators on the stack, pop them to the queue
  while (!(operatorsStack->empty())) {
    if (operatorsStack->top() == "(" || operatorsStack->top() == ")") {
      throw ("bad input - mismatched parenthesis"); // mismatched parenthesis
    }
    string tmp = operatorsStack->top();
    outputQueue->push(tmp);
    operatorsStack->pop();
  }
  // end of shunting yard
}
Expression *MathInterpreter::fromPolishToTree() {
  // termination condition for recursion
  if (isDigit(this->finalStack->top()[0]) ||
      (isDigit(this->finalStack->top()[1])
          && (this->finalStack->top()[0] == '-'))) {
    string::size_type st;
    double val = stod(this->finalStack->top(), &st);
    this->finalStack->pop();
    return new Value(val);
  }
  if (this->isChar(this->finalStack->top()[0])) {
    string name = this->finalStack->top();
    map<string, double>::iterator it;
    it = this->varMap->find(name);
    if (it == this->varMap->end()) {
      throw ("no var found in map!");
    }
    double value = it->second;
    this->finalStack->pop();
    return new Variable(name, value);
  }
  Expression *left;
  Expression *right;
  Expression *unExp;
  string operatorChar = this->finalStack->top();
  // case this is a binary operator
  if (this->isBinaryOperator(operatorChar)) {
    this->finalStack->pop();
    // evaluating right left first due to polish notation constrains
    right = this->fromPolishToTree();
    left = this->fromPolishToTree();
    switch (operatorChar[0]) {
      case ('+'):return new Plus(left, right);
      case ('-'):return new Minus(left, right);
      case ('*'):return new Mul(left, right);
      case ('/'):return new Div(left, right);
    }
    // case its an unary operator
  } else if (operatorChar[0] == '#' || operatorChar[0] == '$') {
    this->finalStack->pop();
    unExp = this->fromPolishToTree();
    switch (operatorChar[0]) {
      case ('$'):return new UMinus(unExp);
      case ('#'):return new UPlus(unExp);
    }
  }
  return nullptr;
}
Expression *MathInterpreter::interpret(string expression) {
  // first stage of the MathInterpreter
  fromStringToList(expression);
  // second stage of MathInterpreter - shunting yard
  shuntingYard();
  // creating the final stack
  createFinalStack();
  // third stage - creating the expression tree
  return fromPolishToTree();
}
void MathInterpreter::createFinalStack() {
  while (!this->outputQueue->empty()) {
    string tmp = this->outputQueue->front();
    this->finalStack->push(tmp);
    this->outputQueue->pop();
  }
}
bool MathInterpreter::isChar(char token) {
  return (token <= 90 && token >= 65) || (token <= 122 && token >= 97);
}
bool MathInterpreter::isValidNumber(string token) {
  unsigned int i = 0;
  int dotFlag = 0;
  if (token[i] == '-') {
    i = 1;
  }
  while (i < token.size() && (dotFlag <= 1 && (this->isDigit(token[i]) ||
      token[i] == '.'))) {
    if (token[i] == '.') {
      dotFlag++;
    }
    i++;
  }
  return i == token.size();
}
