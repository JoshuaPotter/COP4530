/*
  Name: Joshua Potter (jop13)
  Class: COP4530
  Assignment 3 - stack.h
*/

#ifndef DL_STACK_H
#define DL_STACK_H
#include <iostream>
#include <vector>

namespace cop4530 {

	template <typename T>
  class Stack {
    public:
      Stack(); // zero-argument constructor
      ~Stack(); // destructor
      Stack (const Stack<T>&); // copy constructor
      Stack(Stack<T> &&); // move constructor
    
      Stack<T>& operator= (const Stack <T>&); //copy assignment operator=
      Stack<T> & operator=(Stack<T> &&); //move assignment operator=
    
      bool empty() const; // returns true if Stack contains no element
      void clear(); // delete all elements from Stack
      void push(const T& x); // add x to Stack. copy version
      void push(T && x); // add x to Stack. move version
      void pop(); // removes and discards most recently added element to Stack
      T& top(); // mutator that returns a reference to recently added element
      const T& top() const; // accessor that returns most recently added element
      int size() const; // returns number of elements stored in Stack.
    
      void print(std::ostream& os, char ofc = ' ') const; // print elements of stack in reverse order to ostream os with char ofc as deliminator
    
    private:
      std::vector<T> container; // container of data

  };

	// outstream overload
	template <typename T>
    std::ostream& operator<< (std::ostream& os, const Stack<T>& a); // invokes print() for Stack<T> a to ostream
  
	// comparison operator overloads
  template <typename T>
    bool operator== (const Stack<T>&, const Stack <T>&); // returns true if two compared stacks have same elements in same order
  
  template <typename T>
    bool operator!= (const Stack<T>&, const Stack <T>&); // opposite of operator==()
  
  template <typename T>
    bool operator<=(const Stack<T>& a, const Stack <T>& b); // returns true if every element in Stack a is smaller than or equal to element in Stack b
  
	// include the implementation file here
	#include "stack.hpp"

} // end of namespace 4530

#endif