CXX_DIR = ../lib/cxxtest
CXXTEST = $(CXX_DIR)/cxxtestgen.pl
CXXFLAGS = --error-printer --abort-on-fail --have-eh

FLAGS = -Wall -g

# Program files.
readInput.o:	readInput.cpp readInput.h
	g++ $(FLAGS) -c readInput.cpp 

regex.o:	regex.cpp regex.h
	g++ $(FLAGS) -c regex.cpp 

scanner.o:	scanner.cpp scanner.h regex.h readInput.h
	g++ $(FLAGS) -c scanner.cpp 

extToken.o: 	extToken.cpp extToken.h parser.h
	g++ $(FLAGS) -c extToken.cpp

parser.o: 	parser.cpp parser.h scanner.h extToken.h AST.h
	g++ $(FLAGS) -c parser.cpp

parseResult.o: parseResult.cpp parseResult.h AST.h
	g++ $(FLAGS) -c parseResult.cpp

strfmt.o: strfmt.cpp strfmt.h
	g++ $(FLAGS) -c strfmt.cpp

cffc.o: cffc.cpp parser.h readInput.h AST.h regex.h parseResult.h scanner.h extToken.h strfmt.h
	g++ $(FLAGS) -c cffc.cpp

cffc: cffc.o parser.o readInput.o AST.h regex.o parseResult.o scanner.o extToken.o strfmt.o
	g++ $(FLAGS) -o ../cffc/cffc cffc.o parser.o readInput.o regex.o parseResult.o scanner.o extToken.o strfmt.o

# Testing files and targets.
run-tests:	regex_tests scanner_tests parser_tests ast_tests codeGen_tests
	./regex_tests
	./scanner_tests
	./parser_tests
	./ast_tests
	./codeGen_tests

regex_tests:	regex_tests.cpp regex.o
	g++ $(FLAGS) -I$(CXX_DIR) -o regex_tests regex.o regex_tests.cpp

regex_tests.cpp:	regex.h regex_tests.h
	$(CXXTEST) $(CXXFLAGS) -o regex_tests.cpp regex_tests.h

scanner_tests:	scanner_tests.cpp scanner.o regex.o readInput.o
	g++ $(FLAGS) -I$(CXX_DIR)  -o scanner_tests \
		scanner.o regex.o readInput.o scanner_tests.cpp

scanner_tests.cpp:	scanner.o scanner_tests.h readInput.h
	$(CXXTEST) $(CXXFLAGS) -o scanner_tests.cpp scanner_tests.h

parser_tests: 	parser_tests.cpp parser.o extToken.o parseResult.o \
		scanner.o readInput.o regex.o strfmt.o
	g++ $(FLAGS) -I$(CXX_DIR) -o parser_tests parser_tests.cpp \
		parser.o extToken.o parseResult.o scanner.o readInput.o \
		regex.o strfmt.o

parser_tests.cpp: parser.o extToken.h parseResult.h scanner.h \
		readInput.h strfmt.h
	$(CXXTEST) $(CXXFLAGS) -o parser_tests.cpp parser_tests.h

ast_tests: ast_tests.cpp readInput.o scanner.o extToken.o parser.o \
		parseResult.o regex.o strfmt.o
	g++ $(Flags) -I$(CXX_DIR) -o ast_tests ast_tests.cpp \
		readInput.o scanner.o extToken.o parser.o parseResult.o regex.o strfmt.o

ast_tests.cpp: parser.o readInput.h scanner.h extToken.h parseResult.h \
		ast_tests.h AST.h strfmt.h
	$(CXXTEST) $(CXXFLAGS) -o ast_tests.cpp ast_tests.h

codeGen_tests: codeGen_tests.cpp readInput.o parser.o scanner.o extToken.o \
		parseResult.o AST.h regex.o strfmt.o
	g++ $(Flags) -I$(CXX_DIR) -o codeGen_tests codeGen_tests.cpp \
		readInput.o parser.o scanner.o extToken.o parseResult.o \
		regex.o strfmt.o

codeGen_tests.cpp: parser.h readInput.h scanner.h extToken.h parseResult.h \
		AST.h codeGen_tests.h regex.h strfmt.h
	$(CXXTEST) $(CXXFLAGS) -o codeGen_tests.cpp codeGen_tests.h


clean:
	rm -Rf *.o *~ \
		regex_tests regex_tests.cpp \
		scanner_tests scanner_tests.cpp \
		parser_tests parser_tests.cpp \
		ast_tests ast_tests.cpp \
		codeGen_tests codeGen_tests.cpp \
		../cffc/cffc ../cffc/Machine.h ../cffc/Machine.cpp
