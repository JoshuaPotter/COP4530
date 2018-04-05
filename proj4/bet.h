/*
  Name: Joshua Potter (jop13)
  Class: COP4530
  Assignment 4 - bet.h
*/

#ifndef BET_H
#define BET_H
#include <string>

using namespace std;

class BET {
  
  public:
    BET(); // default zero-parameter constructor
    BET(const string postfix); // one-parameter constructor
    BET(const BET&); // copy constructor
    ~BET(); // destructor
  
    bool buildFromPostfix(const string postfix); // parameter postfix is string containing postfix expression
    const BET & operator= (const BET &); // assignment operator
    
    void printInfixExpression(); // call private version 
    void printPostfixExpression(); // call private version
    size_t size(); // call private version
    size_t leaf_nodes(); // call private version
    bool empty(); // return true if tree is empty
    bool isOperator(const string & exp); // checks if string character is operator
    bool isOperand(const string & exp); // checks if string character is operand
  
  private:
    struct BinaryNode {
      string element;
      BinaryNode *left;
      BinaryNode *right;
      
      BinaryNode (const string & theElement, BinaryNode *lt, BinaryNode *rt)
        : element{ theElement }, left{ lt }, right{ rt } { }
      
      BinaryNode (string && theElement, BinaryNode *lt, BinaryNode *rt)
        : element{ move(theElement) }, left{ lt }, right{ rt } { }
    };
  
    BinaryNode *root; // Root Node
    
    void printInfixExpression(BinaryNode *n); // print infix expression
    void makeEmpty(BinaryNode* &t); // delete all nodes pointed to by object t
    BinaryNode * clone(BinaryNode *t) const; // clone all nodes in subtree pointed to by object to
    void printPostfixExpression(BinaryNode *n); // print postfix expression
    size_t size(BinaryNode *t); // return number of nodes pointed to by object t
    size_t leaf_nodes(BinaryNode *t); // return number of leaf nodes in subtree pointed to by object t
  
};

#include "bet.hpp"

#endif