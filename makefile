OPTS = -c -g -Wall -Werror

microc:token.o lexer.o parser.o symboltable.o microc.o hashTable.o hash.o link.o
	g++ -o microc microc.o lexer.o parser.o token.o symboltable.o hashTable.o hash.o link.o

microc.o: microc.cc parser.h lexer.h token.h hash.h hashTable.h link.h stack.h stack.cc
	g++ $(OPTS) microc.cc
lexer.o:lexer.cc lexer.h token.h
	g++ $(OPTS) lexer.cc
token.o:token.cc token.h
	g++ $(OPTS) token.cc
parser.o: parser.h parser.cc token.h lexer.h symboltable.h
	g++ $(OPTS) parser.cc
symboltable.o: symboltable.h symboltable.cc hashTable.h 
	g++ $(OPTS) symboltable.cc
hash.o: hash.h hash.cc
	g++ $(OPTS) hash.cc
hashTable.o: hashTable.cc hashTable.h link.h hash.h
	g++ $(OPTS) hashTable.cc
link.o: link.cc link.h
	g++ $(OPTS) link.cc
clean:
	rm -f *.o