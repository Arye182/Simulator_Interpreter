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
    parser->run();
    // delete memory
    delete parser;
    delete lexer;
  } catch (string msg) {
    cout << msg << endl;
  }
  //TODO
  //data_base.setRunning(false);
  // delete allocated memory from the data
  //data_base.deleteMemory();
  // close the pthread
  pthread_exit(nullptr);
}

