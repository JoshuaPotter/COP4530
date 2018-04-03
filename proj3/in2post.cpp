/*
  Name: Joshua Potter (jop13)
  Class: COP4530
  Assignment 3 - in2post.cpp
*/

#include <iostream>
#include <sstream>
#include <string>
#include "stack.h"

using namespace std;
using namespace cop4530;

/*

	Function Declarations

*/
void stackToExpression(Stack<char> &symbols, string &expression);
int precedence(string s);
bool operandFlag(string s);
bool operatorFlag(string s);
bool foundDoubleSpace(char l, char r);
bool validExpression(int whitespace, vector<string> expression);
float evaluateExpression(vector<string> expression);

int main() {
  char character = '\0';
  bool flag = true; // ask user for another expression if true
	int whitespace = 0; // counts spaces in user input
	string originalExpression = ""; // stores expression
  string expression = ""; // stores expression for manipulation
	string variable = ""; // for variable character storing
	vector<string> postfixExpression; // contains formatted postfix expression after manipulations
  Stack<char> symbols; // for symbol organization within expression
	
  symbols.push('\0'); // head element
  
  while(flag) {
    cout << "Enter infix expression (\"exit\" to quit): ";
    
    while(cin.get(character) && character != '\n') {
			
			// keep copy of user input
			originalExpression = originalExpression + character;
			
      // read character and add to expression string while not newline      
      if (character == '(') {
				
        // character is open parentheses
        symbols.push(character);
				
      } else if (character == ' ') {
				
        // character is whitespace, store any variable created
				expression = expression + variable + " ";
				variable = "";
				++whitespace;
				
      } else if(operandFlag(string(1, character))) {
				
        // character is operand, build a variable
				variable = variable + character;
				
      } else if (character == ')') {
				
        // character is closing parentheses
        while(symbols.top() != '\0' && symbols.top() != '(') {
					
          // add everything inside parentheses to stack
          stackToExpression(symbols, expression);
					
        }
        
        if(symbols.top() == '(') {
					
					// pop the final parantheses
          symbols.pop();
					
        }

      } else {
				
        // character is operator
				while(symbols.top() != '\0' && (precedence(string(1, character)) <= precedence(string(1, symbols.top())))) {
					stackToExpression(symbols, expression);
				}
				
				symbols.push(character);
				
			}
			
    }
		cout << endl;
		
		// store any left over variable
		expression = expression + variable + " ";
    
    // empty stack into expression after reading all characters
    while(symbols.top() != '\0') {
      stackToExpression(symbols, expression);
    }
		
		// if the expression isn't empty,
		//    move string expression to vector
    if(!expression.empty()) {
			istringstream iss(expression);
			string temp;
			while(iss >> temp) {
				postfixExpression.push_back(temp);
				if(whitespace > 0) {
					postfixExpression.push_back(" ");
				}
			}
			if(whitespace > 0) {
				postfixExpression.pop_back();
			}
    }
    
    // if original user input isn't "exit", print expression, flush variables, repeat loop
    //    otherwise exit loop
    if(originalExpression != "exit") {
			// print and evaluated if valid expression
			//    otherwise print originalExpression (unmanipulated)
			if(validExpression(whitespace, postfixExpression)) {
				cout << "Postfix expression: ";
				for(auto &s : postfixExpression) {
					if (s != "\n" && s != " ") {
						cout << s << " ";
					}
				}
				cout << endl;
				// evaluate the expression
				cout << "Postfix evaluation: " << evaluateExpression(postfixExpression) << endl;
			} else {
				cout << "Postfix expression: " << expression << endl;
				cout << "Postfix evaluation: " << expression << " = " << expression << endl;
			}
			
      // flush variables
      expression = "";
      originalExpression = "";
			postfixExpression.clear();
      character = '\0';
			variable = "";
    } else {
      flag = false;
    }
  }
  
	return 0;
}

/* 

Function Definitions 

*/

void stackToExpression(Stack<char> &symbols, string &expression) {
  // empty stack into expression
  char temp = symbols.top();
  symbols.pop();
  expression = expression + temp + " ";
}

int precedence(string c) {
  // return precedence of operator
  if(c == "+" || c == "-") {
    return 1;
  } else if (c == "*" || c == "/") {
    return 2;
  } else {
    return 0;
  }
}

bool operandFlag(string c) {
	if(c.length() == 1) {
		if((c >= "0" && c <= "9") || (c >= "A" && c <= "Z") || (c >= "A" && c <= "Z")) {
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

bool operatorFlag(string c) {
  if(c == "+" || c == "-" || c == "*" || c == "/") {
    return true;
  } else {
    return false;
  }
}


bool foundDoubleSpace(char l, char r) { 
	if((l == r) && (l == ' ')) {
		return true;
	} else {
		return false;
	}
}

bool validExpression(int whitespace, vector<string> expression) {
	int spaces = 0;
	int operators = 0;
	int operands = 0;
	int parentheses = 0;
	
	if(whitespace == 0) {
		spaces = -1;
	}
	
	// count elements of expression
	for(string &s : expression) {
		if(s == " ") {
			++spaces;
		} else if (operandFlag(s)) {
			++operands;
		} else if (operatorFlag(s)) {
			++operators;
		} else if (s == "(" || s == ")" || s == "[" || s == "]") {
			++parentheses;
		}
	}
	
	// if incorrect number of spaces for expression
	if(spaces != 0) {
		if(!(spaces == (operators + operands + parentheses - 1))) {
			return false;
		}
	} else {
		return false;
	}
		 
	// if incorrect number of parantheses
	if (!(parentheses%2 == 0)) {
		cout << "Error: Mismatched parantheses" << endl;
		return false;
	}
	
	// if incorrect number of operands
	if(operands != 0) {
		if(operators != 0) {
			if(!(operands == (operators + 1))) {
				cout << "Error: Missing operand" << endl;
				return false;
			}
		} else {
			cout << "Error: Missing operator" << endl;
			return false;
		}
	} else {
		cout << "Error: Missing operand" << endl;
		return false;
	}
		
	// if incorrect number of operators
	if(operators != 0) {
		if (!(operators == (operands - 1))) {
			cout << "Error: Missing operator" << endl;
			return false;
		}
	} else {
		cout << "Error: Missing operator" << endl;
		return false;
	}
	
	return true;
}

float evaluateExpression(vector<string> expression) {
	Stack<string> operation;
	
	// loop through expression
	for(vector<string>::iterator itr = expression.begin(); itr != expression.end(); ++itr) {
// 		cout << *itr << endl;
		if(*itr == " ") {
			// ignore whitespace
		} else if (operandFlag(*itr)) {
			// push operands
			operation.push(*itr);
		} else {
			// get operands
			float rhs = stof(operation.top());
			operation.pop();
			float lhs = stof(operation.top());
			operation.pop();
			
			// perform operation
			if(*itr == "+") {
				operation.push(to_string(lhs + rhs)); 
			} else if (*itr == "-") {
				operation.push(to_string(lhs - rhs)); 
			} else if (*itr == "*") {
				operation.push(to_string(lhs * rhs)); 
			} else if (*itr == "/") {
				operation.push(to_string(rhs / lhs));
			}
		}
	}
	
	return stof(operation.top());
}