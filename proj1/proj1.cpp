#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// function declarations
void insertCharacter(map<char,int> &characters, char character);
void insertNumber(map<string,int> &numbers, string &number);
void insertWord(map<string,int> &words, string &word);

// main function
int main() {
	char prevChar = '\0';
	unsigned int maxElementWidth = 0;
	int maxPrint;
	int counter = 0;
	string input;
	string word;
	// maps for storing elements and frequency
	map<string,int> words;
	map<string,int> numbers;
	map<char,int> characters;
	// vector pairs for sorting elements by frequency
	vector<pair<string,int>> sortedWords;
	vector<pair<string,int>> sortedNumbers;
	vector<pair<char,int>> sortedCharacters;
	// sort characters comparator
	struct character {
		bool operator() (pair<char,int> i, pair<char,int> j) { 
			return (i.second>j.second); 
		}
	} characterComparison;
	// sort string (words and numbers) comparator
	struct phrase {
		bool operator() (pair<string,int> i, pair<string,int> j) { 
			return (i.second>j.second); 
		}
	} stringComparison;
	
	// get input line by line
	while(getline(cin,input)) {
		// iterate through characters in the line
		for (char c : input) {
			// store character in lowercase for comparisons
			char lower = tolower(c);
			// if this is the first character in line, skip comparisons
			// 		and add to word temporary
			if(prevChar != '\0') {
				// check if character is a digit or letter or symbol
				if(c >= '0' && c <= '9') {
					// character is a digit
					
					// check if previous character was not digit
					if(prevChar >= 'a' && prevChar <= 'z') {
						// put word in words map
						insertWord(words, word);
					}
					
					// add character to word temporary
					word.push_back(c);
				} 
				else if (lower >= 'a' && lower <= 'z') {
					// character is a letter
					
					// check if previous character was a digit
					if(prevChar >= '0' && prevChar <= '9') {
						// put number in numbers map
						insertNumber(numbers, word);
					}
					
					// add character to word temporary
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
							
							// add character to word temporary
							word.push_back(c);
						} else if (lower >= 'a' && lower <= 'z') {
							// character is a letter

							// check if previous character was a digit
							if(prevChar >= '0' && prevChar <= '9') {
								// put number in numbers map
								insertNumber(numbers, word);
							}

							// add character to word temporary
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
					// add character to word temporary
					word.push_back(c);
				} else if (lower >= 'a' && lower <= 'z') {
					// add character to word temporary
					word.push_back(lower);
				}
			}
			// add to characters map
			insertCharacter(characters, c);
			
			// set checked character as previous character
			prevChar = lower;
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
	}
	
	// sort characters based on frequency into vector
	for(auto itr = characters.begin(); itr != characters.end(); ++itr) {
		sortedCharacters.push_back(*itr);
	}
	sort(sortedCharacters.begin(), sortedCharacters.end(), characterComparison);
	
	// sort numbers based on frequency into vector and erase empty keys
	numbers.erase("");
	for(auto itr = numbers.begin(); itr != numbers.end(); ++itr) {
		sortedNumbers.push_back(*itr);
	}
	sort(sortedNumbers.begin(), sortedNumbers.end(), stringComparison);
	
	// sort words based on frequency into vector and erase empty keys
	words.erase("");
	for(auto itr = words.begin(); itr != words.end(); ++itr) {
		sortedWords.push_back(*itr);
	}
	sort(sortedWords.begin(), sortedWords.end(), stringComparison);
	
	// check for largest character width of top ten words
	for(auto result : sortedWords) {
		if(counter < 10) {
			if(result.first.length() > maxElementWidth) {
				maxElementWidth = result.first.length();
			}
		}
		++counter;
	}
	counter = 0;
	for(auto result : sortedNumbers) {
		if(counter < 10) {
			if(result.first.length() > maxElementWidth) {
				maxElementWidth = result.first.length();
			}
		}
		++counter;
	}
	counter=0;
	maxElementWidth = maxElementWidth + 5;
	
	// print characters
	if(characters.size() > 10) {
		maxPrint = 10;
	} else {
		maxPrint = characters.size();
	}
	cout << "Total " << characters.size() << " different characters, " << maxPrint << " most used characters:" << endl;
	for(auto result : sortedCharacters) {
		if(counter < 10) {
			// format escaped characters
			if (result.first == '\\') {
				cout << "No. " << counter << ": " << setw(maxElementWidth) << left << "\\ \t " << result.second << endl;
			} else if (result.first == '\'') {
				cout << "No. " << counter << ": " << setw(maxElementWidth) << left << "\'" << result.second << endl;
			} else if (result.first == '\"') {
				cout << "No. " << counter << ": " << setw(maxElementWidth) << left << "\"" << result.second << endl;
			} else if (result.first == '\t') {
				cout << "No. " << counter << ": " << setw(maxElementWidth) << left << "\\t" << result.second << endl;
			} else if (result.first == '\v') {
				cout << "No. " << counter << ": " << setw(maxElementWidth) << left << "\\v" << result.second << endl;
			} else if (result.first == '\r') {
				cout << "No. " << counter << ": " << setw(maxElementWidth) << left << "\\r" << result.second << endl;
			} else if (result.first == '\n') {
				cout << "No. " << counter << ": " << setw(maxElementWidth) << left << "\\n" << result.second << endl;
			} else if (result.first == '\0') {
				cout << "No. " << counter << ": " << setw(maxElementWidth) << left << "\\0" << result.second << endl;
			}	else {
				cout << "No. " << counter << ": " << setw(maxElementWidth) << left << result.first << result.second << endl;
			}
		}
		++counter;
	}
	counter = 0;
	cout << endl;
	
	// find out max size, otherwise set to 10
	if(words.size() > 10) {
		maxPrint = 10;
	} else {
		maxPrint = words.size();
	}
	// print words
	cout << "Total " << words.size() << " different words, " << maxPrint << " most used numbers:" << endl;
	for(auto result : sortedWords) {
		if(counter < 10) {
			cout << "No. " << counter << ": " << setw(maxElementWidth) << left << result.first << result.second << endl;
		}
		++counter;
	}
	// reset counter
	counter = 0;
	cout << endl;
	
	// find out max size, otherwise set to 10
	if(numbers.size() > 10) {
		maxPrint = 10;
	} else {
		maxPrint = numbers.size();
	}
	// print numbers
	cout << "Total " << numbers.size() << " different numbers, " << maxPrint << " most used numbers:" << endl;
	for(auto result : sortedNumbers) {
		if(counter < 10) {
			cout << "No. " << counter << ": " << setw(maxElementWidth) << left << result.first << result.second << endl;
		}
		++counter;
	}	
	
	return 0;
}

// function definition
void insertCharacter(map<char,int> &characters, char character) {
	// insert character to characters map
	
	map<char,int>::iterator itr;
	itr = characters.find(character);
	if(itr == characters.end()) {
		// add to characters map if word not found in map
		characters.insert({character, 1});
	} else {
		// if character already exists in map, iterate frequency
		itr->second = (itr->second + 1);
	}
}

// function definition
void insertNumber(map<string,int> &numbers, string &number) {
	// insert number to numbers map
	
	map<string,int>::iterator itr;
	itr = numbers.find(number);
	if(itr == numbers.end()) {
		// add to number map if word not found in map
		numbers.insert({number, 1});
	} else {
		// if number already exists in map, iterate frequency
		itr->second = (itr->second + 1);
	}
	
	// reset temporary for new number string
	number.clear();
}

// function definition
void insertWord(map<string,int> &words, string &word) {
	// insert word to words map
	
	map<string,int>::iterator itr;
	itr = words.find(word);
	if(itr == words.end()) {
		// add to words map if word not found in map
		words.insert({word, 1});
	} else {
		// if word already exists in map, iterate frequency
		itr->second = (itr->second + 1);
	}
	
	// reset temporary for new word string
	word.clear();
}