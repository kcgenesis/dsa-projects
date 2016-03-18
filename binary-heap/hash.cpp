#include "hash.h"
#include <cmath>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


/*

bool hashTable::isPrime(int z) 
{
	
	//assume z is positive
	//lesser primes
	if (z==1) return false;
	if ((z==2)||(z==3)) return true;
	//weed out non primes
	if ((z%2 == 0)||(z%3 == 0)) return false;
	int i = 1;
	bool pos = false;
	double rootz = (int)sqrt(z);
	//if z isn't a multiple of a prime 
	//leading up to it's sqrt, it's prime
	while (i<=rootz) {
		if (pos == false) 
		{
			i = 6*i-1;
			pos = true;
		} 
		else 
		{
			i = 6*i+1;
			pos = false;
			i++;
		}

		if (z%i == 0) return false;
	}
	



	return true;
}

*/




/*
//accepts a minimum size of the array of primes.
//outputs pointer to that array

int* hashTable::primez (int size)
{
	//allocate memory
	int* arr = new int[size];
	//first prime
	int p = 2;
	//loop through arr


	for(int i=0;i<size;i++)
	{
		//while not prime
		while(!isPrime(p))
		{
			//increment
			p++;
		}
		arr[i] = p;
		p++;

	}
	return arr;
}
*/








//gets a prime number that is bigger than min
unsigned int hashTable::getPrime(int min) 
{

	/*
	if (size < primes[primeSize-1])
	{
		for(int i=0;i<primeSize;i++)
		{
			if (primes[i]<size)
			{
				i++;
			}
			else
			{
				if (increment == true)
				{
					return (unsigned int)primes[i];	
				}
				else
				{
					return (unsigned int)primes[i-2];
				}
				
			}
		}
	}
	else
	{

		cout<<"failure: not enough primes"<<endl;

		return 1;
	}

	if (size < primes[primeSize-1])
	{
		for(int i=0;i<primeSize;i++)
		{
			if (primes[i]<size)
			{
				i++;
			}
			else
			{
				if (increment == true)
				{
					return (unsigned int)primes[i];	
				}
				else
				{
					return (unsigned int)primes[i-2];
				}
				
			}
		}
	}
	else
	{

		cout<<"failure: not enough primes"<<endl;

		return 1;
	}
	*/

	//precomputed list of primes
	int lsize = 15; 
	unsigned int primes[15] = {
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
			cout<<"hashTable minimum size: "<<min<<endl;
			cout<<"hashTable constructed size: "<<primes[i]<<"\n"<<endl;
			return primes[i];
		}
	}
	cout<<"failure: not enough primes"<<endl;
}

hashTable::hashTable (int size) 
{
	/*
		insertions = 0;
		collisions = 0;
		res = 1;
		primes = primez(primeSize);
		let the size of array of primes be 1000 times the size of the prime #
		primeSize = 1000*size;
	*/
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
		cout<<"failure: "<< key <<" already exists in hash table"<<endl;
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


	cout<<"inserting "<<key<<" into hash table"<<endl;


	
	int index = hash(key);
	//if vacant or deleted, insert
	if ((data[index].isDeleted == true)||(data[index].isOccupied == false))
	{
		//cout<<"plain old insert successful"<<endl;
		data[index].isDeleted = false;
		data[index].pv = pv;
		data[index].isOccupied = true;
		data[index].key = key;
		filled++;
		//cout<< "filled:"<< filled << endl;
		return 0;
	}
	//if occupied, double hash
	//cout<<"COLLISION"<<endl;
	collisions++;
	//int index2 = hash2(key);


	cout<<"plain old insert failed"<<endl;
	while (data[index].isOccupied)
	{

		//double hashing
		//index = abs((index+index2)%capacity);
		//cout << "double hash "<< i <<" index: " << index << endl;

		//linear probing
		index = index+1;

		//if vacant or deleted, insert.
		if ((data[index].isDeleted == true)||(data[index].isOccupied == false))
		{
			cout<<"linear probing: successful"<<endl;
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
			cout<<"linear probing: trying again"<<endl;
			res++;
		}
	}
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
}




//linear probing
int hashTable::hash(const string &key)
{
	int hash = 0;
	//int i = 0;
	for(string::const_iterator it = key.begin(); it != key.end(); ++it)
	{
		//cout<<"char "<<i<<": "<< *it <<endl;
		hash = hash*101 + *it;
		//i++;
	}
	hash = abs(hash % capacity);
	//cout<<"h1 index: "<<hash<<endl;
	return hash;
}
/*
int hashTable::hash2(const string &key)
{
	int hash = 0;
	for(string::const_iterator it=key.begin();it != key.end();++it)
	{
		hash = hash*17 + *it;
	}
	//mod the hashed value with a prime smaller than the table size, subtract that number
	//from the prime just used and return that value

	int newPrime = getPrime(capacity,false);
	//cout<<"hash2 newprime: "<<newPrime<<endl;
	int index = newPrime - abs( hash % newPrime );
	//cout << "h2 index: " << index << endl;
	return index;
}
*/


bool hashTable::contains(const std::string &key)
{
	int pos = findPos(key);
	if ( pos >= 0 )
	{
		//cout<<"FIND FOUND"<<endl;
		return true;
	}
	else
	{
		//cout<<"FIND FAIL"<<endl;
		return false;
	}
}

int hashTable::findPos(const std::string &key)
{	
	//cout<<"searching for "<< key << " in hash table" <<endl;
	int index = hash(key);

	//while failed
	while ( (data[index].isDeleted) || (data[index].key != key) )
	{
		if (!(data[index].isOccupied))
		{
			//cout<<"COULD NOT FIND "<< key << " in hash table"<<endl;
			return -1;
		}
		//cout<<"linearly probing:"<<endl;
		//double hashing
		//index = abs((index+index2)%capacity);

		//linear probing
		index = abs((index+1)%capacity);
	}
	//if occupied and matches search key and isn't deleted		
	if ((data[index].isOccupied)&&(data[index].key == key)&&(!(data[index].isDeleted)))
	{
		//cout<<"FOUND"<<endl;
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
void* hashTable::getPointer(const std::string &key, bool *b)
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
	//cout<<"setting pointer of key "<< key <<" in hash table"<<endl;
	if (contains(key))
	{
		data[findPos(key)].pv = pv;
		return 0;
	}
	else
	{
		cout<<"setkey failure: could not find key "<< key <<" in hash table"<<endl;
		return 1;
	}
}

// Delete the item with the specified key.
// Returns true on success,
// false if the specified key is not in the hash table.
bool hashTable::remove(const std::string &key)
{
	//cout<<"removing "<< key <<" from hash table"<<endl;
	if (contains(key))
	{
		data[findPos(key)].isDeleted = true;
		//cout<<"success: deleted key "<< key << endl;	
		return true;
	}
	else
	{
		cout<<"remove failure: could not find key "<< key <<" in hash table"<<endl;
		return false;
	}
}