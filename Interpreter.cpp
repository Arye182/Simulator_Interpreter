//
// Created by arye on 15/12/2019.
//

#include "Interpreter.h"

Interpreter::Interpreter(vector<vector<string>> lexed_data) {
  this->lexed_data_to_interpret = lexed_data;
}

void Interpreter::parseLexedDataToCommandsVector() {
  int iteration = 0;

  // iterate all the data that came from the lexer
  for (auto it = this->lexed_data_to_interpret.begin(); it !=
       this->lexed_data_to_interpret.end(); ++it, ++iteration) {
    // the keyword we look for to know what will be the suitable command
    string command_string = (*it)[0];
    vector<string> command_string_vector = *it;
    // the key for switch
    int commandEnum;
    // check the
    if (this->CMD_DICTIONARY.find(command_string) != this->CMD_DICTIONARY.end()) {
      commandEnum = this->CMD_DICTIONARY[command_string];
    } else {
      commandEnum = ASSIGN; // cant really do that ah? TODO try to think
      // creatively with miri
    }

    // take a vector of strings and Execute it!
    switch (commandEnum) {
      case OPEN_DATA_SERVER:  {
        this->open_data_server_command->setParameters(command_string_vector);
        this->open_data_server_command->execute();
        cout << "opening a data server" << endl;
        break;
      }
      case CONNECT:  {
        cout << "connecting to the simulator" << endl;
        break;
      }
      case DEFINE_VAR:  {
        cout << "defining var (execute not ready yet)" << endl;
        break;
      }
      case SLEEP:  {
        if (this->belongToCondition(command_string_vector, this->sleep_command)) {
          break;
        } else {
          this->sleep_command->setParameters(command_string_vector);
          this->sleep_command->execute();
          break;
        }
      }
      case ASSIGN:  {
        cout << "assigning variable (execute not ready yet)" << endl;
        break;
      }
      case PRINT:  {
        if (this->belongToCondition(command_string_vector, this->print_command)) {
          break;
        } else {
          this->print_command->setParameters(command_string_vector);
          this->print_command->execute();
          break;
        }
      }
      case WHILE:  {
        this->is_while_command = true;
        // need to collect the commands in the vector :)
        this->condition_string = command_string_vector[1];
        cout << "Begining Scope of while loop" << endl;
        break;
      }
      case IF:  {
        // need to collect the commands in the vector :)
        this->is_if_command = true;
        this->condition_string = command_string_vector[1];
        cout << "Begining Scope of if condition" << endl;
        break;
      }
      case END_CONDITION: {
        // if condition
        if (this->is_if_command) {
          // create a new if
          this->if_command = new IfCommand(this->condition_string,
              this->if_commands_pointers, this->if_strings_vectors);
          // execute it (no set needed)
          this->if_command->execute();
          // delete the if
          delete(this->if_command);
          this->if_strings_vectors.clear();
          this->if_commands_pointers.clear();
        }
        // while condition
        else if (this->is_while_command) {
          // create a new while
          this->while_command = new WhileCommand(this->condition_string,
              this->while_commands_pointers, this->while_strings_vectors);
          this->while_command->execute();
          // delete the old while
          delete(this->while_command);
          this->while_strings_vectors.clear();
          this->while_commands_pointers.clear();
        }
        this->is_if_command = false;
        this->is_while_command = false;
        cout << "Ending Condition" << endl;
        break;
      }
      default: {
        break;
      }
    }
  }
}

void Interpreter::run() {
  this->parseLexedDataToCommandsVector();
}

bool Interpreter::belongToCondition(vector<string> condition_string_vector_arg,
    Command* condition_command_pointer_arg) {
  if (this->is_if_command) {
    this->if_commands_pointers.push_back(condition_command_pointer_arg);
    this->if_strings_vectors.push_back(condition_string_vector_arg);
    return true;
  } else if (this->is_while_command) {
    this->while_commands_pointers.push_back(condition_command_pointer_arg);
    this->while_strings_vectors.push_back(condition_string_vector_arg);
    return true;
  } else return false;
}




