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
	char menuFunction;
	
	// get size of hashtable
	cout << "Enter preferred hash table capacity: ";
	cin >> psSize;
	cout << psSize << endl;
	
	// initialize password server object with desired size
	PassServer ps(psSize);
	
  // show menu and ask for character to corresponding function
  do {
		Menu();
		while(showMenu && cin.get(menuFunction)) {
			switch(menuFunction) {
				case 'l': {
					string loadFile;
          
					cout << "Enter password file name to load from: ";
					cin >> loadFile;
          
					if(!ps.load(loadFile.c_str())) {
						cout << endl << "Error: Cannot open file " << loadFile << endl;
					}
          
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
						cout << endl << "*****Error: User " << username << " could not be added." << endl;
					} else {
						cout << endl << "User " << username << " added." << endl;
					}
          
					break;
				}
				case 'r': {
					string username;
					
					cout << "Enter username: ";
					cin >> username;
					
					if(!ps.removeUser(username)) {
						cout << endl << "*****Error: User not found. Could not delete user" << endl;
					} else {
						cout << endl << "User " << username << " deleted." << endl;
					}
          
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
						cout << endl << "*****Error: Could not change user password" << endl;
					} else {
						cout << endl << "Password changed for user " << username << endl;
					}
          
					break;
				}
				case 'f': {
					string username;
					
					cout << "Enter username: ";
					cin >> username;
					
					if(!ps.find(username)) {
						cout << endl << "User '" << username << "' not found." << endl;
					} else {
						cout << endl << "User '" << username << "' found." << endl;
					}
          
					break;
				}
				case 'd': {
					ps.dump();
					cout << endl;
          
					break;
				}
				case 's': {
					cout << endl << "Size of hashtable: " << ps.size() << endl;
          
					break;
				}
				case 'w': {
					string writeFile;
					
					cout << "Enter password file name to write to: ";
					cin >> writeFile;
					
					if(!ps.write_to_file(writeFile.c_str())) {
						cout << endl << "*****Error: Could not write to file " << writeFile << endl;
					}
          
					break;
				}
				case 'x': {
					showMenu = false;
					break;
				}
			}
      
			if(showMenu) {
				Menu();
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
