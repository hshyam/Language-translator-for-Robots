/*******************************************
 **************

    Scanner.cpp                       
    3081 Iteration 1                  
    Authors: Chris Hesemann           
             Harshita Radhe Shyam     
                                      
	                   *****************
********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "scanner.h"
#include "regex.h"
#include "readInput.h"

using namespace std;

// Create the compiled regular expressions that aren't tokentypes.	    
regex_t *whiteSpace = makeRegex ("^[\n\t\r ]+") ;

regex_t *blockComment = makeRegex ("^/\\*([^\\*]|\\*+[^\\*/])*\\*+/");

regex_t *lineComment = makeRegex ("^//[^\n]*\n");

Token *Scanner::scan (char const *text) {
  
  int consumeWhiteSpaceAndComments(regex_t*, regex_t*, regex_t*, const char *);
  Token *first, *last, *t, *prev;
  t = NULL;
  first = NULL;
  int numMatchedChars = 0 ;

    // Consume leading white space and comments
  numMatchedChars = consumeWhiteSpaceAndComments (whiteSpace, blockComment, lineComment, text) ;
    /* text is a character pointer that points to the current
       beginning of the array of characters in the input.  Adding an
       integer value to it advances the pointer that many elements in
       the array.  Thus, text is increased so that it points to the
       current location in the input. 
     */
    text = text + numMatchedChars ;

    enum MatchType {

      // Keywords
      nameKwdMatch, platformKwdMatch, initialKwdMatch, stateKwdMatch,
      gotoKwdMatch, whenKwdMatch, performingKwdMatch, exitKwdMatch,

      intKwdMatch, floatKwdMatch, booleanKwdMatch, stringKwdMatch, charKwdMatch,

      trueKwdMatch, falseKwdMatch,

      // Constants
      intConstMatch, floatConstMatch, stringConstMatch, charConstMatch,

      // Names
      variableNameMatch,

      // Punctuation
      leftParenMatch, rightParenMatch, leftCurlyMatch, rightCurlyMatch,
      leftAngleMatch, rightAngleMatch, colonMatch, commaMatch, semiColonMatch,
      assignMatch,

      plusSignMatch, starMatch, dashMatch, forwardSlashMatch,
      equalsEqualsMatch, lessThanEqualsMatch,
      greaterThanEqualsMatch, notEqualsMatch,

      // Special terminal types
      lexicalErrorMatch
    } matchType;
    
    int maxNumMatchedChars;

    while ( text[0] != NULL ) {
      maxNumMatchedChars = 0 ; matchType = lexicalErrorMatch;
      tokenType terminal;
      t = new Token("", terminal, NULL);
      
        /* maxNumMatchedChars is used to ensure that the regular
           expression that matched the longest string is the one that
           we use.  

           The regexs for word and integerConst cannot match the
           same text, but if we extend this program to search for
           specific keywords, then the keyword regex and the
           word-regex may, in some cases, match the same input text.

           If two regexs match the same number of characters
           then the tie has to be broken.  To break the tie, priority
           is given to the first one that was tried.  Thus the
           comparison
              (numMatchedChars > maxNumMatchedChars) 
           is strictly greater than.  Not greater than or  equal to.
        */

      int j = 0;
      while(regs[j] != NULL) {
        numMatchedChars = matchRegex (regs[j], text) ;
        if (numMatchedChars > maxNumMatchedChars) {
	  for (int i = maxNumMatchedChars; i<numMatchedChars; i++)
	    t->lexeme = t->lexeme + text[i];
	  maxNumMatchedChars = numMatchedChars ;
	  matchType = (MatchType) j ;
	}
	j++;
      }
      
      switch (matchType) {
      case nameKwdMatch: t->terminal = nameKwd; break;
      case platformKwdMatch: t->terminal = platformKwd; break;
      case initialKwdMatch: t->terminal = initialKwd; break;
      case stateKwdMatch: t->terminal = stateKwd; break;
      case gotoKwdMatch: t->terminal = gotoKwd; break;
      case whenKwdMatch: t->terminal = whenKwd; break;
      case performingKwdMatch: t->terminal = performingKwd; break;
      case exitKwdMatch: t->terminal = exitKwd; break;
      case intKwdMatch: t->terminal = intKwd; break;
      case floatKwdMatch :t->terminal = floatKwd; break;
      case booleanKwdMatch: t->terminal = booleanKwd; break;
      case stringKwdMatch: t->terminal = stringKwd; break;
      case charKwdMatch: t->terminal = charKwd; break;
      case trueKwdMatch: t->terminal = trueKwd; break;
      case falseKwdMatch: t->terminal = falseKwd; break;
      case intConstMatch: t->terminal = intConst; break;
      case floatConstMatch: t->terminal = floatConst; break;
      case stringConstMatch: t->terminal = stringConst; break;
      case charConstMatch: t->terminal = charConst; break;
      case variableNameMatch: t->terminal = variableName; break;
      case leftParenMatch: t->terminal = leftParen; break;
      case rightParenMatch: t->terminal = rightParen; break;
      case leftCurlyMatch: t->terminal = leftCurly; break;
      case rightCurlyMatch: t->terminal = rightCurly; break;
      case leftAngleMatch: t->terminal = leftAngle; break;
      case rightAngleMatch: t->terminal = rightAngle; break;
      case colonMatch: t->terminal = colon; break;
      case commaMatch: t->terminal = comma; break;
      case semiColonMatch: t->terminal = semiColon; break;
      case assignMatch: t->terminal = assign; break;
      case plusSignMatch: t->terminal = plusSign; break;
      case starMatch: t->terminal = star; break;
      case dashMatch: t->terminal = dash; break;
      case forwardSlashMatch: t->terminal = forwardSlash; break;
      case equalsEqualsMatch: t->terminal = equalsEquals; break;
      case lessThanEqualsMatch: t->terminal = lessThanEquals; break;
      case greaterThanEqualsMatch: t->terminal = greaterThanEquals; break;
      case notEqualsMatch: t->terminal = notEquals; break;
      case lexicalErrorMatch: ;
      }
      
      
      if (maxNumMatchedChars == 0) {
	t->terminal = lexicalError;
	t->lexeme = text[0];
	text = text + 1;
      }
      else {
	// Consume the characters that were matched.
	text = text + maxNumMatchedChars ;
      }
      
      // Consume white space and comments before trying again for
      // another word or integer.
      numMatchedChars = consumeWhiteSpaceAndComments (whiteSpace, blockComment, lineComment, text) ;
      text = text + numMatchedChars ;
      
      
      if (first == NULL) {
	first = t;
	prev = t;
      } else {
	prev->next = t;
	prev = t;
      }
      
    }
    
    if (first == NULL) {
      first = new Token("", endOfFile, NULL);
    }
    else {
      t = first;
      while(t->next != NULL) {
	t = t->next;
      }
      last = new Token("", endOfFile, NULL);
      t->next = last;
    }

    return first;

}


int consumeWhiteSpaceAndComments (regex_t *whiteSpace, 
                                  regex_t *blockComment,
				  regex_t *lineComment,
                                  const char *text) {
    int numMatchedChars = 0 ;
    int totalNumMatchedChars = 0 ;
    int stillConsumingWhiteSpace ;

    do {
        stillConsumingWhiteSpace = 0 ;  // exit loop if not reset by a match

        // Try to match white space
        numMatchedChars = matchRegex (whiteSpace, text) ;
        totalNumMatchedChars += numMatchedChars ;
        if (numMatchedChars > 0) {
            text = text + numMatchedChars ;
            stillConsumingWhiteSpace = 1 ;
        }

        // Try to match block comments
        numMatchedChars = matchRegex (blockComment, text) ;
        totalNumMatchedChars += numMatchedChars ;
        if (numMatchedChars > 0) {
            text = text + numMatchedChars ;
            stillConsumingWhiteSpace = 1 ;
        }

        // Try to match line comments
        numMatchedChars = matchRegex (lineComment, text) ;
        totalNumMatchedChars += numMatchedChars ;
        if (numMatchedChars > 0) {
            text = text + numMatchedChars ;
            stillConsumingWhiteSpace = 1 ;
        }
    }
    while ( stillConsumingWhiteSpace ) ;    

    return totalNumMatchedChars ;
}
