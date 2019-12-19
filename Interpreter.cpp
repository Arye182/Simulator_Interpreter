//
// Created by arye on 15/12/2019.
//

#include "Interpreter.h"


Interpreter::Interpreter(vector<vector<string>> lexed_data) {
  this->lexed_data_to_interpret = lexed_data;
}


void Interpreter::parseLexedDataToCommandsVector() {
  int iteration = 0;
  for (auto it = this->lexed_data_to_interpret.begin(); it !=
       this->lexed_data_to_interpret.end(); ++it, ++iteration) {
    string command_string = (*it)[0];
    int commandEnum;
    if (this->CMD_DICTIONARY.find((*it)[0]) != this->CMD_DICTIONARY.end()) {
      commandEnum = this->CMD_DICTIONARY[(*it)[0]];
    } else if (command_string != "}"){
      commandEnum = INIT;
    } else {
      commandEnum = -1;
    }
    switch (commandEnum) {
      case OPEN_DATA_SERVER:  {
        cout << "connecting" << endl;
        break;
      }

      case CONNECT:  {
        cout << "connecting2" << endl;
        break;
      }

      case VAR:  {
        cout << "var" << endl;
        break;
      }

      case PRINT:  {
        PrintCommand *c = new PrintCommand((*it)[1]);
        this->commands_to_run.push_back(c);
        cout << "printing" << endl;
        break;
      }

      case SLEEP:  {
        cout << "sleeping" << endl;
        break;
      }

      case INIT:  {
        cout << "initializing" << endl;
        break;
      }

      case CONDITIONAL:  {
        cout << "Begining Scope" << endl;
        break;
      }

      default: {
        cout << "Ending Scope" << endl;
        break;
      }
    }
  }
}


void Interpreter::runCommands() {
  for (Command *c : this->commands_to_run) {
    c->execute();
  }
}

void Interpreter::run() {
  this->parseLexedDataToCommandsVector();
  this->runCommands();
}

