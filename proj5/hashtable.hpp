/*
  Name: Joshua Potter (jop13)
  Class: COP4530
  Assignment 5 - hashtable.hpp
*/

#include "hashtable.h"

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

template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k) {
	auto & whichList = theLists[myhash(k)];
	auto itr = find_if(whichList.begin(), whichList.end(), [&k](std::pair<K, V> element) { return element.first == k; });
	
	if(itr == end(whichList)) {
		return false;
	} else {
		return true;
	}
// 	if(whichList.size() > 0) {
// 		for(auto & element : whichList) {
// 			if(element.first == k) {
// 				return true;
// 			}
// 		}
// 		return false;
// 	} else {
// 		return false;
// 	}
}

template <typename K, typename V>
bool HashTable<K, V>::match(const std::pair<K, V> &kv) const {
	auto & whichList = theLists[myhash(kv.first)];
	
	if(whichList.size() > 0) {
		for(auto & element : whichList) {
			if(element.first == kv.first) {
				if(element.second == kv.second) {
					return true;
				}
			}
		}
		return false;
	} else {
		return false;
	}
}

template <typename K, typename V>
bool HashTable<K, V>::insert(const std::pair<K, V> & kv) {
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
				break;
			}
		}
	} else {
		whichList.push_back(kv);
	}
	
	// rehash if we iterate out of bounds
	if(++currentSize > theLists.size()) {
		rehash();
	}
	
	return true;
}

template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K,  V> && kv) {
	auto & whichList = theLists[myhash(kv.first)];
	
	if(whichList.size() > 0) {
		for(auto & element : whichList) {
			if(element.first == kv.first) {
				if(element.second == kv.second) {
					return false;
				} else {
					std::swap(element.second, kv.second);
					break;
				}
			} else {
				whichList.push_back(kv);
				break;
			}
		}
	} else {
		whichList.push_back(kv);
	}
	
	// rehash if we iterate out of bounds
	if(++currentSize > theLists.size()) {
		rehash();
	}
	
	return true;
}

template <typename K, typename V>
bool HashTable<K, V>::remove(const K & k) {
	auto & whichList = theLists[myhash(k)];
	auto itr = find_if(whichList.begin(), whichList.end(), [&k](std::pair<K, V> element) { return element.first == k; });
	
	if(itr == end(whichList)) {
		return false;
	}
	
	whichList.erase(itr);
	--currentSize;
	
	return true;
}

template <typename K, typename V>
void HashTable<K, V>::clear() {
	makeEmpty();
}

template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename) {
	bool flag = false;
	std::ifstream file;
	std::string data;
	
	file.open(filename);
	while(std::getline(file, data)) {
		std::string key;
		std::string value;
		std::istringstream iss(data);
		
		iss >> key >> value;
		
		std::pair<std::string, std::string> element = std::make_pair(key, value);
		insert(element);
		flag = true;
	}
	file.close();
	
	return flag;
}

template <typename K, typename V>
void HashTable<K, V>::dump() {
	int vectorIndex = 0;
	int listIndex = 0;
	
	for(auto & v : theLists) {
		std::cout << "v[" << vectorIndex << "]: ";
		for(auto & l : v) {
			if(listIndex > 1) {
				std::cout << ":";
			}
			std::cout << l.first << " " << l.second;
			++listIndex;
		}
		std::cout << std::endl;
		vectorIndex++;
		listIndex = 0;
	}
}

template <typename K, typename V>
size_t HashTable<K, V>::size() {
	return currentSize;
}

template <typename K, typename V>
bool HashTable<K, V>::write_to_file(const char *filename) {
	std::ofstream file;
	
	file.open(filename);
	for(auto & v : theLists) {
		for(auto & element : v) {
			file << element.first << " " << element.second << std::endl;
		}
	}
	file.close();
	
	return true;
}

template <typename K, typename V>
void HashTable<K, V>::makeEmpty() {
	for(auto & thisList : theLists) {
		thisList.clear();
	}
}

template <typename K, typename V>
void HashTable<K, V>::rehash() {
	std::vector<std::list<std::pair<K, V>> > oldLists = theLists;
	
	// create new list with double the size
	theLists.resize(prime_below(2 * theLists.size()));
	for(auto & thisList : theLists) {
		thisList.clear();
	}
	
	// copy over new list
	currentSize = 0;
	for(auto & thisList : oldLists) {
		for(auto & x : thisList) {
			insert(std::move(x));
		}
	}
}

template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k) {	
	static std::hash<K> hf;
	return hf(k) % theLists.size();
}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n) {
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
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
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes) {
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

