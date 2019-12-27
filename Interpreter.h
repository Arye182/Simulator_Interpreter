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
#include "DefineVarCommand.h"
#include "AssignVarCommand.h"
#include "ConnectCommand.h"



#include "OpenDataServerCommand.h"

using namespace std;

class Interpreter {
 private:

  // Raw Material
  vector<vector<string>> lexed_data_to_interpret;
  // commands to execute (we use map to indicate this shitty thing)
  PrintCommand* print_command = new PrintCommand();
  SleepCommand* sleep_command = new SleepCommand();
  OpenDataServerCommand* open_data_server_command = new OpenDataServerCommand();
  ConnectCommand* connect_command = new ConnectCommand();
  AssignVarCommand* assign_var_command = new AssignVarCommand();
  DefineVarCommand* define_var_command = new DefineVarCommand();

  // conditional package
  WhileCommand* while_command;
  IfCommand* if_command;
  bool is_if_command = false;
  bool is_while_command = false;
  string condition_string;
  vector<string> condition_vector_string;
  vector<vector<string>> while_strings_vectors;
  vector<Command*> while_commands_pointers;
  vector<vector<string>> if_strings_vectors;
  vector<Command*> if_commands_pointers;
  // map o(1) - with nice enumeration for switch
  enum simulatorCommand{
    OPEN_DATA_SERVER, CONNECT,
    DEFINE_VAR, PRINT, SLEEP, ASSIGN, WHILE, IF, END_CONDITION
  };
  map<string,simulatorCommand> CMD_DICTIONARY = {
      {"openDataServer", OPEN_DATA_SERVER},
      {"connectControlClient", CONNECT},
      {"var", DEFINE_VAR},
      {"Print", PRINT},
      {"Sleep", SLEEP},
      {"while", WHILE},
      {"if", IF},
      {"}" , END_CONDITION}
  };

 public:
  Interpreter(vector<vector<string>> lexed_data);
  ~Interpreter();
  bool belongToCondition (vector<string> condition_string_vector_arg, Command*
                    condition_command_pointer_arg);
  void parseLexedDataToCommandsVector();
  void run();
};

#endif //SIMULATUR_INTERPRETER__INTERPRETER_H_
