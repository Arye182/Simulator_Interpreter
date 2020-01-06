//
// Created by arye on 19/12/2019.
//

#include "RunProgramm.h"

/**
 * Ctor.
 * @param file
 */
RunProgramm::RunProgramm(string file) {
  this->file_name = file;
}

/**
 * run the program flow
 * activates the lexer, and parser (interpreter class) the parser runs
 * the commands of flight.
 */
void RunProgramm::run() {
  // create a new Lexer
  this->lexer = new Lexer(this->file_name);
  // lex the txt file to vector of (vectors of strings)
  vector<vector<string>> lexer_data = lexer->lexTheFlightTextFile();
  // create a new interpreter - lexer
  this->parser = new Interpreter(lexer_data);
  try {
    // run the commands with the help of the lexer
    parser->run();
  } catch (const char *msg) {
    cout << msg << endl;
  }
}

/**
 * Dtor.
 * closes what left..
 */
RunProgramm::~RunProgramm() {
  // delete memory of parser and lexer
  delete this->lexer;
  delete this->parser;
  // delete allocated memory from the data
  DataBase *data_to_delete = DataBase::getInstance();
  if (data_to_delete != nullptr) {
    delete (data_to_delete);
  }
}

