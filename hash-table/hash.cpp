#include "hash.h"
#include <vector>
#include <string>
#include <cmath>
#include <iostream>
using namespace std;

// The constructor initializes the hash table.
// Uses getPrime to choose a prime number at least as large as
// the specified size for the initial size of the hash table.
hashTable::hashTable(int size) {
	capacity = getPrime(size);
	data.resize(capacity);
	filled = 0;
	for(int i=0;i<data.size();i++)
	{
		data[i].isOccupied = false;
		data[i].isDeleted = false;
		data[i].pv = NULL;
		data[i].key = "";
	}
}

// Insert the specified key into the hash table.
// If an optional pointer is provided,
// associate that pointer with the key.
// Returns 0 on success,
// 1 if key already exists in hash table,
// 2 if rehash fails.
int hashTable::insert(const std::string &key, void *pv) {
	if(contains(key)) {
		return 1;
	}
	int index = hash(key);

	while((data[index].isOccupied))
	{
		if(data[index].isDeleted){
			break;
		}
		else{
			index = abs((index+1)%capacity);
		}
	}

	data[index].isOccupied = true;
	data[index].isDeleted = false;
	data[index].pv = pv;
	data[index].key = key;
	filled++;

	float load = (float)filled/(float)capacity;
	if (load>0.5) {
		if(!rehash()) {
		cout<<"reash fail: mem alloc fail"<<endl;
		return 2;
		}
	}
	return 0;
}


// Check if the specified key is in the hash table.
// If so, return true; otherwise, return false.
bool hashTable::contains(const std::string &key){
	int pos = findPos(key);
	if(pos>=0){
		return true;
	}
	else{
		return false;
	}
}

// Get the pointer associated with the specified key.
// If the key does not exist in the hash table, return NULL.
// If an optional pointer to a bool is provided,
// set the bool to true if the key is in the hash table,
// and set the bool to false otherwise.
void* hashTable::getPointer(const std::string &key, bool *b){
	int index = findPos(key);
	if(b){
		if(index!=-1){
			*b = true;
			if(data[index].pv){
				return data[index].pv;
			}
			else{
				return NULL;
			}
		}
		else {
			*b = false;
			return NULL;
		}
		
	}
	else{
		if(index!=-1){
			if(data[index].pv){
				return data[index].pv;
			}
			else{
				return NULL;
			}
		}
	}
	return NULL;	
}

// Set the pointer associated with the specified key.
// Returns 0 on success,
// 1 if the key does not exist in the hash table.
int hashTable::setPointer(const std::string &key, void *pv){
	if(contains(key)){
		int index = findPos(key);
		data[index].pv = pv;
		return 0;
	}
	else{
		return 1;
	}
}

// Delete the item with the specified key.
// Returns true on success,
// false if the specified key is not in the hash table.
bool hashTable::remove(const std::string &key){
	if(contains(key)){
		int index = findPos(key);
		data[index].isDeleted = true;
		return true;
	}
	else {
		return false;
	}
}

// The hash function
int hashTable::hash(const std::string &key){
	int seed = 0;
	int hash = seed;
    for(int i=0;i<key.size();i++){
        hash = hash * 101  + key[i];
    }
    return abs(hash%capacity);
}

// The rehash function; makes the hash table bigger.
// Returns true on success, false if memory allocation fails.
bool hashTable::rehash(){
	vector<hashItem> *temp = new vector<hashItem>;
	*temp = data;
	
	capacity = getPrime(capacity*2);
	try{
		data.resize(capacity);
	}
	catch(std::bad_alloc& exc){
		return false;
	}
	filled = 0;
	for(int i=0;i<data.size();i++) {
		data[i].isOccupied = false;
		data[i].isDeleted = false;
	}

	for(int i=0;i<temp->size();i++) {
		if(((*temp)[i].isOccupied)&&(!(*temp)[i].isDeleted))
		{
			insert((*temp)[i].key);
		}
	}
	delete temp;
	return true;
}


// Search for an item with the specified key.
// Return the position if found, -1 otherwise.
int hashTable::findPos(const std::string &key){
	int i = hash(key);
	while(!(!data[i].isOccupied)||(data[i].isDeleted))
	{
		if((data[i].isOccupied)&&(!data[i].isDeleted)&&(data[i].key==key)){
			return i;
		} 
		else {
			i = abs((i+1)%capacity);
		}
	}
	return -1;

}


// Return a prime number at least as large as size.
// Uses a precomputed sequence of selected prime numbers.
unsigned int hashTable::getPrime(int size){
	unsigned int primes[13] = {
		79,
		239,
		557,
		1021,
		2237,
		4003,
		8039,
		16747,
		25031,
		32027,
		67577,
		144887,
		301247
	};
	for(int i=0;i<13;i++){
		if(size>primes[i]){
			i++;
		}
		else{
			return primes[i];
		}
	}
	cerr<<"getPrime: requested prime too large"<<endl;
}
