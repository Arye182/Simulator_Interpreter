//
// Created by arye on 17/12/2019.
//

#ifndef SIMULATOR_INTERPRETER__LEXER_H_
#define SIMULATOR_INTERPRETER__LEXER_H_

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Lexer {
 private:
  string flight_text_file;
  vector<vector<string>> text_commands_lexed;
  vector<string> operators_to_check = {"<-", "->", "<=", ">=", "<", ">", "="};

 public:
  Lexer(string file_Name);
  static string removeToken(string line, char token);
  vector<vector<string>> lexTheFlightTextFile();
  string trim(const std::string &s);
  ~Lexer() = default;
};

#endif //SIMULATOR_INTERPRETER__LEXER_H_
