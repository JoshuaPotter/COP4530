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
    
    while(cin.get(character) && flag) {
      // read character and add to expression string while there are characters
      //   unless expression says "exit"
      if(expression == "exit") {
        cout << "Flag: " << "Exiting inner loop" << endl;
        flag = false;
        break;
      } else if (character == '\n') {
        cout << "Flag: " << "Found newline" << endl;
        flag = false;
        break;
      } else {
        expression = expression + character;
        cout << "Flag: " << "Char: " << character << endl;
        cout << "Flag: " << "Exp: " << expression << endl;
        flag = true;
      }
    }
    
    if(expression == "exit") {
      flag = false;
      cout << "Flag: " << "Exiting outer loop" << endl;
    } else {
      flag = true;
      cout << "Flag: " << "Run outer loop again" << endl;
      expression = "";
    }
  }
  
	return 0;
}