#include "hash.h"
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


//gets a prime number that is bigger than min
unsigned int hashTable::getPrime(int min) 
{

	//precomputed list of primes
	int lsize = 15; 
	int primes[15] = {
		1019,
		2003,
		4001,
		8117,
		16703,
		30509,
		40213,
		50321,
		60953,
		80317,
		100297,
		201961,
		437243,
		832451,
		1299827 
	};

	for (int i=0;i<lsize;i++)
	{
		if (min <= primes[i])
		{
			return primes[i];
		}
	}
	cout<<"failure: not enough primes"<<endl;
	exit(1);
}

hashTable::hashTable (int size) 
{
	capacity = getPrime(size);
	filled = 0;
	data.resize(capacity);

	//initialize all values
	for (std::vector<hashItem>::iterator it = data.begin() ; it != data.end(); ++it)
	{
		it->isDeleted = false;
		it->pv = NULL;
		it->isOccupied = false;
	}
}

int hashTable::insert(const std::string &key, void *pv) 
{
	//check: is key unique?
	if (contains(key))
	{
		//cout<<"hashTable::insert failure: "<< key <<" already exists in hash table"<<endl;
		return 1;
	}

	//rehash if necessary
	float load = (float)filled/(float)capacity;
	if (load>0.5)
	{
		//cout << "load factor "<< load <<": rehashing"<<endl;
		if (rehash() == -1)
		{
			//cout << "rehash failure"<<endl;
			return 2;
		}
	}


	//cout<<"hashTable::insert inserting "<<key<<" into hash table"<<endl;


	
	int index = hash(key);
	//if vacant or deleted, insert
	if ((data[index].isDeleted == true)||(data[index].isOccupied == false))
	{
		data[index].isDeleted = false;
		data[index].pv = pv;
		data[index].isOccupied = true;
		data[index].key = key;
		filled++;
		return 0;
	}
	collisions++;

	while (data[index].isOccupied)
	{
		//linear probing
		index = index+1;

		//if vacant or deleted, insert.
		if ((data[index].isDeleted == true)||(data[index].isOccupied == false))
		{
			//cout<<"linear probing: successful"<<endl;
			data[index].isDeleted = false;
			data[index].pv = pv;
			data[index].isOccupied = true;
			data[index].key = key;
			filled++;
			return 0;	
		}
		//otherwise if occupied
		else if (data[index].isOccupied)
		{
			//cout<<"linear probing: trying again"<<endl;
			res++;
		}
	}
	return 2;
}

bool hashTable::rehash()
{
	vector<hashItem>* temp;
	temp = new vector<hashItem>;
	//copy data to temp
	*temp = data;
	//resize data
	int newPrime = getPrime(capacity*2);
	data.resize(newPrime);
	capacity = newPrime;
	//loop through data and reset all values
	for (vector<hashItem>::iterator it = data.begin(); it != data.end(); ++it)
	{
		it->isDeleted = false;
		it->isOccupied = false;
	}
	filled = 0;
	//loop through temp and if the value is occupied and not deleted
	//hash it into data
	for (vector<hashItem>::iterator it = temp->begin(); it != temp->end(); ++it)
	{
		if((it->isOccupied)&&(!(it->isDeleted)))
		{
			insert(it->key);
		}
	}
	delete temp;
	return true;
}




//linear probing
int hashTable::hash(const string &key)
{
	int hash = 0;
	for(string::const_iterator it = key.begin(); it != key.end(); ++it)
	{
		hash = hash*101 + *it;
		
	}
	hash = abs(hash % capacity);
	return hash;
}


bool hashTable::contains(const std::string &key)
{
	int pos = findPos(key);
	if ( pos >= 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}


//PROBLEM WITH THIS FUNCTION
//in relation to getpointer
int hashTable::findPos(const std::string &key)
{	

	int index = hash(key);
	while ( (data[index].isDeleted) || (data[index].key != key) )
	{
		if (!(data[index].isOccupied))
		{
			return -1;
		}
		index = abs((index+1)%capacity);
	}
	if ((data[index].isOccupied)&&(data[index].key == key)&&(!(data[index].isDeleted)))
	{
		return index;	
	}
	else 
	{
		return -1;
	}
}


// Get the pointer associated with the specified key.
// If the key does not exist in the hash table, return NULL.
// If an optional pointer to a bool is provided,
// set the bool to true if the key is in the hash table,
// and set the bool to false otherwise.
void* hashTable::getPointer(const std::string &key, bool* b)
{
	if (b)
	{
		if (contains(key))
		{
			*b = true;
			return data[findPos(key)].pv;
		} 
		else
		{
			*b = false;
			return NULL;
		}
	}
	else
	{
		if (contains(key))
		{
			return data[findPos(key)].pv;
		}
		else
		{
			return NULL;
		}	
	}
}




// Set the pointer associated with the specified key.
// Returns 0 on success,
// 1 if the key does not exist in the hash table.
int hashTable::setPointer(const std::string &key, void *pv)
{
	if (contains(key))
	{
		data[findPos(key)].pv = pv;
		return 0;
	}
	else
	{
		return 1;
	}
}

// Delete the item with the specified key.
// Returns true on success,
// false if the specified key is not in the hash table.
bool hashTable::remove(const std::string &key)
{
	if (contains(key))
	{
		data[findPos(key)].isDeleted = true;
		return true;
	}
	else
	{
		return false;
	}
}