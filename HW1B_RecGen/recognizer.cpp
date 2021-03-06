#include<iostream>
#include<string>
using namespace std;

//-------------------------------------------------------
// CS421 HW1 
// Write a recognizer in C++ for L = {x | x is a binary number}.
// Your name: Aaron Johnson
//-------------------------------------------------------

//  The recognizer function should return TRUE or FALSE 
//  checking each character
//  to make sure it is 0 or 1. (leading 0's are allowed).
bool recognizer(string s) { 
  bool isBinary; // used to return result
  
  // loop through string and determine if 's' is a binary number
  for(int i = 0; i < s.length(); i++)
    {
      if(s[i] == '0' || s[i] == '1') {
	isBinary = true;
      }
      else {
	isBinary = false;
      }
    }
  return isBinary;
}// end of recognizer

//main: Given a string (from E) cined from the user, pass it to
//      the recognizer function.
//      Cout "YES IN L" or "NO NOT IN L" depending on what was returned.
int main() {
  string E; // user inputted string
  bool isBinary; // boolean used to receive value from recognizer()
  
  // loop that asks user for a string and prints results or exits 
  while (E != "end") {
    cout << "Enter a string to check, enter 'end' to exit: ";
    cin >> E;
    isBinary = recognizer(E);
    if(isBinary == true) {
      cout << "YES in L" << endl;
    }
    else if(isBinary == false && E == "end") {
      cout << "Exiting program..." << endl;
    }
    else if(isBinary == false) {
      cout << "NO NOT in L" << endl;
    }
  }// end of while
}// end of main
