#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
//--------------------------------------
// CS421 File td.cpp for HW2B Table-Driven Scanner
// Your name: Aaron Johnson
//--------------------------------------
// Complete this to fit the HW2B specification - look for **
// Must have the same types of tracing couts as my demo program.
//--------------------------------------

// info on each DFA
struct info {
  string name; // token name
  int startstate;
  int finalstate;
};

info DFAs[4]; // store up to 4 dfas' start and final
int TRS[10][4]; // store all trs's - states 0-9 and chars a b c d -- all dfas transitions are in here 

// ----- utility functions -----------------------

int readTables() {  
  ifstream fin ("trs.txt", ios::in);
  ifstream fin2 ("dfas.txt", ios::in);
  // ** Read in the files into TRS and DFAs
  int numDFAs, i, j, k;
  // TRS
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 4; j++) {
      fin >> TRS[i][j];
    }
  }
  // DFA
  for (int k = 0; k < 4; k++) {
    fin2 >> DFAs[k].name >> DFAs[k].startstate >> DFAs[k].finalstate;
    numDFAs++;
  }

  fin.close();
  fin2.close();
  
  // ** Return how many DFAs were read
  return numDFAs;
}

void displayTables(int numDFAs) {
  // ** display TRS nicely labeled                                                           
  cout << "         a b c d" << endl;
  for (int i = 0; i < 10; i++) {
    cout << "State " << i << ": ";
    for (int j = 0; j < 4; j++) {
      if (TRS[i][j] == -1) {
        cout << "  ";
      } else {
        cout << TRS[i][j] << " ";
      }
    }
    cout << endl;
  }

  // ** display DFAs nicely labeled
  for (int i = 0; i < numDFAs; i++) {
    if (!DFAs[i].name.empty()) {
      cout << "Token " << DFAs[i].name << ": " << DFAs[i].startstate 
	   << " is start and end is " << DFAs[i].finalstate << endl;
    }
  }
}

bool accept(info dfa, string word) {
  /* ** Does the dfa accept the word? Start with the start state of the DFA and
     look up the next state in TRS for each char in word. At the end of the word, 
     make sure you are in the final state of the DFA. Use a formula to convert chars 
     to TRS col numbers. */
  int charpos = 0;
  int state = dfa.startstate;
  cout << "Trying dfa " << dfa.name << " -------------" << endl;
  while (word[charpos] != '\0')
    {
      cout << "state: " << state << " char: " << word[charpos] << endl;
      if (state == dfa.startstate && word[charpos] == dfa.name[0]) {
	  state = dfa.startstate;
	}
      else {
	if (state == dfa.startstate && word[charpos] == dfa.name[1]) {
	  state = dfa.finalstate;
	}else
	  {
	    state = -1;
	  }
      }
      cout << "new state: " << state << endl;
      if (state == -1) {
	return(false);
      }
      charpos++;

    }//end of while loop
  
  if (state == dfa.finalstate) { 
    return(true); //end in a final state
  } else {
    return(false);
  }
}

int main() {
  cout << "This is a table driven scanner. Needs trs.txt and dfas.txt." << endl;
  cout << "States are 0 to 9 and chars are a to d" << endl;
  
  int numDFA = readTables(); // how many DFAs were read
  displayTables(numDFA);     // DISPLAY TABLES
  cout << ".....done reading tables...." << endl;
  
  string word;
  while (true)
    { 
      cout << "@@Enter a string: ";
      cin >> word;
      /* ** try the DFAs one by one and see if the word is accepted
	 if so, display the word and the token name,
	 if no DFA does, generate a lexical error message. */
      for (int i = 0; i < 4; i++) {
	if (accept(DFAs[i], word)) {
	  cout << "Found token " << DFAs[i].name << endl;
	  break;
	}
	if (DFAs[i].name.empty()) {
          cout << ">>>>Lexical error..." << endl;
          break;
        }
      }
      cout << "do control-C to quit" << endl;
    }
}//the end
