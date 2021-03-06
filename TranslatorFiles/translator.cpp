#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include "scanner.cpp"
using namespace std;

/* INSTRUCTION:  copy your parser.cpp here
   cp ../ParserFiles/parser.cpp .
   Then, insert or append its contents into this file and edit.
   Complete all ** parts.
*/

//=================================================
// File translator.cpp written by Group Number: 12
//=================================================

// ----- Additions to the parser.cpp ---------------------

// ** Declare Lexicon (i.e. dictionary) that will hold the content of lexicon.txt
// Make sure it is easy and fast to look up the translation.
// Do not change the format or content of lexicon.txt 
//  Done by: ** 

// ** Additions to parser.cpp here:
//    getEword() - using the current saved_lexeme, look up the English word
//                 in Lexicon if it is there -- save the result   
//                 in saved_E_word
//  Done by: **
//    gen(line_type) - using the line type,
//                     sends a line of an IR to translated.txt
//                     (saved_E_word or saved_token is used)
//  Done by: ** 

// ----- Changes to the parser.cpp content ---------------------

// ** Comment update: Be sure to put the corresponding grammar 
//    rule with semantic routine calls
//    above each non-terminal function 

// ** Each non-terminal function should be calling
//    getEword and/or gen now.

void s();
void afterSubject();
void afterNoun();
void afterObject();
void noun();
void verb();
void be();
void tense();

// global variables
ofstream outputFile;
string saved_lexeme;
bool token_available = false;
token_type saved_token;
string savedEword;

// vectors used for dictionary
// Done by: Aaron Johnson
vector<string> japaneseWords;
vector<string> englishWords;

// using the current saved_lexeme, look up the English word in Lexicon if it is there -- save the result in saved_E_word
// Done by: Aaron Johnson
void getEword() {
  bool found = false;
  for (int i = 0; i < japaneseWords.size(); i++) {
    if (japaneseWords[i] == saved_lexeme) {
      savedEword = englishWords[i];
      found = true;
    }
  }
  if (found == false) {
    savedEword = saved_lexeme;
  }
}

// using the line type sends a line of an IR to translated.txt (saved_E_word or saved_token is used)
// Done by: Trent Hildebrand
void gen(string lineType) {
  if (lineType == "TENSE") {
    outputFile << lineType << ": " << tokenName[saved_token] << endl;
  }
  else {
    outputFile << lineType << ": " << savedEword << endl;
  }
}

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)      
//    to display syntax error messages as specified by me.

// Type of error: Thrown when match fails. Expected token but found saved_lexeme instead
// Done by: Trent Hildebrand
void syntaxerror1(token_type expected_token, string saved_lexeme) {
  cout << "SYNTAX ERROR: expected " << tokenName[expected_token] << " but found " << saved_lexeme << endl;
  exit(1);
}

// Type of error: Used in switch default when an unexpected word is found ina parser function
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
    outputFile << endl;
    s();
  }
  cout << "Successfully parsed <story>" << endl;
}

// Grammar: <s> ::= [CONNECTOR #getEword# #gen(???CONNECTOR???)#] <noun> #getEword# SUBJECT #gen(???ACTOR???) <after subject>
// Done by: Aaron Johnson
void s() {
  next_token();
  if (saved_lexeme != "eofm") {
    cout << "Processing <s>" << endl;

    if(next_token() == CONNECTOR) {
      match(CONNECTOR);
      getEword();
      gen("CONNECTOR");
    }
    noun();
    match(SUBJECT);
    gen("ACTOR");
    afterSubject();
  }
}

// Grammar: <after subject> ::= <verb> #getEword# #gen(???ACTION???)# <tense> #gen(???TENSE???)# PEROD | <noun> #getEword# <after noun>
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

// Grammar: <after noun> ::= <be> #gen(???DESCRIPTION???)# #gen(???TENSE???)# PERIOD| DESTINATION #gen(???TO???)# <verb> #getEword# #gen(???ACTION???)# <tense> #gen(???TENSE???) PERIOD | OBJECT #gen(???OBJECT???)# <after object> 
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
      gen("TO");
      verb();
      tense();
      match(PERIOD);
      break;
    case OBJECT:
      match(OBJECT);
      gen("OBJECT");
      afterObject();
      break;
    default:
      syntaxerror2(saved_lexeme, "<afterNoun>");
    }
}

// Grammar: <after object> ::= <verb> #getEword# #gen(???ACTION???)# <tense> gen(???TENSE???) PERIOD | <noun> #getEword# DESTINATION #gen(???TO???)# <verb> #getEword# #gen(???ACTION???)# <tense> #gen(???TENSE???)# PERIOD
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
      gen("TO");
      verb();
      tense();
      match(PERIOD);
      break;
    case PRONOUN:
      noun();
      match(DESTINATION);
      gen("TO");
      verb();
      tense();
      match(PERIOD);
      break;
    default:
      syntaxerror2(saved_lexeme, "afterObject");
    }
}

// Grammar: <noun> ::= WORD1 | PRONOUN
// Done by: Trent Hildebrand
void noun() {
  cout << "Processing <noun>" << endl;
  switch(next_token())
    {
    case WORD1:
      match(WORD1);
      getEword();
      break;
    case PRONOUN:
      match(PRONOUN);
      getEword();
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
      getEword();
      gen("ACTION");
      break;
    default:
      syntaxerror2(saved_lexeme, "<verb>");
    }
}

// Grammar: <be> ::= IS | WAS
// Done By: Trent Hildebrand 
void be() {
  cout << "Processing <be>" << endl;
  gen("DESCRIPTION");
  switch(next_token())
    {
    case IS:
      match(IS);
      gen("TENSE");
      break;
    case WAS:
      match(WAS);
      gen("TENSE");
      break;
    default:
      syntaxerror2(saved_lexeme, "<be>");
    }
}

// Grammar: <tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG
// Done by: Trent Hildebrand 
void tense() {
  cout << "Processing <tense>" << endl;
  switch(next_token())
    {
    case VERBPAST:
      match(VERBPAST);
      gen("TENSE");
      break;
    case VERBPASTNEG:
      match(VERBPASTNEG);
      gen("TENSE");
      break;
    case VERB:
      match(VERB);
      gen("TENSE");
      break;
    case VERBNEG:
      match(VERBNEG);
      gen("TENSE");
      break;
    default:
      syntaxerror2(saved_lexeme, "<tense>");
    }
}

// ---------------- Driver ---------------------------

// The final test driver to start the translator
// Done by:  Trent Hildebrand and Aaron Johnson
int main() {
  //** opens the lexicon.txt file and reads it into Lexicon
  ifstream lexicon;
  string japanese;
  string english;
  string filename;
  lexicon.open("lexicon.txt");
  cout << "opening file..." << endl;
  while (lexicon) {
    lexicon >> japanese;
    lexicon >> english;
    japaneseWords.push_back(japanese);
    englishWords.push_back(english);
  }

  //** closes lexicon.txt 
  lexicon.close();

  //** opens the output file translated.txt
  outputFile.open("translated.txt");

  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());
  //** calls the <story> to start parsing
  story();
  //** closes the input file
  fin.close();
  //** closes traslated.txt
  outputFile.close();
}// end
//** require no other input files!
//** syntax error EC requires producing errors.txt of error messages
//** tracing On/Off EC requires sending a flag to trace message output functions
