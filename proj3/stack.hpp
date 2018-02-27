/*
  Name: Joshua Potter (jop13)
  Class: COP4530
  Assignment 3 - stack.hpp
*/

#include "stack.h"

// zero-argument constructor
template <typename T>
Stack<T>::Stack() {}

// destructor
template <typename T>
Stack<T>::~Stack() {
  clear();
}

// copy constructor
template <typename T>
Stack<T>::Stack (const Stack<T>& rhs) {
  for(auto & x : rhs.container) {
    push(x);
  }
}

// move constructor
template <typename T>
Stack<T>::Stack(Stack<T> && rhs) :  container { rhs.container } {
  rhs.clear();
}

// copy assignment operator overload
template <typename T>
Stack<T>& Stack<T>::Stack::operator= (const Stack <T>& rhs) {
  Stack<T> copy = rhs;
  std::swap(*this, copy);
  
  return *this;
}

// move assignment operator overload
template <typename T>
Stack<T> & Stack<T>::Stack::operator=(Stack<T> && rhs) {
  std::swap(container, rhs.container);
  
  return *this;
}

// returns true if Stack contains no element
template <typename T>
bool Stack<T>::empty() const {
  return container.empty();
}

// delete all elements from Stack
template <typename T>
void Stack<T>::clear() {
  return container.clear();
}

// add x to stack, copy version
template <typename T>
void Stack<T>::push(const T& x) {
  container.push_back(x);
}

// add x to stack, move version
template <typename T>
void Stack<T>::push(T && x) {
  container.push_back(std::move(x));
}

// removes and discards most recently added element to stack
template <typename T>
void Stack<T>::pop() {
  container.pop_back();
}

// mutator that returns reference to recently added element
template <typename T>
T& Stack<T>::top() {
  return container.back();
}

// accessor that returns most recently added element
template <typename T>
const T& Stack<T>::top() const {
  return container.back();
}

// returns number of elements stored in stack
template <typename T>
int Stack<T>::size() const {
  return container.size();
}

// prints elements of stack in reverse order into ostream os with char ofc as deliminator
template <typename T>
void Stack<T>::print(std::ostream& os, char ofc) const {
  for(int i = 0; i != container.size(); ++i) {
    os << container[i] << ofc;
  }
}

// outstream overload
// invokes print() for Stack<T> a to ostream
template <typename T>
std::ostream& operator<< (std::ostream& os, const Stack<T>& a) {
  a.print(os);
  return(os);
}

// == operator overload
// returns true if two compared stacks have same elements in same order
template <typename T>
bool operator== (const Stack<T>& lhs, const Stack <T>& rhs) {
  Stack<T> lhsCopy = lhs;
  Stack<T> rhsCopy = rhs;
  if(lhsCopy.size() == rhsCopy.size()) {
    do {
      if(lhsCopy.top() != rhsCopy.top()) {
        return false;
      }
      lhsCopy.pop();
      rhsCopy.pop();
    } while (!lhsCopy.empty());
    return true;
  } else {
    return false;
  }
}

// != operator overload
// opposite of operator==
template <typename T>
bool operator!= (const Stack<T>& lhs, const Stack <T>& rhs) {
  return !(lhs == rhs);
}

// <= operator overload
// returns true if every element in Stack a is smaller than or equal to element in Stack b.
template <typename T>
bool operator<=(const Stack<T>& a, const Stack <T>& b) {
  if(a == b) {
    return true;
  } else {
    Stack<T> aCopy = a;
    Stack<T> bCopy = b;
    if(aCopy.size() > bCopy.size()) {
      return false;
    } else {
      do {
        if(aCopy.top() > bCopy.top()) {
          return false;
        }
        aCopy.pop();
        bCopy.pop();
      } while (!aCopy.empty() && !bCopy.empty());
    }
  }
  return true;
}
