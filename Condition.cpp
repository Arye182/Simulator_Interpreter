//
// Created by miri on 26.12.2019.
//

#include "Condition.h"

/**
 * Ctor.
 *
 * @param condition - is the strings for condition.
 *
 */
Condition::Condition(vector<string> condition) {
  this->m_condition = condition;
  this->m = new MathInterpreter(DataBase::getInstance()->getInVarMap());
}

/**
 * DCtor.
 *
 */
Condition::~Condition() {
  if (this->m != nullptr) {
    delete this->m;
    this->m = nullptr;
  }
}

/**
 * condition is an expression and therefore it needs to calculate.
 * but in this case the calculation will provide us a boolian result wether
 * the condition is satisfied or not.
 *
 */
double Condition::calculate() {
  Expression *left = this->m->interpret(this->m_condition[1]);
  Expression *right = this->m->interpret(this->m_condition[3]);
  double left_value = left->calculate();
  double right_value = right->calculate();
  delete left;
  delete right;
  if (m_condition[2] == "==") {
    return left_value == right_value;
  } else if (m_condition[2] == "<=") {
    return left_value <= right_value;
  } else if (m_condition[2] == ">=") {
    return left_value >= right_value;
  } else if (m_condition[2] == "<") {
    return left_value < right_value;
  } else if (m_condition[2] == ">") {
    return left_value > right_value;
  } else if (m_condition[2] == "!=") {
    return left_value != right_value;
  } else {
    throw ("condition sign" + m_condition[2] + "is invalid");
  }
}


