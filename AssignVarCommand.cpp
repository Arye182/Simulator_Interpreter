//
// Created by miri on 21.12.2019.
//

#include "AssignVarCommand.h"
#include <string>
#include <vector>

using namespace std;
static DataBase *d = DataBase::getInstance();

/**
 * Ctor.
 *
 */
AssignVarCommand::AssignVarCommand() {
  this->i = new MathInterpreter(d->getInVarMap());
}

/**
 * setParameters function is a function we have in every Command.
 * @param variable_data - is the data that is relevant for each command
 */
void AssignVarCommand::setParameters(vector<string> variable_data) {
  this->param_v = variable_data;
}

/**
 * the execution of assigning variable command is very important it not only
 * updates the values in the map but also send info to simulator according to
 * sim sign (-> or <-).
 */
double AssignVarCommand::execute() {
  string var_name;
  int p;
  //assing in data
  this->i->insertVariables((this->param_v)[0]);
  //assign in simulator
  p = this->param_v[0].find("=");
  var_name = param_v[0].substr(0, p);
  if (!(d->getInVarMap()->find(var_name) == d->getInVarMap()->end())) {
    Variable *temp = d->getInVarMap()->at(var_name);
    // send instruction to simulator
    if (temp->getBindSimbol() == "->") {
      d->addToUpdateSimQueue(
          "set " + temp->getSim() + " " + to_string(temp->calculate())
              + "\r\n");
    }
  }
  return 0;
}

/**
 * DCtor.
 */
AssignVarCommand::~AssignVarCommand() {
  if (this->i != nullptr) {
    delete this->i;
    this->i = nullptr;
  }
}