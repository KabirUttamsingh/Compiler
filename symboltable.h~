#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H
#include "hashTable.h"
#include <iostream>
#include <string>
#include <cstring>
#include <sstream>
#include "stack.cc"
//#include "stack.h"
#include <stdlib.h>
//#include "hashTable.cc"
//#include "hash.h"
//#include "hash.cc"

using namespace std;
class Symboltable
{
  public:
  void enterScope();
  void  exitScope();
  int addSymbol(string sym);
  string getUniqueSymbol(string sym);

  
  Symboltable();
  ~Symboltable();
  private:
  Stack<HashTable> table;
  int index;
  
};

  #endif
