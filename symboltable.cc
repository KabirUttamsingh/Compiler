/*
          CSE 109
	                Kabir Uttamsingh
			                    kku219
					                              Program
	                Description: Program #6
*/
#include "symboltable.h"
//#include "hashTable.h"
#include <cstring>
#include <iostream>
#include <sstream>

string itos(int i) { stringstream ss; ss << i; string res = ss.str(); return res;}

Symboltable:: Symboltable(): index(1)
{

}
Symboltable::~Symboltable()
{

}


string Symboltable:: getUniqueSymbol(string sym)
{
  for(int i = table.getTos(); i >= 0; --i)
  {
      HashTable& temp = table[i];
	if (temp.inTable(sym))
	  {
	    return temp[sym];
          }
   }
    
      return "";
}
int Symboltable:: addSymbol(string sym)
{
  HashTable top = table.peek();
  if(top.inTable(sym)){
    return 0;
  }
  table.peek().add( sym, sym + "$" + itos(index++)); 
  return 1;
}

void Symboltable:: enterScope()
{
  table.push(HashTable(53));
}

void  Symboltable:: exitScope()
{
  table.pop();
}
