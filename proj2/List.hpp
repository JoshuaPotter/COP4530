/*
  Name: Joshua Potter (jop13)
  Class: COP4530
  Assignment 2 - List.hpp
*/

#include "List.h"

/*
   
   Nested const_iterator class definitions

*/

// initialization
template <typename T>
List<T>::const_iterator::const_iterator() : current { nullptr } { }


// const * operator overload
template <typename T>
const T & List<T>::const_iterator::operator*() const { 
  return retrieve();
}

// post-increment overload
template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator++() { 
  current = current->next;
  return *this;
}

// pre-increment overload
template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int) { 
  List<T>::const_iterator old = *this;
  ++(*this);
  return old;
}

// post-decrement overload
template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--() { 
  current = current->prev;
  return *this;
}

// pre-decrement overload
template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int) { 
  List<T>::const_iterator old = *this;
  --(*this);
  return old;
}

// equals to comparison operator overload
template <typename T>
bool List<T>::const_iterator::operator==(const List<T>::const_iterator & rhs) const { 
  return current == rhs.current;
}

// not equals to comparison operator overload
template <typename T>
bool List<T>::const_iterator::operator!=(const List<T>::const_iterator & rhs) const { 
  return !(*this == rhs);
}

// turn data value of node
template <typename T>
T & List<T>::const_iterator::retrieve() const {
  return current->data;
}

// go to node at position p
template <typename T>
List<T>::const_iterator::const_iterator(Node *p) : current { p } { }

/*
  
  Nested iterator class definitions

*/

// initialization
template <typename T>
List<T>::iterator::iterator() { }

// * operator overload
template <typename T>
T & List<T>::iterator::operator*() {
  return List<T>::const_iterator::retrieve();
}

// const * operator overload
template <typename T>
const T & List<T>::iterator::operator*() const {
  return List<T>::const_iterator::operator*();
}

// pre-increment overload
template <typename T>
typename List<T>::iterator & List<T>::iterator::operator++() {
  this->current = this->current->next;
  return *this;
}

// post-increment overload
template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int) {
  List<T>::iterator old = *this;
  ++(*this);
  return old;
}

// pre-decrement overload
template <typename T>
typename List<T>::iterator & List<T>::iterator::operator--() {
  this->current = this->current->prev;
  return *this;
}

// post-decrement overload
template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int) {
  List<T>::iterator old = *this;
  --(*this);
  return old;
}

template <typename T>
List<T>::iterator::iterator(Node *p) : List<T>::const_iterator::const_iterator { p } { }