#include <cxxtest/TestSuite.h>

#include "readInput.h"
#include "scanner.h"
#include "extToken.h"
#include "parser.h"
#include "parseResult.h"
#include "AST.h"
#include <stdio.h>
// One of the above has likely included the .h file with your
// definition of the Node and Program class.  It is not named 
// here so that you can name your files as you see fit.

using namespace std;
class AstTestSuite : public CxxTest::TestSuite 
{
public:
    int DEBUG ;

    Scanner *s ;
    Parser *p ;
    void test_setup_code ( ) {
      s = new Scanner() ;
      p = new Parser() ;
      DEBUG = 0 ;
    }

    /* In this file you will add 3 additional tests like the one for
       squareMapper below.

       You will also add a number of tests that demonstrate how you
       incrementally developed and tested your implementation, as
       described in the specifications for Iteration 3.  This will
       also include the appropriate documentation of that effort.
    */

    void xtest_ast_squareMapper ( ) {
        string file = "../samples/squareMapper.cff" ;
        const char *text =  readInputFromFile ( file.c_str() )  ;
        TS_ASSERT ( text ) ;

        // 1. Test that the file can be parsed.
        ParseResult pr = p->parse ( text ) ;
        TSM_ASSERT ( "file \"" + file + "\" failed to parse. " + 
                     "It had errors: " + pr.errors, pr.ok ) ;

        // 2. Verify that the ast field is not null
        TSM_ASSERT ( "\"" + file + "\" failed to generate an AST.",
                     pr.ast != NULL );

        // 3. Verify that the parser AST is an Expr.
        Program *p = dynamic_cast<Program *>(pr.ast) ;
        TSM_ASSERT ( "file \"" + file + 
                     "\" parser failed to return a Program AST", p ) ;

        // 4. Verify that the correct name is reported.
        TSM_ASSERT_EQUALS ( "file \"" + file + 
                            "\" returned wrong name" ,
                            p->getName(), "SquareMapper" ) ;

        // 5. Verify that the correct number of states.
        TSM_ASSERT_EQUALS ( "file \"" + file + 
                            "\" returned wrong number of states" ,
                            p->getNumStates(), 1 ) ;

        // 6. Verify that the correct number variable declarations.
	TSM_ASSERT_EQUALS ( "file \"" + file + 
                            "\" returned wrong number of variable declarations" ,
                            p->getNumVarDecls(), 0 ) ;

        // 7. Verify that the correct number variable uses.
	TSM_ASSERT_EQUALS ( "file \"" + file + 
                            "\" returned wrong number of variable uses" ,
                            p->getNumVarUses(), 3 ) ;
    }

    void test_ast_abStar ( ) {
      string file = "../samples/abstar.cff" ;
      const char *text =  readInputFromFile ( file.c_str() )  ;
      TS_ASSERT ( text ) ;
      
      // 1. Test that the file can be parsed.
      ParseResult pr = p->parse ( text ) ;
      TSM_ASSERT ( "file \"" + file + "\" failed to parse. " + 
		   "It had errors: " + pr.errors, pr.ok ) ;
      
      // 2. Verify that the ast field is not null
      TSM_ASSERT ( "\"" + file + "\" failed to generate an AST.",
		   pr.ast != NULL );
      
      // 3. Verify that the parser AST is an Expr.
      Program *p = dynamic_cast<Program *>(pr.ast) ;
      TSM_ASSERT ( "file \"" + file + 
		   "\" parser failed to return a Program AST", p ) ;
      
      // 4. Verify that the correct name is reported.
      TSM_ASSERT_EQUALS ( "file \"" + file + 
			  "\" returned wrong name" ,
			  p->getName(), "ABStar" ) ;
      
      // 5. Verify that the correct number of states.
      TSM_ASSERT_EQUALS ( "file \"" + file + 
			  "\" returned wrong number of states" ,
			  p->getNumStates(), 3 ) ;
      
      // 6. Verify that the correct number variable declarations.
      TSM_ASSERT_EQUALS ( "file \"" + file + 
			  "\" returned wrong number of variable declarations" ,
			  p->getNumVarDecls(), 0 ) ;
      
      // 7. Verify that the correct number variable uses.
      TSM_ASSERT_EQUALS ( "file \"" + file + 
			  "\" returned wrong number of variable uses" ,
			  p->getNumVarUses(), 16 ) ;
    }
    
    void test_ast_box ( ) {
      string file = "../samples/box.cff" ;
      const char *text =  readInputFromFile ( file.c_str() )  ;
      TS_ASSERT ( text ) ;

      // 1. Test that the file can be parsed.
      ParseResult pr = p->parse ( text ) ;
      TSM_ASSERT ( "file \"" + file + "\" failed to parse. " + 
		   "It had errors: " + pr.errors, pr.ok ) ;
      
      // 2. Verify that the ast field is not null
      TSM_ASSERT ( "\"" + file + "\" failed to generate an AST.",
		   pr.ast != NULL );
      
      // 3. Verify that the parser AST is an Expr.
      Program *p = dynamic_cast<Program *>(pr.ast) ;
      TSM_ASSERT ( "file \"" + file + 
		   "\" parser failed to return a Program AST", p ) ;
      
      // 4. Verify that the correct name is reported.
      TSM_ASSERT_EQUALS ( "file \"" + file + 
			  "\" returned wrong name" ,
			  p->getName(), "Box" ) ;
      
      // 5. Verify that the correct number of states.
      TSM_ASSERT_EQUALS ( "file \"" + file + 
			  "\" returned wrong number of states" ,
			  p->getNumStates(), 5) ;
      
      // 6. Verify that the correct number variable declarations.
      TSM_ASSERT_EQUALS ( "file \"" + file + 
			  "\" returned wrong number of variable declarations" ,
			  p->getNumVarDecls(), 1 ) ;
      
      // 7. Verify that the correct number variable uses.
      TSM_ASSERT_EQUALS ( "file \"" + file + 
			  "\" returned wrong number of variable uses" ,
			  p->getNumVarUses(), 18) ;
    }

    void test_ast_sumOfSquares ( ) {
      string file = "../samples/sumOfSquares.cff" ;
      const char *text =  readInputFromFile ( file.c_str() )  ;
      TS_ASSERT ( text ) ;
      
      // 1. Test that the file can be parsed.
      ParseResult pr = p->parse ( text ) ;
      TSM_ASSERT ( "file \"" + file + "\" failed to parse. " + 
		   "It had errors: " + pr.errors, pr.ok ) ;
      
      // 2. Verify that the ast field is not null
      TSM_ASSERT ( "\"" + file + "\" failed to generate an AST.",
		   pr.ast != NULL );
      
      // 3. Verify that the parser AST is an Expr.
      Program *p = dynamic_cast<Program *>(pr.ast) ;
      TSM_ASSERT ( "file \"" + file + 
		   "\" parser failed to return a Program AST", p ) ;
      
      // 4. Verify that the correct name is reported.
      TSM_ASSERT_EQUALS ( "file \"" + file + 
			  "\" returned wrong name" ,
			  p->getName(), "SumOfSquares" ) ;
      
      // 5. Verify that the correct number of states.
      TSM_ASSERT_EQUALS ( "file \"" + file + 
			  "\" returned wrong number of states" ,
			  p->getNumStates(), 2 ) ;
      
      // 6. Verify that the correct number variable declarations.
      TSM_ASSERT_EQUALS ( "file \"" + file + 
			  "\" returned wrong number of variable declarations" ,
			  p->getNumVarDecls(), 2 ) ;
      
      // 7. Verify that the correct number variable uses.
      TSM_ASSERT_EQUALS ( "file \"" + file + 
			  "\" returned wrong number of variable uses" ,
			  p->getNumVarUses(), 12 ) ;
    }
    
    // Test for parsePlatform
    void test_parsePlatform() {
      const char *text = "platform: PositionalRobot ;";
      ParseResult pr = p->parsePlatformHelper(text);
      TS_ASSERT(pr.ast != NULL);
      Platform *p = dynamic_cast<Platform *>(pr.ast);
      TSM_ASSERT ("Input failed to return a Platform pointer", p);
      TS_ASSERT_EQUALS("PositionalRobot", p->getPlatformName());
    }

    // Tests for parseExpr
    void test_parseExpr() {

      // Test for integer
      const char *text = "12";
      ParseResult pr = p->parseExprHelper(text);
      TS_ASSERT(pr.ast != NULL);
      Num *n = dynamic_cast<Num *>(pr.ast);
      TSM_ASSERT ("Input failed to return a Num pointer", n);

      // Test for float
      const char *text0 = "1.2300";
      ParseResult pr0 = p->parseExprHelper(text0);
      TS_ASSERT(pr0.ast != NULL);
      Num *n0 = dynamic_cast<Num *>(pr0.ast);
      TSM_ASSERT ("Input failed to return a Num pointer", n0);

      // Test for addition
      const char *text1 = "1 + 1";
      ParseResult pr1 = p->parseExprHelper(text1);
      TS_ASSERT(pr1.ast != NULL);
      Add *a = dynamic_cast<Add *>(pr1.ast);
      TSM_ASSERT("Input failed to return an Add pointer", a);

      // Test for multiplication
      const char *text2 = "2 * 1";
      ParseResult pr2 = p->parseExprHelper(text2);
      TS_ASSERT(pr2.ast != NULL);
      Mul *m = dynamic_cast<Mul *>(pr2.ast);
      TSM_ASSERT("Input failed to return a Mul pointer", m);

      // Test for subtraction
      const char *text3 = "3 - 2";
      ParseResult pr3 = p->parseExprHelper(text3);
      TS_ASSERT(pr3.ast != NULL);
      Sub *s = dynamic_cast<Sub *>(pr3.ast);
      TSM_ASSERT("Input failed to return a Sub pointer", s);

      // Test for division
      const char *text4 = "4 / 2";
      ParseResult pr4 = p->parseExprHelper(text4);
      TS_ASSERT(pr4.ast != NULL);
      Div *d = dynamic_cast<Div *>(pr4.ast);
      TSM_ASSERT("Input failed to return a Div pointer", d);

      // Tests for variable names
      const char *text5 = "x";
      const char *text6 = "var1";
      ParseResult pr5 = p->parseExprHelper(text5);
      ParseResult pr6 = p->parseExprHelper(text6);
      TS_ASSERT(pr5.ast != NULL);
      TS_ASSERT(pr6.ast != NULL);
      VariableUse *v = dynamic_cast<VariableUse *>(pr5.ast);
      TSM_ASSERT ("Input failed to return a VariableUse pointer", v);
      VariableUse *v1 = dynamic_cast<VariableUse *>(pr6.ast);
      TSM_ASSERT ("Input failed to return a VariableUse pointer", v1);
      TS_ASSERT_EQUALS(1, v->getNumVarUses());

      const char *text7 = "i + x";
      ParseResult pr7 = p->parseExprHelper(text7);
      TS_ASSERT(pr7.ast != NULL);
      Expr *e0 = dynamic_cast<Expr *>(pr7.ast);
      TSM_ASSERT("Input failed to return an Expr pointer between two variables", e0);
      TS_ASSERT_EQUALS(2, e0->getNumVarUses());
    }

    // Tests for Decl
    /* void xtest_parseDecl() {
      const char *text = "int i;";
      ParseResult pr = p->parseDeclHelper(text);
      TS_ASSERT(pr.ast != NULL);
      Decl *d = dynamic_cast<Decl *>(pr.ast);
      TSM_ASSERT("Input failed to return Decl pointer", d);
      TS_ASSERT_EQUALS("i", d->getName());
      } 

    For writing assignment 3, we stopped using parseDecl. */

    void test_parseDecls() {
      const char *text = "int i; int x; initial";
      ParseResult pr = p->parseDeclsHelper(text);
      TS_ASSERT(pr.ast != NULL);
      Decl *ds = dynamic_cast<Decl *>(pr.ast);
      TSM_ASSERT("Input failed to return Decls pointer", ds);
      TS_ASSERT_EQUALS(2, ds->getNumVarDecls());
    }

    // Tests for Stmt
    void test_parseStmt() {
      const char *text = "input := 1 + 1 ;" ;
      ParseResult pr = p->parseStmtHelper(text);
      TS_ASSERT(pr.ast != NULL);
      Stmt *s = dynamic_cast<Stmt *>(pr.ast);
      TSM_ASSERT("Input failed to return Stmt pointer", s);
    }

    // Tests for Stmts
    void test_parseStmts() {
      const char *text = "input := 1 + 1 ; output := 2 - 1 ; }";
      ParseResult pr = p->parseStmtsHelper(text);
      TS_ASSERT(pr.ast != NULL);
      Stmts *s = dynamic_cast<Stmts *>(pr.ast);
      TSM_ASSERT("Input failed to return Stmts pointer", s);
    }

    void test_parseTransition() {
      const char *text = "goto X when 1 performing { input := 1 + 1 ; output := 2 - 1 ; };";
      ParseResult pr = p->parseTransitionHelper(text);
      TS_ASSERT(pr.ast != NULL);
      Transition *t = dynamic_cast<Transition *>(pr.ast);
      TSM_ASSERT("Input failed to return Transition pointer", t);

      const char *text2 = "exit when 1 performing { input := 1 + 1 ; output := 2 - 1 ; };";
      ParseResult pr2 = p->parseTransitionHelper(text2);
      TS_ASSERT(pr2.ast != NULL);
      Transition *t2 = dynamic_cast<Transition *>(pr2.ast);
      TSM_ASSERT("Input failed to return Transition pointer", t2);
    }

    void test_parseTransitions() {
      const char *text = "goto X when 1 performing { input := 1 + 1 ; output := 2 - 1 ; }; exit when 1 performing { input := 1 + 1 ; output := 2 - 1 ; }; }";
      ParseResult pr = p->parseTransitionsHelper(text);
      TS_ASSERT(pr.ast != NULL);
      Transitions *t = dynamic_cast<Transitions *>(pr.ast);
      TSM_ASSERT("Input failed to return Transitions pointer", t);
    }

    void test_parseState() {
      const char *text = "state: X { goto X when 1 performing { input := 1 + 1 ; output := 2 - 1 ; }; exit when 1 performing { input := 1 + 1 ; output := 2 - 1 ; }; }";
      ParseResult pr = p->parseStateHelper(text);
      TS_ASSERT(pr.ast != NULL);
      State *s = dynamic_cast<State *>(pr.ast);
      TSM_ASSERT("Input failed to return State pointer", s);
      TS_ASSERT_EQUALS("X", s->getStateName());
      TS_ASSERT_EQUALS(s->isInitialState(), false);
    }

    void test_parseStates() {
      const char *text = "initial state: X { goto X when 1 performing { input := 1 + 1 ; output := 2 - 1 ; } ; } state: X { goto X when 1 performing { input := 1 + 1 ; output := 2 - 1 ; } ; }";
      ParseResult pr = p->parseStatesHelper(text);
      TS_ASSERT(pr.ast != NULL);
      States *s = dynamic_cast<States *>(pr.ast);
      TSM_ASSERT("Input failed to return States pointer", s);
      TS_ASSERT_EQUALS(2, s->getNumStates());
    }
    
    
} ;

/*********************** WRITING ASSIGNMENT 2 ****************************

     We started by writing test cases for all the programs and put x's in front
of the tests so that they would not execute until the program was written. Then
we started writing the unit tests for the non-terminals. We started with
Platform because it has no dependencies on other non-terminals, even more so
than Expr which extends to Num and VariableUse, etc. so it was a very simple
class to start with to make sure we had the right idea. We wrote a helper
function, at the top of parser.cpp (and additional helper functions for each
other class we tested) and it is labelled as such. After we got Platform down,
we moved on to Expr as recommended. We further broke down Expr into several
smaller tests for its own sub-classes, like variable names and functions like
add, subtract, multiply, and divide.

     After that we continued with Decl, and once the test was returning a
correct Decl object, followed with Decls. We chose Decl/Decls because similarly
to Platform, they don't depend on any other non-terminals except for the Decl
objects in Decls' own list so they were a simple class to start with when
getting the idea for structuring the Node lists. Once we had the structure
down, we implemented and tested Stmt followed by Stmts, and then Transition
followed by Transitions, and finally State followed by States, all of which
have their own helper functions in parser.cpp which pass in a string that
should tokenize into that specific class.

*************************************************************************/
