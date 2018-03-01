/*
  Name: Joshua Potter (jop13)
  Class: COP4530
  Assignment 3 - in2post.cpp
*/

#include <iostream>
#include <string>
#include "stack.h"

using namespace std;
using namespace cop4530;

int main() {
  bool flag = true; // ask user for another expression if true
  char character;
  string expression;
  
  while(flag) {
    cout << "Enter infix expression (\"exit\" to quit): ";
    
    while(cin.get(character) && character != '\n') {
      // read character and add to expression string while not newline
      expression = expression + character;
//       cout << "Flag: " << "Char: " << character << endl;
//       cout << "Flag: " << "Exp: " << expression << endl;
    }
    
    // if expression isn't exit, empty expression for next loop
    //    otherwise exit the loop
    if(expression != "exit") {
//       cout << "Flag: " << "Run outer loop again" << endl;
      expression = "";
    } else {
      flag = false;
    }
  }
  
	return 0;
}