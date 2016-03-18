#include "heap.h"
#include "hash.h"
#include <math.h>
#include <cstring>
#include <cstdlib>
#include <climits>
using namespace std;

/*
	Kirk Cameron
	Binary Heap 
	12.2.15

	This is a binary heap data structure which uses a hash table
	to implement quick node lookup for editing and removal.
*/

heap::heap(int capacity) 
{
	heapData.resize(capacity);
	max_size = capacity;
	curr_size = 0;
	maxkey = 0;
	heap_h = 0;
	isEven = true;
	eta = new hashTable(capacity);
	node zero;
	heapData[0] = zero;
}

int heap::insert(const std::string &id, int key, void *pv) 
{
	if (eta->contains(id))
	{
		return 2;
	}
	if (maxkey < key)
	{
		maxkey = key;	
	}

	curr_size++;
	if (curr_size == max_size)
	{
		heapData.resize(max_size*2);
	}
	heapData[curr_size].id = id;			
	heapData[curr_size].pv = pv;
	heapData[curr_size].key = maxkey+1;
	eta->insert(id,&heapData[curr_size]);

	setKey(id,key);
	heap_h = (int)(log(curr_size)/log(2));
	//print();
	return 0;
}

int heap::path (int &index, bool dir)
{
	//percolateDown
	//int next_h;
	if (dir == false)
	{
		int lc = index*2;
		int rc = lc+1;
		if (heapData[lc].key > heapData[rc].key)
		{
			if (rc>curr_size)
			{
				return -1;
				//cout<<"floor reached"<<endl;
			}
			return rc;
		}
		else
		{
			if (lc>curr_size)
			{
				return -1;
				//cout<<"floor reached"<<endl;
			}
			return lc;
		}
	}
	//percolateUp
	else if (dir == true)
	{
		int up = index/2;
		if (up<1)
		{
			return -1;
			//cout<<"ceiling reached"<<endl;
		}
		return up;
	}
	//cout<<"shouldnt get here"<<endl;
	exit(1);
}




int heap::percolate(int &curr,int &next)
{
	heapData[curr] = heapData[next];
	eta->setPointer(heapData[next].id,&heapData[curr]);
	curr = next;

	return 0;
}
		
int heap::setKey(const std::string &id, int key)
{
	bool inTable;

	node* hole = (node*)eta->getPointer(id, &inTable);
	if (!inTable)
	{
		return 1;
	}
	//print();

	node* temp = new node;
	temp->id = id;
	temp->pv = hole->pv;
	temp->key = key; 

	
	int index = hole - &heapData[0];
	int up = path(index,true);
	int dn = path(index,false);

	//satisfy heap order
	if(up >= 0)
	{
		while(heapData[up].key > temp->key)
		{
			//cout<<"percolating up"<<endl;
			percolate(index,up);
			up = path(index,true);
			if (up<0){break;}
		}	
	}
	if (dn >= 0)
	{
		while(heapData[dn].key < temp->key)
		{
			//cout<<"percolating down"<<endl;
			percolate(index,dn);
			dn = path(index,false);
			if (dn<0){break;}
		}
	}

	heapData[index] = *temp;

	eta->setPointer(id,&heapData[index]);

	delete temp;
	return 0;
}



//print the heap
int heap::print()
{
	int h = 0;
	int hn = 0;
	cout<<"STATUS"<<endl;
	for(int i=1;i<=curr_size;i++)
	{
		hn = (int)(log(i)/log(2));
		if (h < hn)
		{
			cout<<endl;
		}
		bool inTable;
		node* loc = (node*)eta->getPointer(heapData[i].id , &inTable);
		if (!inTable)
		{
			cout<<"id "<< heapData[i].id <<" is not in table"<<endl;
			return 1;
		}
		cout << "["<< heapData[i].key 		<<	", ";
		cout <<	 "["<< heapData[i].id 		<<	",";
		cout 		<< loc - &heapData[0]	<<  "],";
		cout 		<< heapData[i].pv <<"], ";
		

		h = hn;
	}
	cout<<endl<<endl;
	return 0;
}


/*
*/
int heap::deleteMin(std::string *pId, int *pKey, void *ppData)
{
	//cout<<"deleting id: "<< *pId <<endl;
	if (curr_size == 0)
	{
		return 1;
	}
	node* hole = &(heapData[1]);
	/*
		int del_key = hole->key;
		void* del_ptr = hole->pv;
		const string del_str = hole->id;
	*/
	eta->remove(hole->id);
	if (pId)
	{
		*pId = hole->id;
	}
	if (pKey)
	{
		*pKey = hole->key;
	}
	if (ppData)
	{
		*(static_cast<void **>(ppData)) = hole->pv;
	}
	curr_size--;
	node* last = &heapData[curr_size+1];

	hole->id = last->id;
	hole->key = last->key;
	hole->pv= last->pv;
	eta->setPointer(hole->id,hole);

	setKey(last->id,last->key);
	//print();
	return 0;
}


//setKey to -infinity
//deleteMin
int heap::remove(const std::string &id, int *pKey, void *ppData)
{
	bool inTable;
	node* hole = (node*)eta->getPointer(id, &inTable);
	if (!inTable)
	{
		return 1;
	}
	if (pKey)
	{
		*pKey = hole->key;
	}
	if (ppData)
	{
		*(static_cast<void **>(ppData)) = hole->pv;
	}
	
	setKey(id,INT_MIN);
	
	int retval = deleteMin();

	return retval;
}