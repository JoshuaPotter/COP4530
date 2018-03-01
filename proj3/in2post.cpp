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

void stackToExpression(Stack<char> &symbols, string &expression);
int precedence(char c);
bool operandFlag(char c);
bool operatorFlag(char c);

int main() {
  bool flag = true; // ask user for another expression if true
  bool errorFlag = false;
  char character;
  char prevCharacter;
  string expression;
  Stack<char> symbols;
  symbols.push('\0'); // head element
  
  while(flag) {
    cout << "Enter infix expression (\"exit\" to quit): ";
    
    while(cin.get(character) && character != '\n' && !errorFlag) {
      // read character and add to expression string while not newline      
      if (character == '(') {
        // character is open parentheses
        symbols.push(character);
      }  else if(operandFlag(character)) {
        // character is operand
        if(operandFlag(prevCharacter)) {
          // previous character was an operand also, we are missing an operator
          cout << "Error: Missing operators in the expression" << endl;
          errorFlag = true;
        } else {
          expression = expression + character;
        }
      } else if (character == ')') {
        // character is closing parentheses
        while(symbols.top() != '~' && symbols.top() != '(') {
          // add everything inside parentheses to stack
          stackToExpression(symbols, expression);
        }
        
        if(symbols.top() == '(') {
          symbols.pop();
        }
      } else if (character == ' ') {
        // character is whitespace
        
      } else {
        // character is operator
        if(operatorFlag(prevCharacter)) {
          // previous character was an operator also, we are missing an operand
          cout << "Error: Missing operands in the expression" << endl;
          errorFlag = true;
        } else {
          while(symbols.top() != '\0' && (precedence(character) <= precedence(symbols.top()))) {
            stackToExpression(symbols, expression);
          }
          symbols.push(character);
        }
      }
      
      if(character != ' ') {
        prevCharacter = character;
      }
    }
     
    // empty stack into expression after reading all characters
    while(symbols.top() != '\0') {
      stackToExpression(symbols, expression);
    }

    if(!errorFlag) { 
      cout << "Postfix expression: ";
      for(char &c : expression) {
        cout << c << " ";
      }
      cout << endl;
    }
    
    // if expression isn't "exit", empty expression for next loop
    //    otherwise exit the loop
    if(expression != "exit") {
      expression = "";
      errorFlag = false;
      character = '\0'; // flush character
      cin.ignore(10000, '\n'); // flush cin.get
    } else {
      flag = false;
    }
  }
  
	return 0;
}

void stackToExpression(Stack<char> &symbols, string &expression) {
  // empty stack into expression
  char temp = symbols.top();
  symbols.pop();
  expression = expression + temp;
}

int precedence(char c) {
  // return precedence of operator
  if(c == '+' || c == '-') {
    return 1;
  } else if (c == '*' || c == '/') {
    return 2;
  } else {
    return 0;
  }
}

bool operandFlag(char c) {
  if((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
    return true;
  } else {
    return false;
  }
}

bool operatorFlag(char c) {
  if(c == '+' || c == '-' || c == '*' || c == '/') {
    return true;
  } else {
    return false;
  }
}