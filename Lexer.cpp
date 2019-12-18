//
// Created by arye on 17/12/2019.
//

#include "Lexer.h"
#include <fstream>
#include <algorithm>
#include <list>
#include "Interpreter.h"
#include <iostream>
#include <cstring>
#include <sstream>
#include <string>
using namespace std;
using std::string;



Lexer::Lexer(string userFileName) {
  this->flight_text_file = userFileName;
}
string Lexer::removeSpaces(string line){
  string::iterator end_pos = std::remove(line.begin(), line.end(),' ');
  line.erase(end_pos, line.end());
  return line;
}
vector<vector<string>> Lexer::lexTheFlightTextFile(){
  ifstream inFile;
  // open the file stream
  inFile.open(this->flight_text_file);
  // check if opening a file failed
  if (inFile.fail()) {
    cerr << "Error opeing a file" << endl;
    inFile.close();
    exit(1);
  }
  string line;
  // lex line after line - i chose to work in the onion slicing method
  while (getline(inFile, line))
  {
    vector<string> command_vector;
    // important keyword i look for in the string
    int has_while = line.find("while");
    int has_if = line.find("if");
    int has_var = line.find("var");
    // minimize all spaces in the string
    if (has_if != string::npos && has_while != string::npos && has_var != string::npos) {
      line = this->removeSpaces(line);
    } else { // dont minimize spaces after the keyword while, if, var
      // TODO
      // put the keyword in a command vector and remove her from line :)

      // take the rest of the line and minimize her for spaces

      // parse the rest of line

          // find "<-" , "->" , "=", "<=" , "<", ">" , ">=" .
          // put every part (left, keyword, right" inside command vector
              // for each string in the command vector do this shit:

                  // find the sograim and split them into two pieces "()"
                  // insert left and right to the fucking command vector and
                  // then delete the origin ones.
    }


    //insert command to the commands vector
    this->text_commands_lexed.push_back(command_vector);
    cout << line << endl;
  }
  // close the file stream
  inFile.close();
  // return the vector of vectors :) (all the strings representing commands)
  return this->text_commands_lexed;
}
