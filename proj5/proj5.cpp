/*
  Name: Joshua Potter (jop13)
  Class: COP4530
  Assignment 5 - proj5.cpp
*/

#include "passserver.h"

#include <iostream>

using namespace cop4530;
using namespace std;

/*

	Function Declarations

*/

void Menu();

int main() {
	bool showMenu = true;
	size_t psSize;
	char c;
	
	// get size of hashtable
	cout << "Enter preferred hash table capacity: ";
	cin >> psSize;
	cout << psSize << endl;
	
	// initialize password server object with desired size
	PassServer ps(psSize);
	
  do {
		Menu();
		while(showMenu && cin.get(c)) {
			switch(c) {
				case 'l': {
					string loadFile;
					cout << "Enter password file name to load from: ";
					cin >> loadFile;
					if(!ps.load(loadFile.c_str())) {
						cout << "Error: Cannot open file " << loadFile << endl << endl;
					}
					Menu();
					break;
				}
				case 'a': {
					string username;
					string password;
					
					cout << "Enter username: ";
					cin >> username;
					cout << "Enter password: ";
					cin >> password;
					
					if(!ps.addUser(make_pair(username, password))) {
						cout << "*****Error: User " << username << " could not be added." << endl << endl;
					} else {
						cout << "User " << username << " added." << endl << endl;
					}
					Menu();
					break;
				}
				case 'r': {
					string username;
					
					cout << "Enter username: ";
					cin >> username;
					
					if(!ps.removeUser(username)) {
						cout << "*****Error: User " << username << " could not be removed." << endl << endl;
					} else {
						cout << "User " << username << " deleted." << endl << endl;
					}
					Menu();
					break;
				}
				case 'c': {
					string username;
					string password;
					string newPassword;
					
					cout << "Enter username: ";
					cin >> username;
					cout << "Enter password: ";
					cin >> password;
					cout << "Enter new password: ";
					cin >> newPassword;
					
					if(!ps.changePassword(make_pair(username, password), newPassword)) {
						cout << "*****Error: Could not change user password" << endl << endl;
					} else {
						cout << "Password changed for user " << username << endl << endl;
					}
					Menu();
					break;
				}
				case 'f': {
					string username;
					
					cout << "Enter username: ";
					cin >> username;
					
					if(!ps.find(username)) {
						cout << "*****Error: User '" << username << "' not found." << endl << endl;
					} else {
						cout << "User '" << username << "' found." << endl << endl;
					}
					Menu();
					break;
				}
				case 'd': {
					ps.dump();
					cout << endl;
					Menu();
					break;
				}
				case 's': {
					cout << "Size of hashtable: " << ps.size() << endl << endl;
					Menu();
					break;
				}
				case 'w': {
					string writeFile;
					
					cout << "Enter password file name to write to: ";
					cin >> writeFile;
					
					if(!ps.write_to_file(writeFile.c_str())) {
						cout << "*****Error: Could not write to file " << writeFile << endl << endl;
					}
					Menu();
					break;
				}
				case 'x': {
					showMenu = false;
					break;
				}
			}
		}
	} while(showMenu);
	
	return 0;
}

/*

	Function Definitions

*/

void Menu()
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}
