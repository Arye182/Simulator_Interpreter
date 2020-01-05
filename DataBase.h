//
// Created by miri on 20.12.2019.
//

#ifndef SIMULATOR_INTERPRETER__DATABASE_H_
#define SIMULATOR_INTERPRETER__DATABASE_H_
#include <string>
#include <map>
#include <queue>
#include <mutex>
#include "Math.h"
using namespace std;

class DataBase {

 private:
  static DataBase *Instance;
  map<string, Variable *> *in_var_map = nullptr;
  map<string, Variable *> *sim_var_map = nullptr;
  queue<string> updates_to_sim;
  string sim_var_index[36] =
      {"/instrumentation/airspeed-indicator/indicated-speed-kt",
       "/sim/time/warp",
       "/controls/switches/magnetos",
       "/instrumentation/heading-indicator/offset-deg",
       "/instrumentation/altimeter/indicated-altitude-ft",
       "/instrumentation/altimeter/pressure-alt-ft",
       "/instrumentation/attitude-indicator/indicated-pitch-deg",
       "/instrumentation/attitude-indicator/indicated-roll-deg",
       "/instrumentation/attitude-indicator/internal-pitch-deg",
       "/instrumentation/attitude-indicator/internal-roll-deg",
       "/instrumentation/encoder/indicated-altitude-ft",
       "/instrumentation/encoder/pressure-alt-ft",
       "/instrumentation/gps/indicated-altitude-ft",
       "/instrumentation/gps/indicated-ground-speed-kt",
       "/instrumentation/gps/indicated-vertical-speed",
       "/instrumentation/heading-indicator/indicated-heading-deg",
       "/instrumentation/magnetic-compass/indicated-heading-deg",
       "/instrumentation/slip-skid-ball/indicated-slip-skid",
       "/instrumentation/turn-indicator/indicated-turn-rate",
       "/instrumentation/vertical-speed-indicator/indicated-speed-fpm",
       "/controls/flight/aileron",
       "/controls/flight/elevator",
       "/controls/flight/rudder",
       "/controls/flight/flaps",
       "/controls/engines/engine/throttle",
       "/controls/engines/current-engine/throttle",
       "/controls/switches/master-avionics",
       "/controls/switches/starter",
       "/engines/active-engine/auto-start",
       "/controls/flight/speedbrake",
       "/sim/model/c172p/brake-parking",
       "/controls/engines/engine/primer",
       "/controls/engines/current-engine/mixture",
       "/controls/switches/master-bat",
       "/controls/switches/master-alt",
       "/engines/engine/rpm"
      };
  DataBase();
  bool is_running = false;

 public:
  mutex sim_var_map_lock;
  mutex in_var_map_lock;
  static DataBase *getInstance();
  map<string, Variable *> *getInVarMap();
  map<string, Variable *> *getSimVarMap();
  void addToUpdateSimQueue(string update);
  queue<string> *getUpdateSimQueue();
  void setSimData(string line_from_sim);
  bool getIsRunning();
  void setIsRunning(bool mode);
  //test
  void printInVarMap();
  ~DataBase();
};

#endif //SIMULATOR_INTERPRETER__DATABASE_H_
