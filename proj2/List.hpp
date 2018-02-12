#include "List.h"

// nested const_iterator class definitions
template <typename T>
List<T>::const_iterator::const_iterator() : current { nullptr } { }

template <typename T>
const T & List<T>::const_iterator::operator*() const { 
  return retrieve();
}

template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator++() { 
  current = current->next;
  return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int) { 
  List<T>::const_iterator old = *this;
  ++(*this);
  return old;
}

template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--() { 
  current = current->prev;
  return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int) { 
  List<T>::const_iterator old = *this;
  --(*this);
  return old;
}

template <typename T>
bool List<T>::const_iterator::operator==(const List<T>::const_iterator & rhs) const { 
  return current == rhs.current;
}

template <typename T>
bool List<T>::const_iterator::operator!=(const List<T>::const_iterator & rhs) const { 
  return !(*this == rhs);
}

template <typename T>
T & List<T>::const_iterator::retrieve() const {
  return current->data;
}

template <typename T>
List<T>::const_iterator::const_iterator(Node *p) : current { p } { }

// nested iterator class definitions
template <typename T>
List<T>::iterator::iterator() { }

template <typename T>
T & List<T>::iterator::operator*() {
  return List<T>::const_iterator::retrieve();
}

template <typename T>
const T & List<T>::iterator::operator*() const {
  return List<T>::const_iterator::operator*();
}

template <typename T>
typename List<T>::iterator & List<T>::iterator::operator++() {
  this->current = this->current->next;
  return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int) {
  List<T>::iterator old = *this;
  ++(*this);
  return old;
}

template <typename T>
typename List<T>::iterator & List<T>::iterator::operator--() {
  this->current = this->current->prev;
  return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int) {
  List<T>::iterator old = *this;
  --(*this);
  return old;
}

template <typename T>
List<T>::iterator::iterator(Node *p) : List<T>::const_iterator::const_iterator { p } { }