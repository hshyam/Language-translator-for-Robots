#include <cxxtest/TestSuite.h>
#include <cstring>

#include "readInput.h"
#include "scanner.h"
#include "extToken.h"
#include "parser.h"
#include "parseResult.h"
#include "AST.h"
#include "regex.h"

/* One of the above has likely included the .h file with your
   definition of the Program class.  It is not named here so that you
   can name your files as you see fit.
*/

using namespace std ;

class CodeGenTestSuite : public CxxTest::TestSuite 
{
public:
    Parser *p ;
    void test_setup_code ( ) {
        p = new Parser() ;
    }

    /* In the tests below, you can adjust the 'length_to_test...'
       variables to change the amount of the two files - the generated
       file and the expected one - that are compared.
    */

    void helper_test_codeGen ( string program ) {
        string file = "../samples/" + program + ".cff" ;
        const char *text =  readInputFromFile ( file.c_str() )  ;
        TSM_ASSERT ( "Could not find file for " + program, text ) ;

        // 1. Test that the file can be parsed.
        ParseResult pr = p->parse ( text ) ;
        TSM_ASSERT ( "file \"" + file + "\" failed to parse. " + 
                     "It had errors: " + pr.errors, pr.ok ) ;

        // 2. Verify that the parser AST is a Program.
        Program *p = dynamic_cast<Program *>(pr.ast) ;
        TSM_ASSERT ( "file \"" + file + 
                     "\" parser failed to return a Program AST", p ) ;

        // 3. Verify correct h code generated.
        string expected_h_file = "../cffc/Machine.h_" + program ;
        const char *expected_h = 
            readInputFromFile ( expected_h_file.c_str() ) ;

        string returned_cppCode_h = p->cppCode_h() ;
        const char *generated_h = returned_cppCode_h.c_str() ;

        int length_to_test_h = 5 ; // for initial testing
        // int length_to_test_h = strlen (expected_h) ; // for final testing
        TSM_ASSERT_EQUALS ( "Comparing h code generated for " + program,
                            0, strncmp ( expected_h, generated_h,
                                         length_to_test_h ) ) ;

        // 4. Verify correct cpp code generated.
        string expected_cpp_file = "../cffc/Machine.cpp_" + program ;
        const char *expected_cpp = 
            readInputFromFile ( expected_cpp_file.c_str() ) ;

        string returned_cppCode_cpp = p->cppCode_cpp() ;
        const char *generated_cpp = returned_cppCode_cpp.c_str() ;

        // int length_to_test_cpp = 150 ; // for initial testing
        int length_to_test_cpp = strlen (expected_cpp) ; // for final testing
        TSM_ASSERT_EQUALS ( "Comparing cpp code generated for " + program,
                            0, strncmp ( expected_cpp, generated_cpp,
                                         length_to_test_cpp ) ) ;
    }

  
    void test_codeGen_squareMapper ( ) {
        helper_test_codeGen ( "squareMapper" ) ;
    }
    void test_codeGen_abstar ( ) {
        helper_test_codeGen ( "abstar" ) ;
    }

    /* Do not attempt these until your generated code distinquishes
       variables that are declared in the state machine and variables
       that are sensors or actuators.

       When ready, remove the "a_" to activate the test.
     */
    void a_test_codeGen_sumOfSquares ( ) {
        helper_test_codeGen ( "sumOfSquares" ) ;
    }
    void a_test_codeGen_box ( ) {
        helper_test_codeGen ( "box" ) ;
    }
} ;
