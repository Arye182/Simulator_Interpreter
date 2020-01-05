//
// Created by miri on 20.12.2019.
//

#include <map>
#include <queue>
#include "DataBase.h"
#include <iostream>

DataBase *DataBase::Instance = nullptr;

/**
 * Ctor.
 * creates new maps in var map and sim var map are our main data bases brain,
 * in these maps all the magic happens.
 */
DataBase::DataBase() {
  this->in_var_map = new map<string, Variable *>();
  this->sim_var_map = new map<string, Variable *>();
}

/**
 * we chose to use the design pattern singleton in this class because it is a
 * class that we create only one time during all the program, in other words
 * we only need one and only one instance of that class.
 *
 * so get Instance is responsible for returning this instance of the one that
 * was created first unless it is null of course - if it is null it will
 * instance it immediately.
 *
 */
DataBase *DataBase::getInstance() {
  if (Instance == nullptr) {
    Instance = new DataBase();
  }
  return Instance;
}

/**
 * getInVarMap - getter for in_var_map
 * @return the map pointer.
 */
map<string, Variable *> *DataBase::getInVarMap() {
  return this->in_var_map;
}

/**
 * getSimVarMap - getter for sim_var_map
 * @return the map pointer.
 */
map<string, Variable *> *DataBase::getSimVarMap() {
  return this->sim_var_map;
}

/**
 * this method pushes to the instructions queue the next instruction
 * @param update - instruction to simulator
 */
void DataBase::addToUpdateSimQueue(string update) {
  this->updates_to_sim.push(update);
}

/**
 * prints all the map - in_var_map
 */
void DataBase::printInVarMap() {
  map<string, Variable *>::iterator it;
  cout << endl;
  for (it = this->in_var_map->begin(); it != in_var_map->end(); it++) {
    cout << (*it).first << ": " << (*it).second->calculate() <<
         "  ---  ";
  }
  cout << endl;
}

/**
 * getter of the queue of instructions (pointer)
 */
queue<string> *DataBase::getUpdateSimQueue() {
  return &(DataBase::updates_to_sim);
}

/**
 * one of the main impacts of the thread of recieving information from the
 * simulator. (every 10 mls). updates every line in the map.
 *
 * @param line_from_sim line that holds 36 values from simulator
 */
void DataBase::setSimData(string line_from_sim) {
  int i = 0, index = 0, size;
  string::size_type j;
  double value;
  string name;
  size = line_from_sim.size();
  j = line_from_sim.find(',');
  //read values from line and updates them in internal data
  while (j != string::npos) {
    value = stod(line_from_sim.substr(i, j));
    name = this->sim_var_index[index];
    if ((this->sim_var_map->find(name) != this->sim_var_map->end())
        && (this->sim_var_map->at(name)->getBindSimbol() == "<-")) {
      this->sim_var_map->at(name)->setValue(value);
    }
    i = j + 1;
    j = line_from_sim.find(',', i);
    index++;
  }
  if (i < size) {
    value = stod(line_from_sim.substr(i, size));
    name = this->sim_var_index[index];
    if ((this->sim_var_map->find(name) != this->sim_var_map->end())
        && (this->sim_var_map->at(name)->getBindSimbol() == "<-")) {
      this->sim_var_map->at(name)->setValue(value);
    }
  }
  //unlock the maps
  DataBase::sim_var_map_lock.unlock();
  DataBase::in_var_map_lock.unlock();
}

/**
 * getter of the boolean variable is running
 */
bool DataBase::getIsRunning() {
  return this->is_running;
}

/**
 * setter of the bollean variable is running
 */
void DataBase::setIsRunning(bool mode) {
  this->is_running = mode;
}

/**
 * Dctor.
 * this instance = nullptr thanks to the fact it is a singleton.
 */
DataBase::~DataBase() {
  if (this->in_var_map != nullptr) {
    delete this->in_var_map;
    this->in_var_map = nullptr;
  }
  if (this->sim_var_map != nullptr) {
    delete this->sim_var_map;
    this->sim_var_map = nullptr;
  }
  this->Instance = nullptr;
}






