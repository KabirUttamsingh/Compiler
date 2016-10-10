/*
    CSE 109
      Kabir Uttamsingh
        kku219
	  ) Program Description: Program #4
*/


#include <iostream>
#include <string>
#include "token.h"
#include <cstdlib>
using namespace std;


Token:: Token()
{
  type = 0;
  lexeme = "";
  line = 1;
  pos = 0;
}

Token:: Token( int type1, string lexeme1, int line1, int pos1)
{

  type = type1;
  lexeme = lexeme1;
  line = line1;
  pos = pos1;

}

Token:: ~Token()
{
}

int Token :: getType()
{

  return type;
}

string Token ::getLexeme()
{

  return lexeme;

}

int Token :: getLine()
{

  return line;
}

int Token ::getPos()
{

  return pos;

}
