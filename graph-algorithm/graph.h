#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <string>
#include <iostream>
#include <climits>
#include <list>
#include "heap.h"
#include "hash.h"

class graph {
	private:
		class node;
	public:
		graph();
		int insertNode(const std::string &vname, graph::node*& inode);
		void dijkstra(const std::string &vertex);
		bool contains(const std::string &vertex);
		void read(const std::string &fname);
		void output(node* start, double difference);

	private:
		hashTable* nHash;
		std::list<node*> nList;

		class node {
			private:
				class edge;
			public:
				node();
				std::string name;// = "";
				bool known;// = false;
				node* prev;// = NULL;
				int dist;// = INT_MAX;
				std::list<edge*> edgeList;

				int insertEdge(node* dest, int cost=1);
				/* {
					edge newEdge;
					newEdge.cost = cost;
					newEdge.dest = dest;
					edgeList.push_back(newEdge);
					return 0;
				}*/

			private:
				class edge {
					public:
						edge(node* vertex);
						node* dest;
						int cost;// = 1;
				};
		};
};

#endif //_GRAPH_H




