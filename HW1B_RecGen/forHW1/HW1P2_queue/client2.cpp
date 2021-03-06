//CS311 Yoshii
//INSTRUCTION:
//Look for ** to complete this program 
//The string output should match my hw1queueDemo.out 

//=========================================================
//HW#: HW1P2 queue application (generate all strings)
//Your name: Aaron Johnson
//Complier:  g++
//File type: client program client2.cpp
//===========================================================
using namespace std;
#include <iostream>
#include <stdlib.h>
#include <string>
#include "queue.h"

//Purpose of the Program: Using a queue, generate strings using the string characters A,B,C.
//Algorithm: Create a queue and fill with string characters A,B,C. Create a while loop that keeps looping until full. A temporary string variable (phrase) is used as a box to hold and print removed elements. phrase is then concatenated with A,B,C and added to the queue. Catches are used for finding errors.  
int main()
{
  queue myqueue; // create a new queue
  // fill queue with A,B,C
  myqueue.add("A");
  myqueue.add("B");
  myqueue.add("C");
  
  // loop while queue is not full
  while(!myqueue.isFull())
    {
      try
	{
	  string phrase; // temporary variable used to store and print
	  if(!myqueue.isEmpty()) // if queue is not empty
	    {
	      myqueue.remove(phrase); // remove front element
	    }
	  cout << phrase << endl; // print phrase

	  if(!myqueue.isFull()) // if queue is not full
	    {
	      //concatenate and add new phrase to queue
	      myqueue.add(phrase + "A"); 
	      myqueue.add(phrase + "B");
	      myqueue.add(phrase + "C");
	    }

	}// end of try
  
      //catch functions
      catch(queue::Underflow)
	{
	  cerr << "Cannot Remove..." << endl; exit(1);
	}
      catch(queue::Overflow)
	{
	  cerr << "Cannot Add..." << endl; exit(1);
	}
    }
  return 0;
}
