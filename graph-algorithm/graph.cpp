#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <ctime>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include "graph.h"
#include "hash.h"
#include "heap.h"
using namespace std;

/*
	Kirk Cameron
	Graph
	12.2.15

	This is a graph data structure which gives the user the ability
	to set the weight of paths.  It has a built-in read function which 
	loads the node and edge information from a text file.  Dijkstra's
	algorithm is implemented as a member function of this class.
*/


graph::node::node()
{
	name = "";
	known = false;
	prev = NULL;
	dist = INT_MAX;
}
graph::node::edge::edge(node* vertex)
{
	cost = 1;
	dest = vertex;
}
int graph::node::insertEdge(node* dest, int cost)
{
	edge* newEdge = new edge(dest);
	newEdge->cost = cost;
	edgeList.push_back(newEdge);	
	return 0;

}





graph::graph()
{
	nHash = new hashTable();
}

//return 1 on failure, 
//0 on success
int graph::insertNode(const string &vname, node*& inode)
{
	if(!contains(vname))
	{
		inode = new node();
		inode->name = vname;
		nHash->insert(vname,inode);
		nList.push_back(inode);
		return 0;
	}
	else
	{
		return 1;
	}
}

void graph::read(const string &fname)
{
	ifstream file1 (fname.c_str());
	if (!file1) 
	{
		cerr << "Error: could not open " << file1 << endl;
		exit(1);
	}
	if (file1.is_open())
	{
		string args[3];
		string line;
		while (getline(file1,line))
		{
			for(int i=0;i<3;i++)
			{
				args[i] = "";
			}
			int i=0;
			//for comments n blanks	
			if (!((strlen(line.c_str()) == 1) || (line[0] == '#')))
			{
				for (string::iterator it = line.begin();it != line.end();it++)
				{
					if (*it != ' ')
					{
						args[i] += *it;
					}
					else
					{
						i++;
					}
				} 
			}
			//cout<<"\ninserting edge from: "<<args[0]<<
			//" to "<<args[1]<<" with weight "<<args[2]<<endl;
			const string node1 = args[0];
			const string node2 = args[1];
			int dist = atoi(args[2].c_str());
			
			node* v1 = NULL;
			node* v2 = NULL;


			insertNode(node1,v1);
			insertNode(node2,v2);


			bool v1exists;
			bool v2exists;
			v1 = static_cast<node*>(nHash->getPointer(node1,&v1exists));
			v2 = static_cast<node*>(nHash->getPointer(node2,&v2exists));
			if (v1exists)
			{	
				if (v1 == NULL)
				{
					cout<< node1 <<" insert FAILURE"<<endl;	
				}
			}
			if (v2exists)
			{
				if (v2 == NULL)
				{
					cout<< node2  <<" insert FAILURE"<<endl;
				}
			}
			if (v1exists && v2exists)
			{
				v1->insertEdge(v2,dist);
			} 
			else 
			{
				cerr << "Error: could not create vertex" << file1 << endl;
				exit(1);
			}
		}
	}
}

bool graph::contains(const string &vertex)
{
	return nHash->contains(vertex);
}


void graph::dijkstra(const std::string &vertex)
{
	if (nList.empty())
	{
		return;
	}

	clock_t t1 = clock();
	bool startExists;
	node* start = static_cast<node*>(nHash->getPointer(vertex,&startExists));
	if (!startExists)
	{
		cerr<<"start vertex doesn't exist!"<<endl;
		return;
	}

	start->dist = 0;
	start->prev = start;
	heap* queue = new heap(nList.size()+1);
	//push list into queue keyed by dist.
	for (list<node*>::iterator it = nList.begin() ; it != nList.end(); ++it)
	{
		queue->insert( (*it)->name, (*it)->dist, *it);
	}

	

	int dist;
	string vert;
	node nnode;
	void* nptr = &nnode;
	while(queue->deleteMin(&vert,&dist,&nptr) == 0)
	{
		node* next = static_cast<node*>(nptr);
		next->known = true;
		if (next->prev != NULL)
		{
			for (list<graph::node::edge*>::iterator ed = next->edgeList.begin() ; ed != next->edgeList.end(); ++ed)
			{
				if (!((*ed)->dest->known))
				{
					int newDist = (*ed)->cost + next->dist;
					if(newDist < (*ed)->dest->dist)
					{	
						(*ed)->dest->prev = next;
						(*ed)->dest->dist = newDist;
						queue->setKey( (*ed)->dest->name, (*ed)->dest->dist);
					}
				}
			}
		}
	}
	
	
	clock_t t2 = clock();
	double diff = ((double)(t2-t1))/CLOCKS_PER_SEC;
	output(start, diff);
}

void graph::output(node* start, double diff)
{
	cout << "Total time is: " << diff << endl;
	string fname;
	cout << "Please enter name of the output file: ";
	cin >> fname;

	ofstream outfile (fname.c_str());
	
	for (list<node*>::iterator nd = nList.begin(); nd != nList.end(); nd++)
	{
		outfile << (*nd)->name << ": ";
		if ((*nd)->prev == NULL)
		{
			outfile << "NO PATH" << endl;
		} 
		else 
		{
			outfile << (*nd)->dist << " ";
			//print names along path
			stack<string> nameStack;
			if ((*nd) != start)
			{
				nameStack.push((*nd)->name);
			}
			//regurgitate in reverse order from src using stack
			node* toSrc = (*nd)->prev;
			while (toSrc != start)
			{
				nameStack.push(toSrc->name);
				toSrc = toSrc->prev;
			}
			outfile << "[" << start->name;
			while (!nameStack.empty())
			{
				outfile << ", " << nameStack.top();
				nameStack.pop();
			}
			outfile << "]" << endl;
		}
	}
	outfile.close();	
}


