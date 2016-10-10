/*
    CSE 109
      Kabir Uttamsingh
        kku219
	  ) Program Description: Program #4
*/


#ifndef LEXER_H
#define LEXER_H
#include <iostream>
#include "token.h"
#include <cstdlib>
#include <string>
using namespace std;
class Lexer
{
public:
  Lexer(istream& i);
  ~Lexer();
  char nextChar();
  Token nextToken();
private:
  istream &store;
  int line;
  int pos;
  char ch;
  string array [31];
  
};
#endif
