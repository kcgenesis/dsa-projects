/*
	





*/





#include <iostream>
#include <fstream> 
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <locale> 
#include <cstdlib>
#include <string>
#include "graph.h"
#include "heap.h"
#include "hash.h"

using namespace std;













/*
	store the DATA of the nodes in a linked list.


	for all lines in file
		if [line] is NOT (empty OR begins with #)
		splice up into args[3] by ' '
		add args[0] and args[1] to the hash table
		edges++;
		

*/






int main()
{

	graph* myDag = new graph();
	cout<<"Please enter name of input file: "<<endl;
	string fname;
	cin >> fname;
	myDag->read(fname);
	cout<<"Please enter name of starting vertex: "<<endl;
	string start;
	cin >> start;
	myDag->dijkstra(start);
	return 0;
}