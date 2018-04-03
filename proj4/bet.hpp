/*
  Name: Joshua Potter (jop13)
  Class: COP4530
  Assignment 4 - bet.hpp
*/

#include "bet.h"

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

bool BET::buildFromPostfix(const string postfix) {
  
}

const BET & BET::operator= (const BET & bet) {
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

void BET::printInfixExpression(BinaryNode *n) {
  
}

void BET::makeEmpty(BinaryNode* &t) {
  if(t != nullptr) {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }
  t = nullptr;
}

BET::BinaryNode * BET::clone(BinaryNode *t) const {
  if(t == nullptr) {
    return nullptr;
  } else {
    return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
  }
}

void BET::printPostfixExpression(BinaryNode *n) {
  
}

size_t BET::size(BinaryNode *t) {
  if(t == nullptr) {
    return 0;
  } else {
    return 1 + size(t->left) + size(t->right);
  }
}

size_t BET::leaf_nodes(BinaryNode *t) {
  if(t == nullptr) {
    return 0;
  } else {
    return size(t->left) + size(t->right);
  }
}