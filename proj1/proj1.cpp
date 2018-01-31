#include <iostream>
#include <string>
#include <map>

using namespace std;

void insertCharacter(map<char,int> &characters, char character);

void insertNumber(map<string,int> &numbers, string &number);

void insertWord(map<string,int> &words, string &word);

int main() {
	char prevChar = '\0';
// 	int charNum = 1;
	string input;
	string word;
	map<string,int> words;
	map<string,int> numbers;
	map<char,int> characters;
	
	// get user input
	while(getline(cin,input)) {
		cout << "Input line: " << input << endl;
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
				}
			} else {
				if(c >= '0' && c <= '9') {
					// push to word stack
					word.push_back(c);
				} else if (lower >= 'a' && lower <= 'z') {
					// push to word stack
					word.push_back(lower);
				}
			}
			// add to characters map
			insertCharacter(characters, c);
			
			// iterate character count
// 			++charNum;
			prevChar = lower;
			
// 			if(charNum % 150000 == 0) {
// 				cout << "Sorting input. Please wait." << endl;
// 			}
		}
			
		// add newline since getline discards \n
		if (!cin.eof()) {
			insertCharacter(characters, '\n');
		}

		// add last word
		if(prevChar >= '0' && prevChar <= '9') {
			insertNumber(numbers, word);
		} else if (prevChar >= 'a' && prevChar <= 'z') {
			insertWord(words, word);
		}
		
		// iterate line
		++lineNum;
	}
	
	// print characters
	if (characters.size() > 0) {
		cout << "Total " << characters.size() << " characters:" << endl;
		for(auto result : characters) {
			// format escaped characters
			if (result.first == '\\') {
				cout << "'\\' => " << result.second << endl;
			} else if (result.first == '\'') {
				cout << "'\'' => " << result.second << endl;
			} else if (result.first == '\"') {
				cout << "'\"' => " << result.second << endl;
			} else if (result.first == '\t') {
				cout << "'\\t' => " << result.second << endl;
			} else if (result.first == '\v') {
				cout << "'\\v' => " << result.second << endl;
			} else if (result.first == '\r') {
				cout << "'\\r' => " << result.second << endl;
			} else if (result.first == '\n') {
				cout << "'\\n' => " << result.second << endl;
			} else if (result.first == '\0') {
				cout << "'\\0' => " << result.second << endl;
			}	else {
				cout << "'" << result.first << "' => " << result.second << endl;
			}
		}
		cout << endl;
	}
	
	// print numbers
	if (numbers.size() > 0) {
		numbers.erase("");
		cout << "Total " << numbers.size() << " numbers:" << endl;
// 		cout << "Debug: " << int(numbers.begin()->first[0]) << " => " << numbers.begin()->second << endl;
		for(auto result : numbers) {
			cout << result.first << " => " << result.second << endl;
		}
		cout << endl;
	}
	
	// print words
	if (words.size() > 0) {
		words.erase("");
		cout << "Total " << words.size() << " words:" << endl;
// 		cout << "Debug: " << int(words.begin()->first[0]) << " => " << words.begin()->second << endl;
		for(auto result : words) {
			cout << result.first << " => " << result.second << endl;
		}
	}
	
	return 0;
}

void insertCharacter(map<char,int> &characters, char character) {
	// insert character to characters map
	
	map<char,int>::iterator itr;
	itr = characters.find(character);
	if(itr == characters.end()) {
		// add to characters map if not in map
		characters.insert({character, 1});
	} else {
		// if character already exists in map, update frequency
		itr->second = (itr->second + 1);
	}
}

void insertNumber(map<string,int> &numbers, string &number) {
	// insert number to numbers map
	
	map<string,int>::iterator itr;
	itr = numbers.find(number);
	if(itr == numbers.end()) {
		// add to number map if not in map
		numbers.insert({number, 1});
	} else {
		// if number already exists in map, update frequency
		itr->second = (itr->second + 1);
	}
	number.clear();
}

void insertWord(map<string,int> &words, string &word) {
	// insert word to words map
	
	map<string,int>::iterator itr;
	itr = words.find(word);
	if(itr == words.end()) {
		// add to words map if not in map
		words.insert({word, 1});
	} else {
		// if word already exists in map, update frequency
		itr->second = (itr->second + 1);
	}
	word.clear();
}