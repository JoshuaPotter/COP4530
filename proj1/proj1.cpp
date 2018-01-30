#include <iostream>
#include<string>
#include <map>

using namespace std;

void insertCharacter(map<char,int> &characters, char character) {
	characters.insert({character, 1});
	// add to characters map if not in vector
	//if() {
		
	//} else {
		// if character already exists in vector
	//}
}

void insertNumber(map<string,int> &numbers, string number) {
	numbers.insert({number, 1});
	// add to numbers vector if not in vector
	//if() {
		
	//} else {
		// if number already exists in vector
	//}
}

void insertWord(map<string,int> &words, string word) {
	words.insert({word, 1});
	// add to word vector if isn't in vector
	//if(words.find(word) == words.end()) {
		
	//} else {
		// if word already exists in vector
	//}
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
			char lower = tolower(c);
			
			// check if theres a previous character
			if(prevChar != '\0') {
				// check if character is a digit or letter
				if(c >= '0' && c <= '9') {
					// character is a digit
					
					// check if previous character was not digit
					if(prevChar >= 'a' && prevChar <= 'z') {
						
						// put word in words map
						insertWord(words, word);
						word.clear();
					}
					
					// add character to characters map
					insertCharacter(characters, c);
					word.push_back(c);
				} else if (lower >= 'a' && lower <= 'z') {
					// character is a letter
					
					// check if previous character was a digit
					if(prevChar >= '0' && prevChar <= '9') {
						// put number in numbers map
						insertNumber(numbers, word);
						word.clear();
					}
					
					// add character to character map
					insertCharacter(characters, c);
					word.push_back(lower);
				} else {
					// non-digit and non-letter character
					if((prevChar >= '0' && prevChar <= '9')||(prevChar >= 'a' && prevChar <= 'z')) {
						if(c >= '0' && c <= '9') {
							// character is a digit

							// check if previous character was not digit
							if(prevChar >= 'a' && prevChar <= 'z') {
								// add word to words map
								insertWord(words, word);
								word.clear();
							}

							// add character to characters map
							insertCharacter(characters, c);

							word.push_back(c);
						} else if (lower >= 'a' && lower <= 'z') {
							// character is a letter

							// check if previous character was a digit
							if(prevChar >= '0' && prevChar <= '9') {
								// put number in numbers map
								insertNumber(numbers, word);
								word.clear();
							}

							// add character to characters map
							insertCharacter(characters, c);

							word.push_back(lower);
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
		// 
// 		cout << "word: " << word << endl;
	}
	
	cout << "Characters" << endl;
	for(auto result : characters) {
		cout << result.first << ": " << result.second << endl;
	}
	cout << endl;
	
	cout << "Numbers" << endl;
	for(auto result : numbers) {
		cout << result.first << ": " << result.second << endl;
	}
	cout << endl;
	
	cout << "Words" << endl;
	for(auto result : words) {
		cout << result.first << ": " << result.second << endl;
	}
	cout << endl;
	
	return 0;
}