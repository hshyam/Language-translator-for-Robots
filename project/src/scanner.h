#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include "regex.h"
#include <string.h>

using namespace std;

class Token ;

/* This enumerated type is used to keep track of what kind of
   construct was matched. 
*/
enum tokenEnumType { 

    // Keywords
    nameKwd, platformKwd, initialKwd, stateKwd, 
    gotoKwd, whenKwd, performingKwd, exitKwd,

    intKwd, floatKwd, booleanKwd, stringKwd, charKwd,

    trueKwd, falseKwd,

    // Constants
    intConst, floatConst, stringConst, charConst,

    // Names
    variableName ,

    // Punctuation
    leftParen, rightParen, 
    leftCurly, rightCurly, 

    leftAngle, rightAngle,
    colon, comma, semiColon, 
    assign, 

    plusSign, star, dash, forwardSlash,
    equalsEquals, lessThanEquals, greaterThanEquals, notEquals, 

    // Special terminal types
    endOfFile ,
    lexicalError
} ;
typedef enum tokenEnumType tokenType ;

// Below you need to write your class definitions for Token and Scanner.

class Token {
 public:
  string lexeme;
  tokenType terminal;
  Token *next;

  Token(string lexeme, tokenType terminal, Token *next)
    :lexeme(lexeme),
    terminal(terminal),
    next(next)
    {}
} ;

class Scanner {
 public:
  Token *scan (const char *);
  regex_t *regs[40];
  Scanner() {
    regs[nameKwd] = makeRegex("^name");
    regs[platformKwd] = makeRegex ("^platform");
    regs[initialKwd] = makeRegex ("^initial");
    regs[stateKwd] = makeRegex ("^state");
    regs[gotoKwd] = makeRegex ("^goto");
    regs[whenKwd] = makeRegex ("^when");
    regs[performingKwd] = makeRegex ("^performing");
    regs[exitKwd] = makeRegex ("^exit");
    regs[intKwd] = makeRegex ("^int");
    regs[floatKwd] = makeRegex ("^float");
    regs[booleanKwd] = makeRegex ("^boolean");
    regs[stringKwd] = makeRegex ("^string");
    regs[charKwd] = makeRegex ("^char");
    regs[trueKwd] = makeRegex ("^true");
    regs[falseKwd] = makeRegex ("^false");
    regs[intConst] = makeRegex ("^[0-9]+") ;
    regs[floatConst] = makeRegex ("^[0-9]+\\.[0-9]+") ;
    regs[stringConst] = makeRegex ("^\"[^\"]*\"");
    //regs[stringConst] = makeRegex ("^\".*\"");
    //regs[charConst] = makeRegex ("^(\'[A-Za-z]\')|(\'\\0\')");
    regs[charConst] = makeRegex ("^'([^\\n']|[\\]'|[\\]n|[\\]t|[\\]0)'");
    regs[variableName] = makeRegex ("^[A-Za-z]+[A-Za-z0-9_]*");
    regs[leftParen] = makeRegex ("^\\(");
    regs[rightParen] = makeRegex ("^\\)");
    regs[leftCurly] = makeRegex ("^\\{");
    regs[rightCurly] = makeRegex ("^\\}");
    regs[leftAngle] = makeRegex ("^<");
    regs[rightAngle] = makeRegex ("^>");
    regs[colon] = makeRegex ("^\\:");
    regs[comma] = makeRegex ("^\\,");
    regs[semiColon] = makeRegex ("^\\;");
    regs[assign] = makeRegex ("^\\:=");
    regs[plusSign] = makeRegex ("^\\+");
    regs[star] = makeRegex ("^\\*");
    regs[dash] = makeRegex ("^\\-");
    regs[forwardSlash] = makeRegex ("^\\/");
    regs[equalsEquals] = makeRegex ("^\\==");
    regs[lessThanEquals] = makeRegex ("^<=");
    regs[greaterThanEquals] = makeRegex ("^>=");
    regs[notEquals] = makeRegex ("^\\!=");
    regs[endOfFile] = NULL;
  }
}; 
  
#endif /* SCANNER_H */
