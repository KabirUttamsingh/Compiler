/*
  CSE 109
  Kabir Uttamsingh
  kku219
  ) Program Description: Program #4
*/

#include <cstdio>
#include <string>
#include <iostream>
#include "lexer.h"
#include "token.h"
using namespace std;


Lexer:: Lexer (istream& input):store(input)
{

  line = 1;
  pos = 0;
 
  ch = nextChar();

  array[0] = "";
  array[1] = "";
  array[2] = "";
  array[3] = "+";
  array[4] = "-";
  array[5] = "*";
  array[6] = "/";
  array[7] = "=";
  array[8] = "==";
  array[9] = "!=";
  array[10] = "<";
  array[11] = "<=";
  array[12] = ">";
  array[13] =">=";
  array[14] = "&&";
  array[15] = "||";
  array[16] = "(";
  array[17] = ")";
  array[18] = "{";
  array[19] = "}";
  array[20] = ",";
  array[21] = ";";
  array[22] = "if";
  array[23] = "else";
  array[24] = "while";
  array[25] = "function";
  array[26] = "var";
  array[27] = "printf";
  array[28] = "return";
  array[29] = "";
  array[30] = "";
    
}

Lexer :: ~Lexer()
{

}

char Lexer:: nextChar()
{
  char temp = store.get();
  if( temp == EOF)
    {
      return '#';
    }
  pos++;
  if(temp == '\n')
    {
      pos = 1;
      line++;
      return ' ';
    }
  return temp;
}

Token Lexer :: nextToken()
{

  
  string lexer;
  while(ch == ' ' || ch == '\t')
    {
      ch = nextChar(); 
    }

  int line1 = line;
  int pos1 = pos;

  
  
  if((ch>= 'a' && ch<= 'z') ||( ch >= 'A' && ch <= 'Z'))
    {
      while((ch>= 'a' && ch<= 'z') ||(ch >= 'A' && ch <='Z') ||( ch >= '0' && ch <='9'))
	{
	  lexer+=ch;
	  ch = nextChar();
	}
      for(int i =0; i <31; i++)
	{
	  if(lexer.compare(array[i])==0)
	    {
	      return Token((i+1),lexer,line1,pos1);
	    }
	}
      return Token(Token::IDENT,lexer,line1,pos1);
    }


  
  
  if(ch>='0' && ch<='9')
    {
      while (ch>='0' &&ch<='9')
	{
	  lexer+=ch;
	  ch = nextChar();
	}
      return Token(Token::INTLIT, lexer, line1, pos1);
    }



  
  if(ch=='+' || ch == '-' || ch== '*' || ch=='/' || ch=='='|| ch=='!'|| ch=='<' || ch== '>'|| ch=='&'|| ch=='|'|| ch== '('|| ch==')'|| ch=='{'|| ch=='}'|| ch==','|| ch==';')
    {
      while(ch=='+' ||
	    ch == '-' ||
	    ch== '*' ||
	    ch=='/' ||
	    ch=='='||
	    ch=='!'||
	    ch=='<' ||
	    ch== '>'||
	    ch=='&'||
	    ch=='|'||
	    ch== '('||
	    ch==')'||
	    ch=='{'||
	    ch=='}'||
	    ch==','||
	    ch==';')
	{
	  lexer+=ch;
	  ch = nextChar();
	  if (lexer != "!" && lexer != ">" && lexer!= "<" && lexer!= "&" && lexer != "|" && lexer!= "=")
	    {
	      break;
	    }
	}
      for(int i =3; i <22; i++)
	{
	  if(lexer.compare(array[i])==0)
	    {
	      return Token((i+1),lexer,line1, pos1);
	    }
	}

    }



  
  if(ch=='"')
    {
      ch = nextChar();
      while(ch!='"')
	{
	  lexer += ch;
	  ch = nextChar();
	}
      ch = nextChar();
      return Token(Token::STRINGLIT,lexer,line1, pos1);
    }
  if(ch== '#')
    {
      lexer +=ch;
      return Token(Token::ENDOFFILE, lexer, line1, pos1);
    }
  
  ch = nextChar();
  cout<< "invalid token " << lexer << "line: " << line1 << " pos: " <<pos1 << " " <<endl;
  exit(1);
  
}


