/* A recursive descent parser with operator precedence.

   Author: Eric Van Wyk

   This algorithms is based on the work of Douglas Crockford in "Top
   Down Operator Precedence", a chapter in the book "Beautiful Code".
   Mr. Crockford describes in his chapter how his work comes from that
   of Based on algorithms described Vaughan Pratt in "Top Down Operator
   Precedence", presented at the ACM Symposium on Principles of
   Programming Languages.

   Douglas Crockford's chapter is available at 
    http://javascript.crockford.com/tdop/tdop.html

   Vaughan Pratt's paper is available at 
    http://portal.acm.org/citation.cfm?id=512931

   These are both quite interesting works and worth reading if you
   find the problem of parsing to be an interesting one.

   Last modified: March 5, 2013.
*/

#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "parseResult.h"

#include <string>

class ExtToken ;

class Parser {

public:
    Parser() ;

    ParseResult parse (const char *text) ;
    ParseResult parsePlatformHelper (const char *text) ;
    ParseResult parseExprHelper (const char *text) ;
    ParseResult parseDeclHelper (const char *text) ;
    ParseResult parseDeclsHelper (const char *text);
    ParseResult parseStmtHelper (const char *text) ;
    ParseResult parseStmtsHelper (const char *text) ;
    ParseResult parseTransitionHelper (const char *text) ;
    ParseResult parseTransitionsHelper (const char *text) ;
    ParseResult parseStateHelper (const char *text) ;
    ParseResult parseStatesHelper (const char *text) ;

    // Parser methods for the nonterminals:
    // Program, Platform, Decls, Decl, States, State,
    // Transitions, Transition, Stmts, Stmt, Expr

    ParseResult parseProgram () ;
    ParseResult parsePlatform () ;
    ParseResult parseDecls () ;
    ParseResult parseDecl () ;
    ParseResult parseType () ;
    ParseResult parseStates () ;
    ParseResult parseState () ;
    ParseResult parseTransitions () ;
    ParseResult parseTransition () ;
    ParseResult parseStmts () ;
    ParseResult parseStmt () ;
    ParseResult parseExpr (int rbp) ;

    // methods for parsing productions for Expr
    ParseResult parseTrueKwd () ;
    ParseResult parseFalseKwd () ;
    ParseResult parseIntConst () ;
    ParseResult parseFloatConst () ;
    ParseResult parseStringConst () ;
    ParseResult parseCharConst () ;
    ParseResult parseVariableName () ;

    ParseResult parseNestedExpr () ;

    ParseResult parseAddition ( ParseResult left ) ;
    ParseResult parseMultiplication ( ParseResult left ) ;
    ParseResult parseSubtraction ( ParseResult left ) ;
    ParseResult parseDivision ( ParseResult left ) ;

    ParseResult parseRelationalExpr ( ParseResult left ) ;

    // Helper function used by the parser.
    void match (tokenType tt) ;
    bool attemptMatch (tokenType tt) ;
    bool nextIs (tokenType tt) ;
    void nextToken () ;

    std::string terminalDescription ( tokenType terminal ) ;
    std::string makeErrorMsg ( tokenType terminal ) ;
    std::string makeErrorMsgExpected ( tokenType terminal ) ;
    std::string makeErrorMsg ( const char *msg ) ;

    ExtToken *tokens ;
    ExtToken *currToken ;
    ExtToken *prevToken ;

} ;

#endif /* PARSER_H */
