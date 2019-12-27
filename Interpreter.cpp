//
// Created by arye on 15/12/2019.
//

#include "Interpreter.h"

static DataBase* data = DataBase::getInstance();

Interpreter::Interpreter(vector<vector<string>> lexed_data) {
  this->lexed_data_to_interpret = lexed_data;
}

void Interpreter::parseLexedDataToCommandsVector() {

  int iteration = 0;
  // begin read text
  data->setIsRunning(true);
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
      commandEnum = ASSIGN;
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
        this->connect_command->setParameters(command_string_vector);
        this->connect_command->execute();
        cout << "connecting to the simulator" << endl;
        break;
      }
      case DEFINE_VAR:  {
        if (this->belongToCondition(command_string_vector, this->define_var_command)) {
          break;
        } else {
          this->define_var_command->setParameters(command_string_vector);
          if (data->sim_var_map_lock.try_lock() && data->in_var_map_lock.try_lock()) {
            this->define_var_command->execute();
            cout << "defining var "<< command_string_vector[1] << endl;
            //data->printInVarMap();
            data->sim_var_map_lock.unlock();
            data->in_var_map_lock.unlock();
          } else {
            cout << "maps are locked by setSimData" << endl;
          }
          break;
        }

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
        // case it belongs to condition
        if (this->belongToCondition(command_string_vector, this->assign_var_command)) {
          break;
        } else {
          // case its just to execute
          this->assign_var_command->setParameters(command_string_vector);
          if (data->sim_var_map_lock.try_lock() && data->in_var_map_lock.try_lock()) {
            this->assign_var_command->execute();
            // unlock the maps
            data->sim_var_map_lock.unlock();
            data->in_var_map_lock.unlock();
          } else {
            cout<< "maps are locked by setSimData" << endl;
          }
          break;
        }
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

        this->condition_vector_string = command_string_vector;
        cout << "Begining Scope of while loop" << endl;
        break;
      }
      case IF:  {
        // need to collect the commands in the vector :)
        this->is_if_command = true;
        this->condition_string = command_string_vector[1];
        this->condition_vector_string = command_string_vector;
        cout << "Begining Scope of if condition" << endl;
        break;
      }
      case END_CONDITION: {
        // if condition
        if (this->is_if_command) {
          // create a new if
          this->if_command = new IfCommand(this->condition_vector_string,
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
          this->while_command = new WhileCommand(this->condition_vector_string,
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
  // end of text commands
  data->setIsRunning(false);
}

void Interpreter::run() {
  //data->sim_var_map_lock.unlock();
  //data->in_var_map_lock.unlock();
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

Interpreter::~Interpreter() {
  delete(this->connect_command);
  delete(this->open_data_server_command);
  delete(this->if_command);
  delete(this->print_command);
  delete(this->while_command);
  delete(this->sleep_command);
  delete(this->assign_var_command);
  delete(this->define_var_command);
}




