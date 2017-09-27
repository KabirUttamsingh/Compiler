/**
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

Parser::Parser(Lexer& lexerx, ostream& outx): lexer(lexerx), out(outx), lindex(1), tindex(1), jindex(0) {
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
      token = lexer.nextToken();
      node = expression();
      check(Token::RPAREN,"Expecting )");
      token = lexer.nextToken();
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
      string id = token.getLexeme();
      token = lexer.nextToken();
      /*string a = token.getLexeme();
      string sym = table.getUniqueSymbol(a);
      if(sym == "")
	{
	  error("symbol not declared");
	}
      */
      if(token.getType() == Token::LPAREN)
	{
	  node = funcall(id);
	}
      else
	{
	  string sym = table.getUniqueSymbol(id);
	  if(sym == "")
	    {
	      error("symbol not delcared");
	    }
	  node = new TreeNode(Parser::PUSHV, sym);
	}
      //       token = lexer.nextToken();
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
  token = lexer.nextToken();
  log = new TreeNode(Parser::SEQ, log, ifblock);
  TreeNode* label1 = new TreeNode(Parser::LABEL,l1);
  TreeNode* label2 = new TreeNode(Parser::LABEL,l2);
  
  if(token.getType() == Token::ELSE)
    {
      token = lexer.nextToken();
      table.enterScope();
      TreeNode* elseblock = block();
      table.exitScope();
      token = lexer.nextToken();
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
  token = lexer.nextToken();
  if(token.getType()==Token::RBRACE)
    {
      return new TreeNode(Parser::SEQ, NULL, NULL);
    }
  node = statement();
  while(token.getType() != Token::RBRACE)
    {
      node = new TreeNode(Parser::SEQ,node, statement());
      //    token = lexer.nextToken();
    }
  //  token = lexer.nextToken();
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
      token = lexer.nextToken();
      return log;
}

Parser::TreeNode* Parser:: assignStatement() 
{
  TreeNode* node;
  check(Token::IDENT, "Expecting IDENT");
  string lex = token.getLexeme();
  string sym = table.getUniqueSymbol(lex);
  if(sym == "")
    {
      error("Symbol not declared");
    }
  TreeNode* a = new TreeNode(STORE, sym);
  token = lexer.nextToken();
  check(Token::ASSIGN, "Expecting =");
  token = lexer.nextToken();
  node = logicalExpression();
  check(Token::SEMICOLON, "Expecting ;");

  TreeNode* assignNode = new TreeNode(SEQ,node,a);
    token = lexer.nextToken();
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
  else if(token.getType() == Token::PRINTF)
    {
      node = printfStatement();
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
  if(token.getType()== Token::LPAREN)
    {
      token = lexer.nextToken();
      if(token.getType() == Token::RPAREN)
	{
      node = new TreeNode(Parser::CALL, functionName);
	}
      else
	{
	  node = expression();
	}
      while(token.getType()!= Token::RPAREN)
	{
	  token = lexer.nextToken();
	  node = new TreeNode(Parser::SEQ, node, expression());
	  if(token.getType()== Token::COMMA)
	    {
	  token = lexer.nextToken();
	    }
	}
    }
  node = new TreeNode(Parser::SEQ,node, new TreeNode(Parser::CALL, functionName));
  check(Token::RPAREN, "EXPECTING RPAREN");
  token = lexer.nextToken();
  return node;
}
Parser::TreeNode* Parser:: returnStatement()  
{
  TreeNode* node;
  check(Token::RETURN, "Expecting return");
  token = lexer.nextToken();
  node = new TreeNode(SEQ,logicalExpression(), new TreeNode(Parser::RET)); 
  check(Token::SEMICOLON,"Expecting ;");
  token = lexer.nextToken();
  return node;
}

Parser::TreeNode* Parser:: compilationunit()  
{
  TreeNode*node = function();
      while(token.getType() == Token::FUNCTION)
	{
	  node = new TreeNode(SEQ,node, function());
	  //token = lexer.nextToken();
	}
    
  return node;
}
Parser::TreeNode* Parser::printfStatement()
{
  TreeNode* paramList = NULL;
  int nparams = 0;
  check(Token::PRINTF, "Expecting printf");
  token = lexer.nextToken();
  check(Token::LPAREN, "Expecting (");
  token = lexer.nextToken();
  check(Token::STRINGLIT, "Expecting string literal");
  string formatString = token.getLexeme();
  token = lexer.nextToken();
  if (token.getType() == Token::COMMA) {
    token = lexer.nextToken();
    paramList = expression();
    ++nparams;
    while (token.getType() == Token::COMMA) {
      token = lexer.nextToken();
      paramList = new TreeNode(SEQ, paramList, expression());
      ++nparams;
    }
  }
  check(Token::RPAREN, "Expecting )");
  token = lexer.nextToken();
  check(Token::SEMICOLON, "Expecting ;");
   token = lexer.nextToken();
  TreeNode* printStatement =
    new TreeNode(SEQ, paramList, new TreeNode(PRINTF, itos(nparams) + formatString));
  return printStatement;
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
      if(table.getUniqueSymbol(token.getLexeme())!="")
	{
	  error("already declared");
	}
      table.addSymbol(token.getLexeme());
      token = lexer.nextToken();
    }
  check(Token::SEMICOLON,"Expecting ;");
  token = lexer.nextToken();
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
     
      token = lexer.nextToken();
      while(token.getType() == Token::COMMA)
	{
	  index++;
	  token = lexer.nextToken();
	  param = token.getLexeme();
	  array[index] = param;
	  token = lexer.nextToken();
	}
    }  
  check(Token::RPAREN, "Expecting )");
  token = lexer.nextToken();
  node = new TreeNode(FUNC, name + ":");
  if(array[index] != "")
    {
  for(int i=index; i>=0; i--)
    {
      int add = table.addSymbol(array[i]);
      if(add==0)
	{
	  error("variable declared in scope");
	}
      string temp = table.getUniqueSymbol(array[i]);
      node = new TreeNode(SEQ,node,new TreeNode(Parser::STORE,temp));
    }
    }
  TreeNode* blockn = block();
  table.exitScope();
  node = new TreeNode(SEQ,node,blockn);
  token = lexer.nextToken();
  return node;
}

string vars[100];
int vin;

void Parser:: vardefs(TreeNode *node)
{
  if(node == NULL)
    {
      return;
    }
  vardefs(node->leftChild);
  vardefs(node->rightChild);
  Operation temp = node->op;
  if(temp == Parser::PUSHV || temp == Parser::STORE)
    {
      if(isNew(node->val))
	{
	  vars[vin] = node->val;
	  vin++;
	}
    }
}

bool Parser:: isNew(string a)
{
  
  for(int i = vin; i>=0; i--)
    {
      if(vars[i] == a)
	{
	  return false;
	}
    }
  return true;
}

string currentFunc;
int nfmts = 0;
string fmts[100];

void Parser:: genasm(TreeNode *node)
{
  vin = 0;
  emit("  global main");
  emit("  extern printf");
  emit("      ");
  emit("  segment .bss");
  vardefs(node);
  for( int i = 0; i < vin; ++i)
    {
     
      emit("  " + vars[i] +" resq 1");
	
    }
  
  emit("    ");
  emit("    ");
  emit("  section .text");
  geninst(node);
  cout << endl << "  section .data" << endl;

    for (int i=0; i < nfmts; ++i) {

    cout << "  fmt" << i+1 << ": db " << fmts[i] << ", 0" << endl;

    }
}
void Parser:: emit(string a)
{
  cout << a << endl;

}
void Parser:: genRelational(string a)
{
  string j1 = JmakeLabel();
  string j2 = JmakeLabel();
  emit("  pop rbx");
  emit("  pop rax");
  emit("  cmp rax,rbx");
  if(a == "je")
    {
      emit("  je " + j1);
    }
  else if(a == "jne")
    {
      emit("  jne " + j1);
    }
  else if(a == "jl")
    {
      emit("  jl " + j1);
    }
  else if(a == "jle")
    {
      emit("  jle " + j1);
    }
  else if(a == "jg")
    {
      emit("  jg "+ j1);
    }
  else if(a == "jge")
    {
      emit("  jge " + j1);
    }
  else
    {
      error("wrong instruction");
    }
  emit("  mov rax,0");
  emit("  jmp " + j2);
  emit(j1+":");
  emit("  mov rax, 1");
  emit(j2+":");
  emit("  push rax");
}
void Parser:: geninst(TreeNode *node)
{
   string fmt;
    int nparams;
  if( node == NULL)
    {
      return;
    }
  geninst(node->leftChild);
  geninst(node->rightChild);
  Operation temp = node->op;

  switch(temp)
    {

    case Parser::ADD:
      emit("  pop rbx");
      emit("  pop rax");
      emit("  add rax,rbx");
      emit("  push rax");
      break;

    case Parser::SUB:
      emit("  pop rbx");
      emit("  pop rax");
      emit("  sub rax,rbx");
      emit("  push rax");
      break;
    case Parser::AND:
      emit("  pop rbx");
      emit("  pop rax");
      emit("  and rax,rbx");
      emit("  push rax");
      break;
    case Parser::OR:
      emit("  pop rbx");
      emit("  pop rax");
      emit("  or rax,rbx");
      emit("  push rax");
      break;
    case Parser::MULT:
      emit("  pop rbx");
      emit("  pop rax");
      emit("  imul rax,rbx");
      emit("  push rax");
      break;
    case Parser::DIV:
      emit("  mov rdx,0");
      emit("  pop rbx");
      emit("  pop rax");
      emit("  idiv rbx");
      emit("  push rax");
      break;
    case Parser::LABEL:
      emit(node->val + ":");
      break;
    case Parser::ISEQ:
      genRelational("je");
      break;
    case Parser::ISNE:
      genRelational("jne");
      break;
    case Parser::ISLT:
      genRelational("jl");
      break;
    case Parser::ISLE:
      genRelational("jle");
      break;
    case Parser::ISGT:
      genRelational("jg");
      break;
    case Parser::ISGE:
      genRelational("jge");
      break;
    case Parser::JUMP:
      emit("  jmp " + node->val);
      break;
    case Parser::JUMPF:
      emit("  pop rax");
      emit("  cmp rax, 0");
      emit("  je " + node->val);
      break;
    case Parser::JUMPT:
      break;
    case Parser::PUSHL:
      emit("  mov rax," + node->val);
      emit("  push rax");
      break;
    case Parser::PUSHV:
      emit("  push qword[" + node->val + "]");
      break;
    case Parser::STORE:
      emit("  pop qword[" + node->val + "]");
      break;
    case Parser::CALL:
      emit("  call " + node->val);
      emit("  push rax");
      break;
    case Parser::RET:
      emit("  pop rax");
      if (currentFunc != "main:")
	emit("  push r15");
      emit("  ret");
      break;
    case Parser::SEQ:
      break;
    case Parser::PRINTF:
      fmt = node->val;
      nparams = fmt.at(0) - '0';
      fmt = "`" + fmt.substr(1) + "`";
      fmts[nfmts++] = fmt;
      emit("  mov    rdi,fmt" + itos(nfmts));
      if (nparams == 5) {
	emit("  pop   r9");
	--nparams; }
      if (nparams == 4) {
	emit("  pop   r8");
	--nparams;
      }
      if (nparams == 3) {
	emit("  pop   rcx");
	--nparams; }
      if (nparams == 2) {
	emit("  pop   rdx");
	--nparams; }
      if (nparams == 1) {
	emit("  pop   rsi");
      }
      emit("  mov    rax,0");
      emit("  push   rbp");
      emit("  call   printf");
      emit("  pop    rbp");
      //      emit("  call   printf");
      // emit("  pop    rbp");
      break;
    case Parser::FUNC:
      currentFunc = node->val;
      emit(currentFunc);
      if (currentFunc != "main:")
	emit("  pop r15");
      break;
    case Parser::PARAM:
      break; 
    }
  
}
