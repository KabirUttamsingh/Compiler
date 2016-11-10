/*
        CSE 109
	      Kabir Uttamsingh
	            kku219
		          Program Description: Program #5
*/
#include "parser.h"
#include <cstring>

const string Parser::ops[] = {"ADD", "SUB", "MULT", "DIV",

		      "ISEQ", "ISNE", "ISLT", "ISLE", "ISGT", "ISGE",

		      "AND", "OR",

		      "PUSHL", "PUSHV", "STORE",

		     "JUMP", "JUMPF", "JUMPT", "CALL", "RET",

		      "PRINTF", "LABEL", "SEQ" , "FUNC" , "PARAM" };

Parser::Parser(Lexer& lexerx, ostream& outx): lexer(lexerx), out(outx), lindex(1), tindex(1) {
  token = lexer.nextToken();
  
}

Parser::~Parser() {
}

void Parser::error(string message)
{
  cerr << message << " Found " << token.getLexeme() << " at line " << token.getLine() << " position " << token.getPos() << endl;
  exit(1);
}

void Parser::check(int tokenType, string message) {
  if (token.getType() != tokenType)
    error(message);
}

Parser::TreeNode* Parser::factor()  
{
  TreeNode* node;
  if (token.getType()== Token::LPAREN)
    {          
      node = expression();
      check(Token::RPAREN,"Expecting )");
      return node;
    }
  if (token.getType() == Token::INTLIT)
    {
     
     node = new TreeNode(Parser::PUSHL,token.getLexeme());
     token = lexer.nextToken();
     return node;
    }
  if (token.getType() == Token::IDENT)
    {
      string a = token.getLexeme();
      string sym = table.getUniqueSymbol(a);
      if(sym == "")
	{
	  error("symbol not declared");
	}
      
      if(lexer.nextToken().getType() == Token::LPAREN)
	{
	  node = funcall(a);
	}
      else
	{
      node = new TreeNode(Parser::PUSHV, sym);
      token = lexer.nextToken();
	}
      return node;
    }
  error("Expected identifier or literal");
  return new TreeNode(Parser::SEQ);
}

Parser::TreeNode* Parser::term()
{
  TreeNode* termNode = factor();
  TreeNode* factorNode;
 
  while((token.getType() == Token::TIMES || token.getType() == Token::DIVIDE))
    {
      int tokenType = token.getType();
      token = lexer.nextToken();
      factorNode = factor();
      Operation op;      
      switch(tokenType)
	{
	case Token:: TIMES: op = Parser::MULT;
	  break;
	  
	case Token::DIVIDE: op = Parser::DIV;
	  break;
	}
      
      termNode = new TreeNode(op, termNode, factorNode);
      tokenType = token.getType();
    }
  return termNode;
}

Parser::TreeNode* Parser::expression()       
{
  TreeNode* expressionNode = term();
  TreeNode* termNode;

  while ((token.getType() == Token:: PLUS || token.getType() == Token:: MINUS))
    {
      int tokenType = token.getType();
      token = lexer.nextToken();
      termNode = term();

      Operation op;

      switch(tokenType)
	{
	case Token::PLUS: op = Parser::ADD;
	break;

	case Token::MINUS: op = Parser::SUB;
	break;
	}
      expressionNode = new TreeNode(op, expressionNode, termNode);
      tokenType = token.getType();
    }
  return expressionNode;

}

Parser::TreeNode* Parser::relationalExpression()
{
  TreeNode* node = expression();
 
  if(token.getType() == Token :: EQ)
    {
      token = lexer.nextToken();
      node = new TreeNode(Parser::ISEQ,node, expression());
      
      
    }
  if(token.getType() == Token :: LT)
    {
      token = lexer.nextToken();
      node = new TreeNode(Parser::ISLT,node, expression());
            
    }
  if(token.getType() == Token :: LE)
    {
      token = lexer.nextToken();
      node = new TreeNode(Parser::ISLE,node, expression());
      
      
    }
  if(token.getType() == Token :: GT)
    {
      token = lexer.nextToken();
      node = new TreeNode(Parser::ISGT, node, expression());
    }
  if(token.getType() == Token::GE)

    {
      token = lexer.nextToken();
      node = new TreeNode(Parser::ISGE, node, expression());
      
    }
  if(token.getType() == Token :: NE)
    {
      token = lexer.nextToken();
      node = new TreeNode(Parser::ISNE, node, expression());
    }
  return node;
}

Parser::TreeNode* Parser::logicalExpression()
{
  TreeNode* logicalNode = relationalExpression();
  TreeNode* relationalNode;

  while ((token.getType() == Token :: AND) || (token.getType() == Token:: OR))
    {
      int tokenType = token.getType();
      token = lexer.nextToken();
      relationalNode = relationalExpression();

      Operation op;

      switch(tokenType)
	{
	case Token::AND: op =Parser:: AND;
	break;

	case Token::OR: op =Parser:: OR;
	break;
	}
      logicalNode = new TreeNode(op, logicalNode, relationalNode);
      tokenType = token.getType();
    }
  return logicalNode;
}

Parser::TreeNode* Parser::ifStatement() 
{
  string l1 = makeLabel();
  string l2 = makeLabel();
  check(Token::IF, "Expecting IF");
  token = lexer.nextToken();
  check(Token::LPAREN, "Expecting (");
  token = lexer.nextToken();
  TreeNode* log = logicalExpression();
  check(Token::RPAREN,"Expecting )");
  TreeNode* jump1 = new TreeNode(Parser::JUMPF,l1);
  log = new TreeNode(Parser::SEQ, log, jump1);
  token = lexer.nextToken();
  table.enterScope();
  TreeNode* ifblock = block();
  table.exitScope();
  log = new TreeNode(Parser::SEQ, log, ifblock);
  TreeNode* label1 = new TreeNode(Parser::LABEL,l1);
  TreeNode* label2 = new TreeNode(Parser::LABEL,l2);
  
  if(token.getType() == Token::ELSE)
    {
      token = lexer.nextToken();
      table.enterScope();
      TreeNode* elseblock = block();
      table.enterScope();
      TreeNode* jump2 = new TreeNode(Parser::JUMP, l2);
      log = new TreeNode(Parser::SEQ, log, jump2);
      log = new TreeNode(Parser::SEQ, log, label1);
      log = new TreeNode(Parser::SEQ, log, elseblock);
      log = new TreeNode(Parser::SEQ, log, label2);
    }
    else
    {
      log = new TreeNode(Parser::SEQ, log, label1);
     
    }
      return log;
}

Parser :: TreeNode* Parser:: block()
{
  TreeNode* node;
  check(Token::LBRACE,"Expecting {");
  table. enterScope();
  token = lexer.nextToken();
  if(token.getType()==Token::RBRACE)
    {
      return new TreeNode(Parser::SEQ, NULL, NULL);
    }
  node = statement();
  while(token.getType() != Token::RBRACE)
    {
      node = new TreeNode(Parser::SEQ,node, statement());
      token = lexer.nextToken();
    }
  return node;

}


Parser::TreeNode* Parser:: whileStatement()
{
      string l1 = makeLabel();
      string l2 = makeLabel();
      check(Token::WHILE, "Expected WHILE");
      token = lexer.nextToken();
      check(Token::LPAREN, "Expected (");
      token = lexer.nextToken();
      TreeNode* log = logicalExpression();
      check(Token::RPAREN, "Expecting )");
      token = lexer.nextToken();
      table.enterScope();
      TreeNode* block1 = block();
      table.exitScope();
      TreeNode* label1 = new TreeNode(Parser::LABEL,l1);
      TreeNode* label2 = new TreeNode(Parser::LABEL,l2);
      log = new TreeNode(Parser::SEQ, label1, log);
      
      TreeNode* jump1 = new TreeNode(Parser::JUMPF,l2);
      log = new TreeNode(Parser::SEQ, log, jump1);
      log = new TreeNode(Parser::SEQ, log, block1);
      TreeNode* jump2 = new TreeNode(Parser::JUMP,l1);
      log = new TreeNode(Parser::SEQ,log,jump2);
      log= new TreeNode(Parser::SEQ,log,label2);
      
      return log;
}

Parser::TreeNode* Parser:: assignStatement() 
{
  TreeNode* node;
  check(Token::IDENT, "Expecting IDENT");
  string lex = token.getLexeme();
  TreeNode* a = new TreeNode(STORE, lex);
  token = lexer.nextToken();
  check(Token::ASSIGN, "Expecting =");
  token = lexer.nextToken();
  node = logicalExpression();
  check(Token::SEMICOLON, "Expecting ;");

  TreeNode* assignNode = new TreeNode(SEQ,node,a);
  //   token = lexer.nextToken();
  return assignNode;
}
Parser::TreeNode* Parser:: statement() 
{
  TreeNode* node;
  if(token.getType() == Token::WHILE)
    {
      node = whileStatement();
      return node;
    }
 else if(token.getType() == Token ::IDENT)
    {
      node = assignStatement();
      return node;
    }
  else if(token.getType() == Token :: IF)
    {
      node = ifStatement();
      return node;
    }
      else if(token.getType() == Token:: VAR)
    {
      node = vardefStatement();
      return node;
      }
  else if(token.getType() == Token:: RETURN)
    {
      node = returnStatement();
      return node;

      }
  else 
    {
    return NULL;
    }
}

Parser::TreeNode* Parser:: funcall(string functionName)
{
  TreeNode* node;
  check(Token::IDENT,"Expecting IDENT");
  token = lexer.nextToken();
  if(token.getType()== Token::LPAREN)
    {
      token = lexer.nextToken();
      while(token.getType()!= Token::RPAREN)
	{
	  node = new TreeNode(Parser::SEQ,expression(),new TreeNode(Parser::CALL, functionName));
	  token = lexer.nextToken();
	}
      node = new TreeNode(Parser::CALL, functionName);
    }
  else
    {
      node = new TreeNode(Parser::PUSHV, token.getLexeme());
      token = lexer.nextToken();
    }
  return node;
}
Parser::TreeNode* Parser:: returnStatement()  
{
  TreeNode* node;
  check(Token::RETURN, "Expecting return");
  token = lexer.nextToken();
  node = new TreeNode(SEQ,logicalExpression(), new TreeNode(Parser::RET)); 
  check(Token::SEMICOLON,"Expecting ;");
  return node;
}
Parser::TreeNode* Parser:: compilationunit()  
{
  TreeNode*node = function();
  while(token.getType() == Token::FUNCTION)
    {
      node = new TreeNode(SEQ,node, function());
      token = lexer.nextToken();
    }
  return node;
}
Parser::TreeNode* Parser:: vardefStatement()  
{
 
  check(Token::VAR, "Expecting var");
  token = lexer.nextToken();
  check(Token::IDENT, "Expecting IDENT");
  if(table.getUniqueSymbol(token.getLexeme())!="")
    {
      error("already declared");
    }
  table.addSymbol(token.getLexeme());
  token = lexer.nextToken();
  while(token.getType()==Token::COMMA)
    {
      token = lexer.nextToken();
      check(Token::IDENT, "Expecting IDENT");
     
      table.addSymbol(token.getLexeme());
      token = lexer.nextToken();
    }
  check(Token::SEMICOLON,"Expecting ;");
    return new TreeNode(SEQ);
}

Parser::TreeNode* Parser:: parameterdef()   
{
  TreeNode* node;
  check(Token::IDENT, "Expecting IDENT");
  node = new TreeNode(Parser::PARAM, token.getLexeme());
  token = lexer.nextToken();
  return node;
}


Parser::TreeNode* Parser:: parameterdefs()  
{
  if(token.getType() != Token::IDENT)
    {
      return new TreeNode(SEQ);
    }
  TreeNode* node = parameterdef();
  while(token.getType()==Token::COMMA)
    {
      token = lexer.nextToken();
      node = new TreeNode(SEQ,node,parameterdef());      
    }
  return node;
}

Parser::TreeNode* Parser:: function()  
{
  int index = 0;
  TreeNode* node;
  check(Token::FUNCTION, "Expecting FUNCTION");
  token = lexer.nextToken();
  check(Token::IDENT, "Expecting IDENT");
  string name = token.getLexeme();
  token = lexer.nextToken();
  check(Token::LPAREN, "Expecting (");
  token = lexer.nextToken();
  string array[100];
  table.enterScope();
  if(token.getType()!=Token::RPAREN)
    {
      check(Token::IDENT, "Expecting param");
      string param = token.getLexeme();
      array[index] = param;
      index++;
      token = lexer.nextToken();
      while(token.getType() == Token::COMMA)
	{	 
	  token = lexer.nextToken();
	  param = token.getLexeme();
	  array[index] = param;
	  index++;
	  token = lexer.nextToken();
	}
    }
  
  check(Token::RPAREN, "Expecting )");
  token = lexer.nextToken();
  node = new TreeNode(FUNC, name);
  for(int i=index; i>=0; i--)
    {
      int add = table.addSymbol(array[i]);
      if(add==0)
	{
	  error("variable declared in scope");
	}
      string temp = table.getUniqueSymbol(array[i]);
      node = new TreeNode(SEQ,node,new TreeNode(Parser::PARAM,temp));
    }
  table.enterScope();
  TreeNode* blockn = block();
  table.exitScope();
  node = new TreeNode(SEQ,node,blockn);
  table.exitScope();
  return node;
}
