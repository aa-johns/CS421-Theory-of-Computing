//CS311 Yoshii
//INSTRUCTION:
//Look for ** to complete this program (Use control-S)
//The output should match my hw1stackDemo.out 
//=========================================================
//HW#: HW1P1 stack application (post-fix evaluation)
//Your name: Aaron Johnson
//Complier:  g++
//File type: client program client1.cpp
//===========================================================
using namespace std;
#include <iostream>
#include <stdlib.h>
#include <string>
#include "stack.h"

//Purpose of the program: Evaluate a stack's postfix expression.(e.g 345-*) If result is good display it. Else, display a catch error.

//Algorithm: Using a while loop, take the user's string expression and identify each character. While checking for a catch, push operands into the stack and apply operators when valid. Then display result when stack is empty. 
int main()
{
  stack postfixstack;  // integer stack
  string expression;   // user entered expression
  
  cout << "type a postfix expression: " ;
  cin >> expression;
  
  int i = 0;  // character position within expression
  char item;  // one char out of the expression
  
  int box1;  // receive things from pop
  int box2;  // receive things from pop

  int result; // box used to store operation result to push into stack  
  
  while (expression[i] != '\0')
    {
     try
       {
	 item = expression[i];  // current char
	 
	 // If it is an operand(number), push it (you might get Overflow exception)
	 if(item >= '0' && item <= '9')
	   {
	     postfixstack.push(item - 48); 
	   }
	 // else if it is an operator, pop two operands(you might get Underflow exception), and apply the operator to the two operands, and push the result 
	 else if(item == '+' || item == '-' || item == '*')
	   {
	     postfixstack.pop(box1);
	     postfixstack.pop(box2);
	     if(item == '-')
	       {
		 result = box2 - box1;
	       }
	     else if(item == '+')
	       {
		 result = box2 + box1;
	       }
	     else if(item == '*')
	       {
		 result = box2 * box1;
	       }
	     postfixstack.push(result);
	   }
	 // else it is an invalid item (throw exception)
	 else
	   {
	     throw "invalid item!";
	   }
       } // this closes try

      // Catch exceptions and report problems and quit the program now (exit(1)). 
      // Error messages describe what is wrong with the expression.
     catch (stack::Overflow) 
       {
	 cerr << "ERROR: Stack Overflow -- Make sure there is space in the stack before you push!" << endl; exit(1); 
       }
     catch (stack::Underflow)
       {
	 cerr << "ERROR: Stack Underflow -- Make sure there are elements in the stack before you pop!" << endl; exit(1);  
       }
     catch (char const* errormsg ) // for invalid item case
       {
	 cerr << "ERROR: Invalid character -- Make sure to use specified operands and operators!" << endl; exit(1);  
       }

     // go back to the loop after incrementing i
     i++;
    }// end of while
  
 // After the loop successfully completes: 
 // Pop the result and show it.
  postfixstack.pop(result);
  cout << "Result: " << result << endl;

  // If anything is left on the stack, an incomplete expression 
  // was found so inform the user.
  if(!postfixstack.isEmpty())
    {
      cerr << "ERROR: Incomplete expression!" << endl; exit(1);
    }

}// end of the program
