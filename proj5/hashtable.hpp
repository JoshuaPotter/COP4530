/*
  Name: Joshua Potter (jop13)
  Class: COP4530
  Assignment 5 - hashtable.hpp
*/

#include "hashtable.h"

using namespace std;

// constructor
template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size) {
	currentSize = 0;
	theLists.resize(prime_below(size));
}

// destructor
template <typename K, typename V>
HashTable<K, V>::~HashTable() {
	clear();
}

// check if key k is in the hash table.
template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k) {
	auto & whichList = theLists[myhash(k)];
	auto itr = find_if(whichList.begin(), whichList.end(), [&k](pair<K, V> element) { return element.first == k; });
	
	if(itr == end(whichList)) {
		return false;
	} else {
		return true;
	}
}

// check if key-value pair is in the hash table.
template <typename K, typename V>
bool HashTable<K, V>::match(const pair<K, V> &kv) const {
	auto & whichList = theLists[const_cast<HashTable*>(this)->myhash(kv.first)];
	
	if(whichList.size() > 0) {
		for(auto & element : whichList) {
			if(element.first == kv.first) {
				if(element.second == kv.second) {
					return true;
				}
			}
		}
	}
  
  return false;
}

// add  the key-value pair kv into the hash table. 
template <typename K, typename V>
bool HashTable<K, V>::insert(const pair<K, V> & kv) {
	auto & whichList = theLists[myhash(kv.first)];
	
	if(whichList.size() > 0) {
		for(auto & element : whichList) {
			if(element.first == kv.first) {
				if(element.second == kv.second) {
					return false;
				} else {
					element.second = kv.second;
					break;
				}
			} else {
				whichList.push_back(kv);
        ++currentSize;
				break;
			}
		}
	} else {
		whichList.push_back(kv);
    ++currentSize;
	}
	
	// rehash if we iterate out of bounds
	if(currentSize > theLists.size()) {
		rehash();
	}
	
	return true;
}

//move version of insert.
template <typename K, typename V>
bool HashTable<K, V>::insert(pair<K,  V> && kv) {
	auto & whichList = theLists[myhash(kv.first)];
	
	if(whichList.size() > 0) {
		for(auto & element : whichList) {
			if(element.first == kv.first) {
				if(element.second == kv.second) {
					return false;
				} else {
					swap(element.second, kv.second);
					break;
				}
			} else {
				whichList.push_back(kv);
        ++currentSize;
				break;
			}
		}
	} else {
		whichList.push_back(kv);
    ++currentSize;
	}
	
	// rehash if we iterate out of bounds
	if(currentSize > theLists.size()) {
		rehash();
	}
	
	return true;
}

// delete the key k and the corresponding value if it is in the hash table. 
template <typename K, typename V>
bool HashTable<K, V>::remove(const K & k) {
	auto & whichList = theLists[myhash(k)];
	auto itr = find_if(whichList.begin(), whichList.end(), [&k](pair<K, V> element) { return element.first == k; });
	
	if(itr == end(whichList)) {
		return false;
	}
	
	whichList.erase(itr);
	--currentSize;
	
	return true;
}

// delete all elements in the hash table
template <typename K, typename V>
void HashTable<K, V>::clear() {
	makeEmpty();
}

// load the content of the file with name filename into the hash table.
template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename) {
	bool flag = false;
	ifstream file;
	string data;
	
	file.open(filename);
	while(getline(file, data)) {
		string key;
		string value;
		istringstream iss(data);
		
		iss >> key >> value;
		
		pair<string, string> element = make_pair(key, value);
		insert(element);
		flag = true;
	}
	file.close();
	
	return flag;
}

// display all entries in the hash table.
template <typename K, typename V>
void HashTable<K, V>::dump() {
	int vectorIndex = 0;
	int listIndex = 0;
	
	for(auto & v : theLists) {
		cout << "v[" << vectorIndex << "]: ";
		for(auto & l : v) {
			if(listIndex > 0) {
				cout << ":";
			}
			cout << l.first << " " << l.second;
			++listIndex;
		}
		cout << endl;
		vectorIndex++;
		listIndex = 0;
	}
}

// return the number of elements in the hash table.
template <typename K, typename V>
size_t HashTable<K, V>::size() {
	return currentSize;
}

// write all elements in the hash table into a file with name filename
template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename) {
	ofstream file;
	
	file.open(filename);
	for(auto & v : theLists) {
		for(auto & element : v) {
			file << element.first << " " << element.second << endl;
		}
	}
	file.close();
	
	return true;
}

// delete all elements in the hash table.
template <typename K, typename V>
void HashTable<K, V>::makeEmpty() {
	for(auto & thisList : theLists) {
		thisList.clear();
	}
}

// Called when the number of elements in the hash table is greater than the size of the vector.
template <typename K, typename V>
void HashTable<K, V>::rehash() {
	vector<list<pair<K, V>> > oldLists = theLists;
	
	// create new list with double the size
	theLists.resize(prime_below(2 * theLists.size()));
	for(auto & thisList : theLists) {
		thisList.clear();
	}
	
	// copy over new list
	currentSize = 0;
	for(auto & thisList : oldLists) {
		for(auto & x : thisList) {
			insert(move(x));
		}
	}
}

 // return the index of the vector entry where k should be stored.
template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) {	
	static hash<K> hf;
	return hf(k) % theLists.size();
}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n) {
  if (n > max_prime)
    {
      cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(vector<unsigned long>& vprimes) {
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

