#ifndef PARSER_H
#define PARSER_H
#include "token.h"
#include "lexer.h"
#include "symboltable.h"
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <sstream>

using namespace std;

class Parser {
  
private:

  enum Operation {
    ADD, SUB, MULT, DIV, // Arithmetic Operators
    ISEQ, ISNE, ISLT, ISLE, ISGT, ISGE, // Relational Operators
    AND, OR, // Logical Operators
    PUSHL, PUSHV, STORE, // Value Transfer Instructions
    JUMP, JUMPF, JUMPT, CALL, RET, // Location Transfer Instructions
    PRINTF, // Misc
    LABEL, SEQ, FUNC, PARAM // Pseudo Operations
  };
  
public:  
  class TreeNode {
    
  public:

    Operation op;
    string val; // Variable name or jump label
    TreeNode *leftChild;
    TreeNode *rightChild;
    Symboltable table;
    // Utility function used by constructors
    void init(Operation opx, string valx, TreeNode *leftChildx, TreeNode *rightChildx) {
      op = opx;
      val = valx;
      leftChild = leftChildx;
      rightChild = rightChildx;
    }


    TreeNode(Operation op, string val) {
      init(op, val, NULL, NULL);
    }
    
    TreeNode(Operation op, string val, TreeNode *leftChild, TreeNode *rightChild) {
      init(op, val, leftChild, rightChild);
    }

    TreeNode(Operation op) {
      init(op, "", NULL, NULL);
    }

    TreeNode(Operation op, TreeNode *leftChild, TreeNode *rightChild) {
      init(op, "", leftChild, rightChild);
    }

    static string toString(TreeNode *node) {
      return toString0(node, 0);
    }
    
    static string toString0(TreeNode *node, int spaces) {
      static string blanks ="                                        ";
      string left = "";
      string right = "";
      bool isLeaf = true;
      if (node->leftChild != NULL) {
	left = toString0(node->leftChild, spaces+2);
	isLeaf = false;
      }
      if (node->rightChild != NULL) {
	right = toString0(node->rightChild, spaces+2);
	isLeaf = false;	
      }
      string ret;
      if (isLeaf) {
	ret = blanks.substr(0, spaces) + ops[node->op] + "[" + node->val + "]";
      } else {
	ret = blanks.substr(0, spaces) + ops[node->op] + "(\n" + left + ",\n" + right + "\n" + 
	      blanks.substr(0, spaces) + ")";
      }
      return ret;
    }
    
  };
  
private:
  Lexer lexer;
  Token token;
  ostream& out;
  int lindex;
  int tindex;
  int jindex;
  Symboltable table;
  string itos(int i) { stringstream ss; ss << i; string res = ss.str(); return res;}
  string makeLabel() { string tmp = "L"; stringstream ss; ss << ++lindex; string res = ss.str(); tmp = tmp + res; return tmp;}
  string JmakeLabel() { string tmp = "J"; stringstream ss; ss << ++jindex; string res = ss.str(); tmp = tmp + res; return tmp;}
  static const string ops[];
  //  string vars[100];
  // int vindex;
  void error(string message);
  void check(int tokenType, string message);
  //  string currentFunc;
  // int nfmts;
  // string fmts[100];
  // string fmt;
  // int nparams;
 public:
 
  TreeNode* funcall(string functionName);
  TreeNode* factor();
  TreeNode* term();
  TreeNode* expression();
  TreeNode* relationalExpression();
  TreeNode* logicalExpression();
  TreeNode* assignmentExpression();
  TreeNode* returnStatement();
  //  TreeNode* printfStatement();
  TreeNode* whileStatement();
  TreeNode* ifStatement();
  TreeNode* assignStatement();
  TreeNode* vardefStatement();  
  TreeNode* statement();
  TreeNode* block();
  TreeNode* parameterdef();
  TreeNode* parameterdefs();
  TreeNode* function();
  TreeNode* compilationunit();  
  TreeNode* printfStatement();
  void vardefs(TreeNode *node);
  void genasm(TreeNode *node);
  void emit(string a);
  void  genRelational(string a);
  void geninst(TreeNode *node);
  bool isNew(string a);
  Parser(Lexer& lexer, ostream& out);
  ~Parser(); 

};

#endif
