//
// Created by arye on 17/12/2019.
//

#include "Lexer.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <map>

using namespace std;
using std::string;

/**
 *
 * @param userFileName
 */
Lexer::Lexer(string userFileName) {
  this->flight_text_file = userFileName;
}

/**
 *
 * @param line
 * @param token
 * @return
 */
string Lexer::removeToken(string line, char token) {
  string::iterator end_pos = std::remove(line.begin(), line.end(), token);
  line.erase(end_pos, line.end());
  return line;
}

/**
 *
 * @return
 */
vector<vector<string>> Lexer::lexTheFlightTextFile() {

  ifstream inFile; // open the file stream
  inFile.open(this->flight_text_file);
  if (inFile.fail()) { // check if opening a file failed
    cerr << "Error opeing a file" << endl;
    inFile.close();
    exit(1);
  }
  string line;
  // lex line after line - i chose to work in the onion slicing method
  while (getline(inFile, line)) {
    if (line.empty()) {
      continue;
    }
    // get rid of tabs
    line = trim(line);
    vector<string> command_vector;
    // important keyword i look for in the string
    string::size_type has_while = line.find("while");
    string::size_type has_if = line.find("if");
    string::size_type has_var = line.find("var");
    string::size_type has_left_parent = line.find('(');
    string::size_type has_sim = line.find("sim");
    string::size_type has_print = line.find("Print");
    string::size_type has_end_condition = line.find('}');
    map<int, string> has_key_words = {{has_while, "while"}, {has_if, "if"},
                                      {has_var, "var"}};
    // NOT var / while / if :
    if (has_if == string::npos && has_while == string::npos && has_var ==
        string::npos) {
      // get rid of spaces in case its not a print
      if (has_print == string::npos) {
        line = this->removeToken(line, ' ');
      }
      // assignments (set vars)
      if (line.find('=') != string::npos) {
        command_vector.push_back(line);
      } else if (has_left_parent != string::npos) {
        string left = line.substr(0, has_left_parent);
        left = this->removeToken(left, '(');
        command_vector.push_back(left);
        string right = line.erase(0, has_left_parent);
        right = this->removeToken(right, '(');
        right = this->removeToken(right, ')');
        right = this->removeToken(right, '"');
        command_vector.push_back(right);
      }
    } else {
      // var / while / if :
      // dont minimize spaces after the keyword while, if, var
      // put the keyword in a command vector and remove her from line :)
      for (auto it = has_key_words.begin(); it != has_key_words.end(); ++it) {
        if (string::size_type(it->first) != string::npos) {
          command_vector.push_back(it->second);
          line.erase(it->first, it->second.size());
          line = this->removeToken(line, ' ');
        }
      }
      // find "<-" , "->" , "=", "<=" , "<", ">" , ">=" .
      // put every part (left, keyword, right" inside command vector
      for (string op : this->operators_to_check) {
        string::size_type has_op = line.find(op);
        if (has_op != string::npos) {
          string left = line.substr(0, has_op);
          left = this->removeToken(left, '(');
          command_vector.push_back(left);
          line.erase(0, has_op);
          command_vector.push_back(op);
          line.erase(0, op.size());
          string right = line;
          if (has_sim != string::npos) {
            left = line.substr(0, 4);
            left = this->removeToken(left, '(');
            command_vector.push_back(left);
            line.erase(0, 4);
            string sec_right = line;
            if (op == "<-" || op == "->") {
              sec_right = this->removeToken(sec_right, ')');
            }
            sec_right = this->removeToken(sec_right, '"');
            command_vector.push_back(sec_right);
            break;
          }
          if (op == "<-" || op == "->") {
            right = this->removeToken(right, ')');
          }
          right = this->removeToken(right, '{');
          command_vector.push_back(right);
          break;
        }
      }
    }
    if (has_end_condition != string::npos) {
      command_vector.push_back("}");
    }
    text_commands_lexed.push_back(command_vector);
  }
  // close the file stream
  inFile.close();
  // return the vector of vectors :) (all the strings representing commands)
  return this->text_commands_lexed;
}

/**
 *
 * @param s
 * @return
 */
string Lexer::trim(const std::string &s) {
  auto start = s.begin();
  while (start != s.end() && std::isspace(*start)) {
    start++;
  }
  auto end = s.end();
  do {
    end--;
  } while (std::distance(start, end) > 0 && std::isspace(*end));
  return std::string(start, end + 1);
}
