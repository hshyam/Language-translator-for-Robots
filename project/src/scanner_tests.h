#include <cxxtest/TestSuite.h>

#include <stdio.h>
#include "readInput.h"
#include "scanner.h"

using namespace std ;

class ScannerTestSuite : public CxxTest::TestSuite 
{
public:
    /* A Scanner object is created in the test_setup_code method.
       This is a test, beginning with "test_", so that it is executed
       by the testing framework.  The scanner is used in some tests of
       the method "scan".
     */
    Scanner *s ;
    void test_setup_code ( ) {
        s = new Scanner() ;
    }


    // Tests for components and functions used by "scan"
    // --------------------------------------------------

    /* You may need to write several tests to adequately test the
       functions that are called from "scan".  Once you are confident
       that the components used by "scan" work properly, then you can
       run tests on the "scan" method itself.
    */

    // Here you should place tests for these other functions.


    /* Below is one of the tests for these components in the project
       solution created by your instructor..  It uses a helper
       function function called "tokenMaker_tester", which you have
       not been given.  You are expected to design your own components
       for "scan" and your own mechanisms for easily testing them.

       void xtest_TokenMaker_leftCurly ( ) {
           TS_ASSERT (tokenMaker_tester ("{ ", "^\\{", leftCurly, "{" ) );
       }

        Note that this test is here named "xtest_Token..." The leading
        "x" is so that cxxTest doesn't scan the line above and think
        it is an actual test that isn't commented out.  cxxTest is
        very simple and doesn't even process block comments.
    */


    /* You must have at least one separate test case for each terminal
       symbol.  Thus, you need a test that will pass or fail based
       solely on the regular expression (and its corresponding code)
       for each terminal symbol.

       This requires a test case for each element of the enumerated
       type tokenType.  This may look something like the sample test
       shown in the comment above.
    */


    // Tests for "scan"
    // --------------------------------------------------
    
    void test_terminal_nameKwd() {
      Token *tks = s->scan ("name");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, nameKwd);
      TS_ASSERT_EQUALS(tks->lexeme, "name");
    }

   void test_terminal_platformKwd() {
      Token *tks = s->scan ("platform");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, platformKwd);
      TS_ASSERT_EQUALS(tks->lexeme, "platform");
    }

   void test_terminal_initialKwd() {
      Token *tks = s->scan ("initial");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, initialKwd);
      TS_ASSERT_EQUALS(tks->lexeme, "initial");
    }

   void test_terminal_stateKwd() {
      Token *tks = s->scan("state");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, stateKwd);
      TS_ASSERT_EQUALS(tks->lexeme, "state");
    }

   void test_terminal_gotoKwd() {
      Token *tks = s->scan("goto");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, gotoKwd);
      TS_ASSERT_EQUALS(tks->lexeme, "goto");
    }

   void test_terminal_whenKwd() {
      Token *tks = s->scan("when");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, whenKwd);
      TS_ASSERT_EQUALS(tks->lexeme, "when");
    }

   void test_terminal_performingKwd() {
      Token *tks = s->scan("performing");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, performingKwd);
      TS_ASSERT_EQUALS(tks->lexeme, "performing");
    }

   void test_terminal_exitKwd() {
      Token *tks = s->scan("exit");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, exitKwd);
      TS_ASSERT_EQUALS(tks->lexeme, "exit");
    }

   void test_terminal_intKwd() {
      Token *tks = s->scan("int");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, intKwd);
      TS_ASSERT_EQUALS(tks->lexeme, "int");
    }

   void test_terminal_floatKwd() {
      Token *tks = s->scan("float");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, floatKwd);
      TS_ASSERT_EQUALS(tks->lexeme, "float");
    }

   void test_terminal_booleanKwd() {
      Token *tks = s->scan("boolean");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, booleanKwd);
      TS_ASSERT_EQUALS(tks->lexeme, "boolean");
    }

   void test_terminal_stringKwd() {
      Token *tks = s->scan("string");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, stringKwd);
      TS_ASSERT_EQUALS(tks->lexeme, "string");
    }

   void test_terminal_charKwd() {
      Token *tks = s->scan("char");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, charKwd);
      TS_ASSERT_EQUALS(tks->lexeme, "char");
    }

   void test_terminal_trueKwd() {
     Token *tks = s->scan("true");
     TS_ASSERT(tks != NULL);
     TS_ASSERT_EQUALS(tks->terminal, trueKwd);
     TS_ASSERT_EQUALS(tks->lexeme, "true");
   }  
  
   void test_terminal_falseKwd() {
     Token *tks = s->scan("false");
     TS_ASSERT(tks != NULL);
     TS_ASSERT_EQUALS(tks->terminal, falseKwd);
     TS_ASSERT_EQUALS(tks->lexeme, "false");
   }

   void test_terminal_intConst() {
      Token *tks = s->scan("1234");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, intConst);
      TS_ASSERT_EQUALS(tks->lexeme, "1234");
   }

   void test_terminal_floatConst() {
      Token *tks = s->scan("123.45");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, floatConst);
      TS_ASSERT_EQUALS(tks->lexeme, "123.45");
    }

   void test_terminal_stringConst() {
      Token *tks = s->scan("\"Apple\"");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, stringConst);
      TS_ASSERT_EQUALS(tks->lexeme, "\"Apple\"");
   }

   void test_terminal_charConst() {
      Token *tks = s->scan("'a'");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, charConst);
      TS_ASSERT_EQUALS(tks->lexeme, "'a'");
    }

   void test_terminal_variableName() {
      Token *tks = s->scan("apple");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, variableName);
      TS_ASSERT_EQUALS(tks->lexeme, "apple");
      Token *tks2 = s->scan("int123");
      TS_ASSERT_EQUALS(tks2->terminal, variableName);
      TS_ASSERT_EQUALS(tks2->lexeme, "int123");
    }

   void test_terminal_leftParen() {
      Token *tks = s->scan("(");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, leftParen);
      TS_ASSERT_EQUALS(tks->lexeme, "(");
    }

   void test_terminal_rightParen() {
      Token *tks = s->scan(")");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, rightParen);
      TS_ASSERT_EQUALS(tks->lexeme, ")");
    }

   void test_terminal_leftCurly() {
      Token *tks = s->scan("{");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, leftCurly);
      TS_ASSERT_EQUALS(tks->lexeme, "{");
    }

   void test_terminal_rightCurly() {
      Token *tks = s->scan("}");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, rightCurly);
      TS_ASSERT_EQUALS(tks->lexeme, "}");
    }

   void test_terminal_leftAngle() {
      Token *tks = s->scan("<");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, leftAngle);
      TS_ASSERT_EQUALS(tks->lexeme, "<");
    }

   void test_terminal_rightAngle() {
      Token *tks = s->scan(">");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, rightAngle);
      TS_ASSERT_EQUALS(tks->lexeme, ">");
    }

   void test_terminal_colon() {
      Token *tks = s->scan(":");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, colon);
      TS_ASSERT_EQUALS(tks->lexeme, ":");
    }

   void test_terminal_comma() {
      Token *tks = s->scan(",");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, comma);
      TS_ASSERT_EQUALS(tks->lexeme, ",");
    }

   void test_terminal_semiColon() {
      Token *tks = s->scan(";");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, semiColon);
      TS_ASSERT_EQUALS(tks->lexeme, ";");
    }

   void test_terminal_assign() {
      Token *tks = s->scan(":=");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, assign);
      TS_ASSERT_EQUALS(tks->lexeme, ":=");
    }

   void test_terminal_plusSign() {
      Token *tks = s->scan("+");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, plusSign);
      TS_ASSERT_EQUALS(tks->lexeme, "+");
   }

   void test_terminal_star() {
      Token *tks = s->scan("*");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, star);
      TS_ASSERT_EQUALS(tks->lexeme, "*");
    }

   void test_terminal_dash() {
      Token *tks = s->scan("-");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, dash);
      TS_ASSERT_EQUALS(tks->lexeme, "-");
    }

   void test_terminal_forwardSlash() {
      Token *tks = s->scan("/");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, forwardSlash);
      TS_ASSERT_EQUALS(tks->lexeme, "/");
    }

   void test_terminal_equalsEquals() {
      Token *tks = s->scan("==");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, equalsEquals);
      TS_ASSERT_EQUALS(tks->lexeme, "==");
    }

   void test_terminal_lessThanEquals() {
      Token *tks = s->scan("<=");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, lessThanEquals);
      TS_ASSERT_EQUALS(tks->lexeme, "<=");
    }

   void test_terminal_greaterThanEquals() {
      Token *tks = s->scan(">=");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, greaterThanEquals);
      TS_ASSERT_EQUALS(tks->lexeme, ">=");
    }

   void test_terminal_notEquals() {
      Token *tks = s->scan("!=");
      TS_ASSERT(tks != NULL);
      TS_ASSERT_EQUALS(tks->terminal, notEquals);
      TS_ASSERT_EQUALS(tks->lexeme, "!=");
    }

   void test_terminal_endOfFile() {
     Token *tks = s->scan("");
     TS_ASSERT(tks != NULL);
     TS_ASSERT_EQUALS(tks->terminal, endOfFile);
     TS_ASSERT(tks->next == NULL);
   }

   void test_terminal_lexicalError() {
     Token *tks = s->scan("$*");
     TS_ASSERT(tks != NULL);
     TS_ASSERT_EQUALS(tks->terminal, lexicalError);
     tks = tks->next;
     TS_ASSERT(tks != NULL);
     TS_ASSERT_EQUALS(tks->terminal, star);
   }




    /* Below are some helper functions and sample tests for testing the 
       "scan" method on Scanner.
    */

    // Test that a list of tokens has no lexicalError tokens.
    bool noLexicalErrors (Token *tks) {
        Token *currentToken = tks ;
        while (currentToken != NULL) {
            if (currentToken->terminal == lexicalError) {
                return false ;
            }
            else {
                currentToken = currentToken->next ;
            }
        }
        return true ;
    }

    /* A quick, but inaccurate, test for scanning files.  It only
       checks that no lexical errors occurred, not that the right
       tokens were returned. 
    */
    void scanFileNoLexicalErrors ( const char* filename ) {
        char *text =  readInputFromFile ( filename )  ;
        TS_ASSERT ( text ) ;
        Token *tks = s->scan ( text ) ;
        TS_ASSERT (tks != NULL) ;
        TS_ASSERT (noLexicalErrors(tks));
    }


    /* This function checks that the terminal fields in the list of
       tokens matches a list of terminals.
    */
    bool sameTerminals (Token *tks, int numTerms, tokenType *ts) {
        Token *currentToken = tks ;
        int termIndex = 0 ;
        while (currentToken != NULL && termIndex < numTerms ) {
            if (currentToken->terminal != ts[termIndex]) {
                return false ;
            }
            else {
                ++ termIndex ;
                currentToken = currentToken->next ;
            }
        }
        return true ;
    }


    /* Below are the provided test files that your code should also
       pass.

       You may initially want to rename these tests to "xtest_..." so
       that the CxxTest framework does not see it as a test and won't
       run it as one.  This way you can focus on the tests that you'll
       write above for the individual terminal types first. Then focus
       on these tests.

    */

    // The "endOfFile" token is always the last one in the list of tokens.
    void test_scan_empty ( ) {
      Token *tks = s->scan ("  ") ;
      TS_ASSERT (tks != NULL) ;
      TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
      TS_ASSERT (tks->next == NULL) ;
    }

    void test_scan_empty_comment ( ) {
      Token *tks = s->scan (" /* a comment */ ") ;
      TS_ASSERT (tks != NULL) ;
      TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
      TS_ASSERT (tks->next == NULL) ;
    }

    // When a lexical error occurs, the scanner creates a token with a 
    // single-character lexeme and lexicalError as the terminal.
    void test_scan_lexicalErrors ( ) {
      Token *tks = s->scan ("$&1  ") ;
      TS_ASSERT (tks != NULL) ;
      TS_ASSERT_EQUALS (tks->terminal, lexicalError) ;
      TS_ASSERT_EQUALS (tks->lexeme, "$");
      tks = tks->next ;
      TS_ASSERT (tks != NULL) ;
      TS_ASSERT_EQUALS (tks->terminal, lexicalError) ;
      TS_ASSERT_EQUALS (tks->lexeme, "&");
      tks = tks->next ;
      TS_ASSERT (tks != NULL) ;
      TS_ASSERT_EQUALS (tks->terminal, intConst) ;
      TS_ASSERT_EQUALS (tks->lexeme, "1");
      tks = tks->next ;
      TS_ASSERT (tks != NULL) ;
      TS_ASSERT_EQUALS (tks->terminal, endOfFile) ;
      TS_ASSERT (tks->next == NULL) ;
    }


    // A test for scanning numbers and a variable.
    void test_scan_nums_vars ( ) {
      Token *tks = s->scan (" 123 x 12.34 ") ;
      TS_ASSERT (tks != NULL) ;
      tokenType ts[] = { intConst, variableName, floatConst, endOfFile } ;
      TS_ASSERT ( sameTerminals ( tks, 4, ts ) ) ;
    }



    /* This test checks that the scanner returns a list of tokens with
       the correct terminal fields.  It doesn't check that the lexeme
       are correct.
     */

    void xtest_scan_bad_syntax_good_tokens ( ) {
      const char *filename = "../samples/bad_syntax_good_tokens.cff" ;
      char *text =  readInputFromFile ( filename )  ;
      TS_ASSERT ( text ) ;
      Token *tks = s->scan ( text ) ;
      TS_ASSERT (tks != NULL) ;
      tokenType ts[] = { 
	intConst, intConst, intConst, intConst, 
	
	stringConst, stringConst, stringConst,
	
	floatConst, floatConst, floatConst,
	
	charConst, charConst, charConst, charConst, 
	charConst, charConst, charConst, 
	
	trueKwd, falseKwd,
	
	
	colon, semiColon, comma, 
	leftCurly, leftParen, rightCurly, rightParen,
	
	plusSign, star, dash, forwardSlash, 
	rightAngle, leftAngle,
	
	equalsEquals, lessThanEquals, 
	greaterThanEquals, notEquals, 
	assign,
	
	variableName, variableName, variableName, variableName, 
	variableName, variableName, variableName,
	
	nameKwd, platformKwd, initialKwd, stateKwd, 
	gotoKwd, whenKwd, exitKwd, performingKwd,
	
	intKwd, floatKwd, booleanKwd, stringKwd, charKwd,
	
	endOfFile
      } ;
      int count = 58; 
      TS_ASSERT ( sameTerminals ( tks, count, ts ) ) ;
    }
    
    void test_scan_sample_abstar ( ) {
      scanFileNoLexicalErrors ("../samples/abstar.cff") ;
    }
    
    
} ;
