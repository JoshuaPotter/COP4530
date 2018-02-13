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
bool List<T>::const_iterator::operator==(const List<T>::const_iterator &rhs) const { 
  return current == rhs.current;
}

// not equals to comparison operator overload
template <typename T>
bool List<T>::const_iterator::operator!=(const List<T>::const_iterator &rhs) const { 
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
// template <typename T>
// void List<T>::remove(const T &val) {
  
// }

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

// remove all elements with value = val
template <typename T>
void List<T>::remove(const T &val) {
  for(List<T>::iterator i = begin(); i != end(); ++i) {
    if(i.current->data == val) {
      erase(i);
    }
  }
}

// remove all elements with value = val
// template <typename T>
// void List<T>::print(std::ostream& os, char ofc = ' ') const {
  
// } 

// iterator to first element
template <typename T>
typename List<T>::iterator List<T>::begin() {
  return { head->next };
}

// iterator to first element
template <typename T>
typename List<T>::const_iterator List<T>::begin() const {
  return { head->next };
}

// end marker iterator
template <typename T>
typename List<T>::iterator List<T>::end() {
  return { tail };
}

// end marker iterator
template <typename T>
typename List<T>::const_iterator List<T>::end() const {
  return { tail };
}

// insert val ahead of itr
template <typename T>
typename List<T>::iterator List<T>::insert(List<T>::iterator itr, const T& val) {
  Node *p = itr.current;
  theSize++;
  return { p->prev = p->prev->next = new Node{ val, p->prev, p } };
}

// move version of insert
template <typename T>
typename List<T>::iterator List<T>::insert(List<T>::iterator itr, T && val) {
  Node *p = itr.current;
  theSize++;
  return { p->prev = p->prev->next = new Node{ std::move(val), p->prev, p } };
}

// erase one element
template <typename T>
typename List<T>::iterator List<T>::erase(List<T>::iterator itr) {
  Node *p = itr.current;
  iterator retVal{ p->next };
  p->prev->next = p->next;
  p->next->prev = p->prev;
  delete p;
  theSize--;
  
  return retVal;
}

// erase one element
template <typename T>
typename List<T>::iterator List<T>::erase(List<T>::iterator start, List<T>::iterator end) {
  for(List<T>::iterator i = start; i != end;) {
    i = erase(i);
  }
  return end;
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

// overload comparison operator
template <typename T>
bool operator==(const List<T> & lhs, const List<T> &rhs) {
  if(lhs.size() == rhs.size()) {
    for(auto i = lhs.begin(); i != lhs.end(); ++i) {
      for (auto j = rhs.begin(); i != rhs.end(); ++i) {
        if(*i != *j) {
          return false;
        }
      }
    }
    return true;
  } else {
    return false;
  }
}

// overload not comparison operator
template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs) {
  if(lhs == rhs) {
    return false;
  } else {
    return true;
  }
}