/*
  Name: Joshua Potter (jop13)
  Class: COP4530
  Assignment 2 - List.hpp
*/

#include "List.h"

/*
   
   Nested const_iterator class definitions

*/

// constructor
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

// constructor
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

// go to node at position p 
template <typename T>
List<T>::iterator::iterator(Node *p) : List<T>::const_iterator::const_iterator { p } { }

/*
  
  List class definitions
  
*/

// default constructor
template <typename T>
List<T>::List() {
  init();
}

// copy constructor
template <typename T>
List<T>::List(const List<T> & rhs) {
  init();
  for(auto & x : rhs) {
    push_back(x);
  }
}

// move constructor
template <typename T>
List<T>::List(List<T> && rhs) : theSize { rhs.theSize }, head { rhs.head }, tail { rhs.tail } {
  rhs.theSize = 0;
  rhs.head = nullptr;
  rhs.tail = nullptr;
}

// list with num elements with value val
template <typename T>
List<T>::List(int num, const T& val) {
  init();
  for(int i = 0; i < num; ++i) {
    push_back(val);
  }
}

// constructs with elements [start, end)
template <typename T>
List<T>::List(List<T>::const_iterator start, List<T>::const_iterator end) {
  init();
  while (start != end) {
    start++;
    push_back(start.current->data);
  }
}

// destructor
template <typename T>
List<T>::~List() {
  clear();
  delete head;
  delete tail;
}

// assignment operator overload
template <typename T>
const List<T>& List<T>::List::operator=(const List<T> &rhs) {
  List<T> copy = rhs;
  std::swap(*this, copy);
  return *this;
}

// assignment operator overload
template <typename T>
List<T> & List<T>::List::operator=(List<T> && rhs) {
  std::swap(theSize, rhs.theSize);
  std::swap(head, rhs.head);
  std::swap(tail, rhs.tail);
  
  return *this;
}

// number of elements
template <typename T>
int List<T>::size() const {
  return theSize;
}

// check if list is empty
template <typename T>
bool List<T>::empty() const {
  return size() == 0;
}

// delete all elements
template <typename T>
void List<T>::clear() {
  while(!empty()) {
    pop_front();
  }
}

// reverse the order of the elements


// reference to the first element
template <typename T>
T &List<T>::front() {
  return *begin();
}

// reference to the first element
template <typename T>
const T& List<T>::front() const {
  return *begin();
}

// reference to the last element
template <typename T>
T &List<T>::back() {
  return *--end();
}

// reference to the last element
template <typename T>
const T & List<T>::back() const {
  return *--end();
}

// insert to the beginning
template <typename T>
void List<T>::push_front(const T & val) { 
  insert(begin(), val); 
}

// move version to insert
template <typename T>
void List<T>::push_front(T && val) { 
  insert(begin(), std::move(val)); 
}

// insert to end
template <typename T>
void List<T>::push_back(const T & val) { 
  insert(end(), val); 
}

// move version of insert
template <typename T>
void List<T>::push_back(T && val) { 
  insert(end(), std::move(val)); 
}

// delete first element
template <typename T>
void List<T>::pop_front() { 
  erase(begin()); 
}

// delete last element
template <typename T>
void List<T>::pop_back() {
  erase(--end()); 
}

// create new node in list
template <typename T>
void List<T>::init() {
  theSize = 0;
  head = new Node;
  tail = new Node;
  head->next = tail;
  tail->prev = head;
}