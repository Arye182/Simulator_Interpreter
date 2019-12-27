//
// Created by arye on 19/12/2019.
//

#include "RunProgramm.h"

RunProgramm::RunProgramm(string file) {
  this->file_name = file;
}

void RunProgramm::run() {
  // create a new Lexer
  Lexer *lexer = new Lexer(this->file_name);
  // lex the txt file to vector of (vectors of strings)
  vector <vector<string>> lexer_data = lexer->lexTheFlightTextFile();
  // create a new interpreter - lexer
  Interpreter *parser = new Interpreter(lexer_data);
  try {
    // run the commands with the help of the lexer
    parser->run();
    // delete memory of parser and lexer
    delete parser;
    delete lexer;
  } catch (const char* msg) {
    cout << msg << endl;
  }
  // delete allocated memory from the data
  DataBase::getInstance()->deleteDataBase();
  // close the pthread
  pthread_exit(nullptr);
}

