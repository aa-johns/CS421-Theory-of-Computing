#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "scanner.cpp"
using namespace std;

/*
  INSTRUCTION:  Complete all ** parts.
  You may use any method to connect this file to scanner.cpp
  that you had written.  
  e.g. You can copy scanner.cpp here by:
  cp ../ScannerFiles/scanner.cpp .  
  and then append the two files into one: 
  cat scanner.cpp parser.cpp > myparser.cpp
*/
//=================================================
// File parser.cpp written by Group Number: 12
//=================================================

// ----- Four Utility Functions and Globals -------------------------------

// function prototypes
void s();
void afterSubject();
void afterNoun();
void afterObject();
void noun();
void verb();
void be();
void tense();

// global variables
token_type saved_token;
string saved_lexeme;
bool token_available = false;

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
//    to display syntax error messages as specified by me. 
// Type of error: Thrown when match fails. Expected token but found saved_lexeme instead 
// Done by: Trent Hildebrand 
void syntaxerror1(token_type expected_token, string saved_lexeme) {
  cout << "SYNTAX ERROR: expected " << tokenName[expected_token] << " but found " << saved_lexeme << endl;
  exit(1);
}

// Type of error: Used in switch default when an unexpected word is found in a parser function
// Done by: Trent Hildebrand
void syntaxerror2(string saved_lexeme, string parser_function) {
  cout << "SYNTAX ERROR: unexpected " << saved_lexeme << " found in " << parser_function << endl;
  exit(1);
}

// ** Need the updated match and next_token with 2 global vars
// saved_token and saved_lexeme

// Purpose: Looks ahead to see what token comes next from the scanner
// Done by: Trent Hildebrand
token_type next_token() {
  // if there is no saved token yet
  if (!token_available) {
    scanner(saved_token, saved_lexeme);
    cout << "Scanner called using word: " << saved_lexeme << endl;
    token_available = true;
  }
  return saved_token;
}

// Purpose: Checks and eats up the expected token
// Done by: Aaron Johnson
bool match(token_type expected) {
  // mismatch has occurred with the next token
  if (next_token() != expected) {
    syntaxerror1(expected, saved_lexeme);
  }
  // match has occurred
  else {
    cout << "Matched " << tokenName[expected] << endl;
    token_available = false;
    return true;
  }
}

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Be sure to put the name of the programmer above each function

// Grammar: <story> ::= <s>{<s>}
// Done by: Aaron Johnson
void story() {
  cout << "Processing <story>" << endl;
  s();
  while (true && (saved_lexeme != "eofm")) {
    s();
  }
  cout << "Successfully parsed <story>" << endl;
}

// Grammar: <s> ::= [CONNECTOR]<noun>SUBJECT<after subject>   
// Done by: Aaron Johnson
void s() {
  next_token();
  if (saved_lexeme != "eofm") {
    cout << "Processing <s>" << endl;

    if(next_token() == CONNECTOR) {
      match(CONNECTOR);
    }   
    noun();
    match(SUBJECT);
    afterSubject();
  }
}

// Grammar: <after subject> ::= <verb><tense>PERIOD|<noun><after noun>
// Done by: Aaron Johnson
void afterSubject() {
  cout << "Processing <afterSubject>" << endl;
  
  switch(next_token())
    {
    case WORD2:
      verb();
      tense();
      match(PERIOD);
      break;
    case WORD1:
      noun();
      afterNoun();
      break;
    case PRONOUN:
      noun();
      afterNoun();
      break;
    default:
      syntaxerror2(saved_lexeme, "<afterSubject>");
    }
}

// Grammar: <after noun> ::= <be>PERIOD|DESTINATION<verb><tense>PERIOD|OBJECT<after object>
// Done by: Aaron Johnson 
void afterNoun() {
  cout << "Processing <afterNoun>" << endl;
  switch(next_token())
    {
    case IS:
      be();
      match(PERIOD);
      break;
    case WAS:
      be();
      match(PERIOD);
      break;
    case DESTINATION:
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;
    case OBJECT:
      match(OBJECT);
      afterObject();
      break;
    default:
      syntaxerror2(saved_lexeme, "<afterNoun>");
    }
}

// Grammar: <after object> ::= <verb><tense>PERIOD|<noun>DESTINATION<verb><tense>PERIOD
// Done by: Aaron Johnson 
void afterObject() {
  cout << "Processing <afterObject>" << endl;
  switch(next_token())
    {
    case WORD2:
      verb();
      tense();
      match(PERIOD);
      break;
    case WORD1:
      noun();
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;
    case PRONOUN:
      noun();
      match(DESTINATION);
      verb();
      tense();
      match(PERIOD);
      break;
    default:
      syntaxerror2(saved_lexeme, "afterObject");
    }
}

// Grammar: <noun> ::= WORD1|PRONOUN
// Done by: Trent Hildebrand
void noun() {
  cout << "Processing <noun>" << endl;
  switch(next_token())
    {
    case WORD1:
      match(WORD1);
      break;
    case PRONOUN:
      match(PRONOUN);
      break;
    default:
      syntaxerror2(saved_lexeme, "<noun>");
    }
}

// Grammar: <verb> ::= WORD2
// Done by: Trent Hildebrand 
void verb() {
  cout << "Processing <verb>" << endl;
  switch(next_token())
    {
    case WORD2:
      match(WORD2);
      break;
    default:
      syntaxerror2(saved_lexeme, "<verb>");
    }
}

// Grammar: <be> ::= IS|WAS
// Done By: Trent Hildebrand 
void be() {
  cout << "Processing <be>" << endl;
  switch(next_token())
    {
    case IS:
      match(IS);
      break;
    case WAS:
      match(WAS);
      break;
    default:
      syntaxerror2(saved_lexeme, "<be>");
    }
}

// Grammar: <tense> ::= VERBPAST|VERBPASTNEG|VERB|VERBNEG
// Done by: Trent Hildebrand
void tense() {
  cout << "Processing <tense>" << endl;
  switch(next_token())
    {
    case VERBPAST:
      match(VERBPAST);
      break;
    case VERBPASTNEG:
      match(VERBPASTNEG);
      break;
    case VERB:
      match(VERB);
      break;
    case VERBNEG:
      match(VERBNEG);
      break;
    default:
      syntaxerror2(saved_lexeme, "<tense>");
    }
}

//----------- Driver ---------------------------

// The new test driver to start the parser
// Done by: Aaron Johnson
int main() {
  string filename;
  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  story();
  //** closes the input file 
  fin.close();

}// end

//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
