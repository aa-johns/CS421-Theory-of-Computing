#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

//---------------------------------------
// CS421 File ll1.cpp for HW3A LL1 Table-Driven Parser
// Your name: Aaron Johnson
//---------------------------------------

// Complete this to fit the HW3A specification - look for **
// Must have the same types of tracing couts as my demo program.

// Feel free to use a stack class or use a vector
// to implement your stack.  The stack will contain characters.

stack<char> cStack;
vector<char> M[3][2];  // the table of rules 
                       // 3 rows for S, A, B
                       // 2 rows for 0, 1
// Each slot contains a rule's right side
// which is a vector of characters

//  ------- conversion functions ------------------------

// to convert non-terms S, A, B to table rows 0, 1, 2
int toRow(char c) {
  //**  bunch of if then else
  if (c == 'S') {
    return 0;
  } 
  else if (c == 'A') {
    return 1;
  } 
  else if (c == 'B') {
    return 2;
  }
  else {
    return -1;
  }
}

// to convert '0' and '1' to table columns 0 and 1 
int toCol(char c) {
  // ** bunch of if then else
  if (c == '0') {
    return 0;
  } 
  else if (c == '1') {
    return 1;
  }
  else {
    return -1;
  }
}

// to convert row 0, 1, 2 to non-terms S, A and B
char toNonterm(int r) {
  // ** bunch of if then else
  if (r == 0) {
    return 'S';
  } 
  else if (r == 1) {
    return 'A';
  } 
  else if (r == 2) {
    return 'B';
  }
  else {
    return -1;
  }
}

// ** Then complete the following functions.-----------------------------

// to display a rule's rhs which is in vector V
void displayVector(vector<char> V) {
  cout << "\t";
  // ** display V horizontally e.g. 0 A 0
  for (auto const it: V) {
    cout << " " << it;
  }
}

// to read in the rules into M, make sure ; is not stored
void readrules() { 
  ifstream fin ("rules", ios::in);
  char firstChar;
  char nextChar;
  int row, col;
  // For each line of "rules" (e.g. S  0 A 0 ;) 
  // The first char of a line determines the row of M
  // The second char of a line determine the column of M  
  // Note that each entry of M (the second char up to ;)
  // will be a vector representing 
  // the right hand side of a rule (rhs)
  while (fin >> firstChar) {
    row = toRow(firstChar);
    fin >> nextChar;
    col = toCol(nextChar);

    while (nextChar != ';') {
      M[row][col].emplace_back(nextChar);
      fin >> nextChar;
    }
  }
  
  // ** Display the table nicely  
  //    use toNonterm to show row labels (S, A, B)
  //    use displayVector for each content 
  for (int i = 0; i < 3; ++i) {
    cout << toNonterm(i) << ':';
    for (auto const &it: M[i]) {
      displayVector(it);
    }
    cout << endl;
  }
}

//  pushes V contents to the stack 
void addtostack(vector<char> V) {  
  cout << "Pushing rhs of a rule to the stack." << endl;
  // **  be careful of the order
  // because 1 0 0 means 1 will be at the top of the stack
  for (auto it = V.rbegin(); it != V.rend(); it++) {
    cStack.push(*it);
  }
}

// Additional Stack Functions ------------------------
bool terminal(char c) {
  return toCol(c) != -1;
}

void displayStack() {
  stack<char> cStackCopy(cStack);

  cout << "Stack:" << endl;

  while (!cStackCopy.empty()) {
    cout << cStackCopy.top() << endl;
    cStackCopy.pop();
  }
  cout << "------------------------" << endl;
}

// Main -------------------------------------
int main() { 
  readrules();  // M is filled and displayed 
  
  string ss;
  char nextChar;
  cout << "Enter a string made of 0's and/or 1's: ";
  cin >> ss;

  // ** push 'S' onto the stack to start
  cStack.push('S');

  cout << "Stack:";
  // ** display the stack vertically from top to bottom
  
  int i = 0;  // index for ss
  while (ss[i] != '\0')  // for each char of ss
    {
      // Based on ss[i] and the top of stack, update the stack: 
      // ** note that empty stack will cause immediate failure  
      // ** note that top of stack terminal and ss[i] mismatching will cause immediate failure 
      // ** note that no entry in M for the top of stack (non-terminal) and ss[i] will cause immediate failure  (use toRow and toCol to look up M)
      // ** otherwise, addtoStack the M entry based on ss[i] and the top of stack 
      if (cStack.empty()) {
	cout << "Stack: [Empty]" << endl;
	cout << "------------------------" << endl;
	cout << "current char is: " << ss[i] << endl;
	cout << "Reject! Stack is Empty.." << endl;
	return -1;
      } 
      else {
	displayStack();
      }
      
      nextChar = cStack.top();
      cStack.pop();
      cout << "current char is: " << ss[i] << endl;

      if (!terminal(ss[i])) {
	cout << "Reject! No Rule Found.." << endl;
	return -1;
      }

      if (!terminal(nextChar)) {
	addtostack(M[toRow(nextChar)][toCol(ss[i])]);
	continue;
      } 
      else if (ss[i] == nextChar) {
	cout << "Matched!" << endl;
      } 
      else {
	cout << "Reject! Mismatch Error.." << endl;
	return 1;
      }
      cout << endl;
      i++;
    } // end of string

  // ** Here, check for success for failure based on stack empty or not
  if (cStack.empty()) {
    cout << "Stack [Empty]" << endl;
    cout << "------------------------" << endl;
    cout << "Accepted!" << endl;
    return 0;
  }
  else {
    displayStack();
    cout << "Reject! Input is too short.." << endl;
    return -1;
  }

}// end of main
