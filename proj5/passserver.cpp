/*
  Name: Joshua Potter (jop13)
  Class: COP4530
  Assignment 5 - passserver.cpp
*/

#include "passserver.h"
#include <crypt.h>
#include <cstring>
#include <unistd.h>

using namespace std;
using namespace cop4530;

// pass size from PassServer to HashTable
PassServer::PassServer(size_t size = 101) {
  HashTable<string, string> ht(size);
}

PassServer::~PassServer() {
  
}

// load password file into HashTable
bool PassServer::load(const char *filename) {
  return HashTable<string, string>::load(filename);
}

// add username and encrypted password
bool PassServer::addUser(pair<string,  string> & kv) {
  return HashTable<string, string>::insert(make_pair(kv.first, encrypt(kv.second)));
}

// move version of addUser
bool PassServer::addUser(pair<string, string> && kv) {
  return HashTable<string, string>::insert(make_pair(kv.first, encrypt(kv.second)));
}

// delete existing user with key k
bool PassServer::removeUser(const string & k) {
  return HashTable<string, string>::remove(k);
}

// change existing user's password
bool PassServer::changePassword(const pair<string, string> &p, const string & newpassword) {
  
}

// check if user exists
bool PassServer::find(const string & user) {
  return HashTable<string, string>::contains(user);
}

// dump HashTable
void PassServer::dump() {
  HashTable<string, string>::dump();
}

// return HashTable size
size_t PassServer::size() {
  return HashTable<string, string>::size();
}

// save username nad password combo to file
bool PassServer::write_to_file(const char *filename) {
  return HashTable<string, string>::write_to_file(filename);
}

string PassServer::encrypt(const string & str) {
  char salt[] = "$1$########";
  char * password = new char [100];
  
  strcpy ( password, crypt(key.c_str(), salt));
  string encryptedPassword = password;
  
  // return only last 22 characters
  return encryptedPassword.substr(12, 34);
}