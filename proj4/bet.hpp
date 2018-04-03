  /*
  Name: Joshua Potter (jop13)
  Class: COP4530
  Assignment 4 - bet.hpp
*/

#include "bet.h"
#include <iostream>
#include <stack>
#include <sstream>

using namespace std;

// default zero-parameter constructor
BET::BET() : root { nullptr } { }

// one-parameter constructor
BET::BET(const string postfix) : root { nullptr } {
  buildFromPostfix(postfix);
}

// copy constructor
BET::BET(const BET& bet) : root { nullptr } {
  root = clone(bet.root);
} 

// destructor
BET::~BET() {
  makeEmpty(root);
}

// constructs a binary expression tree from string parameter
bool BET::buildFromPostfix(const string postfix) {
  istringstream iss(postfix);
  stack<BinaryNode*> s;
  string token;
  
  // if tree from root is not empty, make empty
  if(!empty()) {
    makeEmpty(root);
  }
  
  // traverse expression word by word
  while(iss >> token) {
    BinaryNode *t1, *t2;
    BinaryNode *n = new BinaryNode(token, nullptr, nullptr);
    
    if(isOperand(token)) {
      // token is an operand, push it to the stack 
      s.push(n);
    } else if(isOperator(token)) {
      // token is an operator
      
      // if we don't have 2 operands, then input is invalid
      if(s.size() < 2) {
        cout << "Wrong postfix expression" << endl;
        return false;
      }
      
      // get 2 operands from stack
      t1 = s.top();
      s.pop();
      t2 = s.top();
      s.pop();
      
      // set the children to operands from stack
      n->right = t1;
      n->left = t2;
      
      // push the operator, with operand children, to stack
      s.push(n);
    }
  }
    
  // if we don't have one operator left, then input is invalid
  if(s.size() != 1) {
    cout << "Wrong postfix expression" << endl;
    return false;
  }

  // grab final operator, set as root, remove from stack
  root = s.top();
  s.pop();
    
  // tree has been constructed
  return true;
}

// assignment operator
const BET & BET::operator= (const BET & bet) {
  // clone a tree based on its root node and return the clone
  root = bet.clone(bet.root);
  return *this;
}

// call private version
void BET::printInfixExpression() {
  printInfixExpression(root);
  cout << endl;
}

// call private version
void BET::printPostfixExpression() {
  printPostfixExpression(root);
  cout << endl;
}

// call private version
size_t BET::size() {
  return size(root);
}

// call private version
size_t BET::leaf_nodes() {
  return leaf_nodes(root);
}

// return true if tree is empty
bool BET::empty() {
  return (root == nullptr);
}

// checks if string parameter is one of specified operators
bool BET::isOperator(const string & exp) {
  if(exp == "+" || exp== "-" || exp == "*" || exp == "/") {
    return true;
  } else {
    return false;
  }
}

// checks if string parameter is alphanumeric
bool BET::isOperand(const string & exp) {
  if((exp >= "A" && exp <= "Z") || (exp >= "a" && exp <= "z") || (exp >= "0" && exp <= "9")) {
    return true;
  } else {
    return false;
  }
}

// print infix expression by traversing tree in-rder
void BET::printInfixExpression(BinaryNode *n) {
  // check if node element is operator or operand
  if(isOperator(n->element)) {
    // if operator, check for related expression, otherwise print operator
    if(n->left != nullptr) {
      // left child exists
      if(isOperator(n->left->element)) {
        // if left child is an operator, then print its subexpression
        cout << "( ";
        printInfixExpression(n->left);
        cout << ") ";
      } else if (isOperand(n->left->element)) {
        // if left child is operand, print its expression
        printInfixExpression(n->left);
      }
      
      // print operator
      cout << n->element << " ";
      
      // right child exists
      if(isOperator(n->right->element)) {
        // if right child is an operator, print its subexpression
        cout << "( ";
        printInfixExpression(n->right);
        cout << ") ";
      } else if (isOperand(n->right->element)) {
        // if right child is operand, print its expression
        printInfixExpression(n->right);
      }
    }
  } else if (isOperand(n->element)) {
    // print operand
    cout << n->element << " ";
  }
}

void BET::makeEmpty(BinaryNode* &t) {
  // empty children, then delete node
  if(t != nullptr) {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }
}

BET::BinaryNode * BET::clone(BinaryNode *t) const {
  // clone if element and children isn't empty
  if(t == nullptr) {
    return nullptr;
  } else {
    return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
  }
}

void BET::printPostfixExpression(BinaryNode *n) {
  // recursively print node and children if root node exists
  if(n != nullptr) {
    printPostfixExpression(n->left);
    printPostfixExpression(n->right);
    cout << n->element << " ";
  }
}

size_t BET::size(BinaryNode *t) {
  // return size recursively or 0 if empty
  if(t != nullptr) {
    return size(t->left) + size(t->right) + 1;
  } else {
    return 0;
  }
}

size_t BET::leaf_nodes(BinaryNode *t) {
  if (t->left == nullptr && t->right == nullptr) {
    // if left and right children are nullptr, we have reached leaf node
    return 1;
  } else {
    return leaf_nodes(t->left) + leaf_nodes(t->right);
  }
}