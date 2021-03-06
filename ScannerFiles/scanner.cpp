#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 12
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA 
// Done by: Christopher Fleury
// RE: (vowel | vowel n | consonant vowel | consonant vowel n |
// consonant-pair vowel | consonant-pair vowel n)^+
bool word (string s) {
  int state = 0;
  int charpos = 0;
  bool vowel;
  bool starter;
  bool non;

  while (s[charpos] != '\0')  {
      char c = s[charpos];
      vowel = c == 'a' || c == 'e' || c == 'i' || c == 'o'
	|| c == 'u' || c == 'I' || c == 'E';
      starter = c == 'b' || c == 'g' || c == 'h' || c == 'k'
	|| c == 'm' || c == 'p' || c == 'r';
      non = c == 'd' || c == 'j' || c == 'w' || c == 'y' || c == 'z';
      
      if (state == 0 && vowel)
	state = 0;
      else if (state == 0 && c == 'n')
	state = 1;
      else if (state == 0 && c == 'c')
	state = 2;
      else if (state == 0 && c == 's')
	state = 3;
      else if (state == 0 && c == 't')
	state = 4;
      else if (state == 0 && starter)
	state = 5;
      else if (state == 0 && non)
	state = 6;
      else if (state == 1 && vowel)
	state = 0;
      else if (state == 1 && c == 'c')
	state = 2;
      else if (state == 1 && c == 's')
	state = 3;
      else if (state == 1 && c == 't')
	state = 4;
      else if (state == 1 && (c == 'n' || starter))
	state = 5;
      else if (state == 1 && non)
	state = 6;
      else if (state == 2 && c == 'h')
	state = 6;
      else if (state == 3 && vowel)
	state = 0;
      else if (state == 3 && c == 'h')
	state = 6;
      else if (state == 4 && vowel)
	state = 0;
      else if (state == 4 && c == 's')
	state = 6;
      else if (state == 5 && vowel)
	state = 0;
      else if (state == 5 && c == 'y')
	state = 6;
      else if (state == 6 && vowel)
	state = 0;
      else 
	return false;
      charpos++;
    }//end of while

  // where did I end up????
  if (state == 0 || state == 1) return true;  // end in a final state
  else return false;
}

// PERIOD DFA 
// Done by: Christopher Fleury
bool period (string s) {
  int state = 0;
  int charpos = 0;

  while (s[charpos] != '\0') {
      if (state == 0 && s[charpos] == '.')
	state = 1;
      else
	return false;
      charpos++;
    }
  if (state == 1) return true;
  else return false;
}

// ------ Three  Tables -------------------------------------
// TABLES Done by: Trent Hildebrand 

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, EOFM, etc.
enum token_type { ERROR, WORD1, WORD2, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, PERIOD, EOFM };

// ** For the display names of tokens - must be in the same order as the tokentype.
string tokenName[30] = { "ERROR", "WORD1", "WORD2", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", "WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "PERIOD", "EOFM"};

// ** Need the reservedwords table to be set up here. 
// ** Do not require any file input for this. Hard code the table.
// ** a.out should work without any additional files.
struct reservedWords {
  const char* string;
  token_type token;
}
  
  reservedWords[] = {
    {"masu",VERB},
    {"masen",VERBNEG},
    {"mashita",VERBPAST},
    {"masendeshita",VERBPASTNEG},
    {"desu",IS},
    {"deshita",WAS},
    {"o", OBJECT},
    {"wa", SUBJECT},
    {"ni", DESTINATION},
    {"watashi",PRONOUN},
    {"anata",PRONOUN},
    {"kare",PRONOUN},
    {"kanojo", PRONOUN},
    {"sore", PRONOUN},
    {"mata",CONNECTOR},
    {"soshite", CONNECTOR},
    {"shikashi", CONNECTOR},
    {"dakara", CONNECTOR}
  };

//RESERVED WORDS

// ------------ Scanner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Aaron Johnson
int scanner(token_type& tt, string& w) {
  
  fin >> w;
  
  int rowCount = sizeof reservedWords/ sizeof reservedWords[0];

  if (period(w)) {
    tt = PERIOD;
  }
  else if (w == "eofm") {
    
  }
  else if (word(w)) {
    for (int i = 0; i < rowCount; i++) {
      if (w == reservedWords[i].string) {
	tt = reservedWords[i].token;
	return 0;
      }
    }
    char lastChar = w[w.length() - 1];
    if (lastChar == 'I' || lastChar == 'E') {
      tt = WORD2; 
    }
    else {
      tt = WORD1;
    }
  }
  else {
    cout << "LEXICAL ERROR: " << w << " is not a valid token" << endl;
    tt = ERROR;
  }
  return 0;
}//the end of scanner

// The temporary test driver to just call the scanner repeatedly  
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!! 
// Done by:  Louis
int main()
{
  token_type thetype;
  string theword; 
  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str());

  // the loop continues until eofm is returned.
  while (true)
    {
      scanner(thetype, theword);  // call the scanner which sets
      // the arguments  
      if (theword == "eofm") break;  // stop now

      cout << "Type is:" << tokenName[thetype] << endl;
      cout << "Word is:" << theword << endl;   
    }

  cout << "End of file is encountered." << endl;
  fin.close();

}// end
