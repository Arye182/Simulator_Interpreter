#include <iostream>
#include "Interpreter.h"
#include "OpenDataServerCommand.h"
#include "Lexer.h"
#include "DataBase.h"
#include <vector>
#include <string>

#define FILE_NAME_ARG_INDEX 1

DataBase data_base;

/**
 * Run the program
 * activates the lexer, and parser (interpreter class) the parser runs
 * the commands of flight.
 * @param file_name is the file name to read from.
 */
void run(string file_name) {
  Lexer *lexer = new Lexer(file_name);
  vector <vector<string>> lexer_data = lexer->lexTheFlightTextFile();
  //TODO - interpreter :)
  //Interpreter *parser = new Interpreter(lexer_data);
//  try {
//    parser->run();
//    // delete memory
//    delete parser;
//    delete lexer;
//  } catch (string msg) {
//    cout << msg << endl;
//  }
}

/**
 * Main
 * @param argc
 * @param argv includes the file name of the script.
 */
int main(int argc, char *argv[]) {
  // notify that we start to run the program
  //TODO
  //data_base.setRunning(true);
  run(argv[FILE_NAME_ARG_INDEX]);
  //TODO
  //data_base.setRunning(false);
  // delete allocated memory from the data
  //data_base.deleteMemory();
  // close the pthread
  pthread_exit(nullptr);
}
