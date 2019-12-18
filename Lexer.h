//
// Created by arye on 17/12/2019.
//

#ifndef SIMULATOR_INTERPRETER__LEXER_H_
#define SIMULATOR_INTERPRETER__LEXER_H_

#include <string>
#include <vector>

using namespace std;

class Lexer {
 private:
  string flight_text_file;
  vector<vector<string>> text_commands_lexed;
 public:
  /**
 * Ctor
 * @param userFileName
 */
  Lexer(string file_Name);
  /*
 * Split - this function take a string and delimeter and returns vector of s
 *
 * @param userFileName
 */
  string removeSpaces(string line);
  /* the function that lex the text file from user into vector(dynamic array)
   * of strings
  */
  vector<vector<string>> lexTheFlightTextFile();
};

#endif //SIMULATOR_INTERPRETER__LEXER_H_
