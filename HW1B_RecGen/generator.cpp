#include<iostream>
#include<string>
#include "queue.h" // include queue.h or equivalent such as <queue>
using namespace std;
//----------------------------------------------
// CS421 HW1 
// Write a generator in C++ for L = {x | x is a binary number}.
// Your name: Aaron Johnson
//----------------------------------------------

// Copy the recognizer function here from the other file.
bool recognizer(string s) {
  bool isBinary; // used to check if char in string is binary

  // loop through string and determine binary number
  for(int i = 0; i < s.length(); i++) {
    if(s[i] == '0' || s[i] == '1') {
      isBinary = true;
    }
    else {
      isBinary = false;
    }
    return isBinary; // return binary number
  }
}// end of recognizer     

// main: It should create each string over E = {0,1,2} systematically
//   (short to long) and pass each string to the recognizer function
//   created in Part a).  Hint: use a queue to generate strings
//   Only those strings for which the recognizer returned TRUE
//   should be displayed. 
//   Keeps on going until the queue overflows but the user can 
//   terminate the program with control-C 
//   after about 20 strings have been displayed.
int main() { 
  string E[] = {"0","1","2"}; // set of E
  string number;// used to push into the recognizer
  string result;// used to create result to put into queue
  string userInput = "yes"; // used to determine if the loop should continue or end
  int count = 0; // used to track entries in queue
  queue q;// queue to hold entries

  // initialize queue with set E
  q.add("0");
  q.add("1");
  q.add("2");
  
  while(userInput == "yes") {
    q.remove(number);// remove oldest (front) num from queue
    if(recognizer(number)) { // run num through recognizer
      cout << number << endl; // if true, display binary number
      count++;
    }
    if(!q.isFull()) { // is queue is not full, go through set and create a new number and add to queue
      for(int i = 0; i < sizeof(E)/sizeof(E[0]); i++) {
	result = number + E[i];
	q.add(result);
      }
    }
    // boudary for queue not to overflow
    if(count >= 20) {
      // give userinput a chance to end program
      cout << "To continue enter 'yes', else enter 'exit': ";
      cin >> userInput;
    }
  }// end of while
}// end of main
