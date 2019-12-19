//
// Created by arye on 15/12/2019.
//

#ifndef SIMULATUR_INTERPRETER__INTERPRETER_H_
#define SIMULATUR_INTERPRETER__INTERPRETER_H_

#include <string>
#include <vector>
#include <map>

#include "Command.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "WhileCommand.h"
#include "IfCommand.h"
#include "OpenDataServerCommand.h"


using namespace std;

class Interpreter {
 private:
  vector<vector<string>> lexed_data_to_interpret;
  vector<Command*> commands_to_run;
  enum simulatorCommand{
    OPEN_DATA_SERVER, CONNECT,
    VAR, PRINT, SLEEP, INIT, CONDITIONAL
  };
  map<string,simulatorCommand> CMD_DICTIONARY = {
      {"openDataServer", OPEN_DATA_SERVER},
      {"connectControlClient", CONNECT},
      {"var", VAR},
      {"Print", PRINT},
      {"Sleep", SLEEP},
      {"while", CONDITIONAL},
      {"if", CONDITIONAL},
  };
 public:
  Interpreter(vector<vector<string>> lexed_data);
  void parseLexedDataToCommandsVector();
  void runCommands();
  void run();
};

#endif //SIMULATUR_INTERPRETER__INTERPRETER_H_
