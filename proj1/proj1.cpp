#include <iostream>
#include<string>
#include <map>

using namespace std;

void insertCharacter(map<char,int> &characters, char character) {
// 	cout << "Character: " << character << endl;
	map<char,int>::iterator itr;
	itr = characters.find(character);
	if(itr == characters.end()) {
		// add to characters map if not in vector
		characters.insert({character, 1});
	} else {
		// if character already exists in vector, update frequency
		itr->second = (itr->second + 1);
	}
}

void insertNumber(map<string,int> &numbers, string &number) {
// 	cout << "Number: " << number << endl;
	map<string,int>::iterator itr;
	itr = numbers.find(number);
	if(itr == numbers.end()) {
		// add to characters map if not in vector
		numbers.insert({number, 1});
	} else {
		// if character already exists in vector, update frequency
		itr->second = (itr->second + 1);
	}
	number.clear();
}

void insertWord(map<string,int> &words, string &word) {
// 	cout << "Word: " << word << endl;
	map<string,int>::iterator itr;
	itr = words.find(word);
	if(itr == words.end()) {
		// add to characters map if not in vector
		words.insert({word, 1});
	} else {
		// if character already exists in vector, update frequency
		itr->second = (itr->second + 1);
	}
	word.clear();
}

int main() {
	string input;
	string word;
	char prevChar = '\0';
	int charNum = 1;
	
	map<string,int> words;
	map<string,int> numbers;
	map<char,int> characters;
	
	// get user input
	while(getline(cin,input)) {
		// get character from input unless no characters left to retrieve
		for (char c : input) {
			// store character in lowercase for comparisons
			char lower = tolower(c);
			
			// check if this is the first character
			if(prevChar != '\0') {
				// check if character is a digit or letter or symbol
				if(c >= '0' && c <= '9') {
					// character is a digit
					
					// check if previous character was not digit
					if(prevChar >= 'a' && prevChar <= 'z') {
						// put word in words map
						insertWord(words, word);
					}
					
					// add character to characters map
					insertCharacter(characters, c);
					// add letter to temporary word storage
					word.push_back(c);
				} 
				else if (lower >= 'a' && lower <= 'z') {
					// character is a letter
					
					// check if previous character was a digit
					if(prevChar >= '0' && prevChar <= '9') {
						// put number in numbers map
						insertNumber(numbers, word);
					}
					
					// add character to character map
					insertCharacter(characters, c);
					// add letter to temporary word storage
					word.push_back(lower);
				} 
				else {
					// non-digit and non-letter character
					if((prevChar >= '0' && prevChar <= '9')||(prevChar >= 'a' && prevChar <= 'z')) {
						// previous character is alphanumeric, test for digit or letter
						if(c >= '0' && c <= '9') {
							// character is a digit

							// check if previous character was not digit
							if(prevChar >= 'a' && prevChar <= 'z') {
								// add word to words map
								insertWord(words, word);
							}

							word.push_back(c);
						} else if (lower >= 'a' && lower <= 'z') {
							// character is a letter

							// check if previous character was a digit
							if(prevChar >= '0' && prevChar <= '9') {
								// put number in numbers map
								insertNumber(numbers, word);
							}

							word.push_back(lower);
						} else {
							// character is not alphanumeric
							if(prevChar >= 'a' && prevChar <= 'z') {
								// add word to words map
								insertWord(words, word);
							} else if (prevChar >= '0' && prevChar <= '9') {
								// insert number to numbers map
								insertNumber(numbers, word);
							}
						}
					}
					// add character to characters map
					insertCharacter(characters, c);
				}
			} else {
				if(c >= '0' && c <= '9') {
					// push to word stack
					word.push_back(c);
				} else if (lower >= 'a' && lower <= 'z') {
					// push to word stack
					word.push_back(lower);
				}
				
				// add to characters map
				insertCharacter(characters, c);
			}
			
			// iterate number of character
			charNum++;
			prevChar = lower;
			
			if(charNum % 150000 == 0) {
				cout << "Sorting input. Please wait." << endl;
			}
		}
		
		// add last word
		if(prevChar >= '0' && prevChar <= '9') {
			insertNumber(numbers, word);
		} else if (prevChar >= 'a' && prevChar <= 'z') {
			insertWord(words, word);
		}
	}
	
	cout << endl << "Characters" << endl;
	for(auto result : characters) {
		cout << result.first << " => " << result.second << endl;
	}
	cout << endl;
	
	cout << "Numbers" << endl;
	for(auto result : numbers) {
		cout << result.first << " => " << result.second << endl;
	}
	cout << endl;
	
	cout << "Words" << endl;
	for(auto result : words) {
		cout << result.first << " => " << result.second << endl;
	}
	cout << endl;
	
	return 0;
}