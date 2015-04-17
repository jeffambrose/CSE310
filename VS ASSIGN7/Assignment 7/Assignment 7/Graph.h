// Assignment #7
// Name: Jeff Ambrose
// ASU Email Address: jeffrey.ambrose@asu.edu
// Arizona State University CSE310
// Description: Sets up an adjacency list of vertexes that point to edges.

#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include "LinkedList.h"

using namespace std;

//constant colors used for dfs
const string WHITE = "white";
const string GREY = "grey";
const string BLACK = "black";

//arrays used for color, discover, finish, parent, and topological sort
string color[];
int d[];
int f[];
Vertex * pi[];
LinkedList topoSort[];

//vertex structure
struct Vertex
{
	string name;
	string color;
	LinkedList routes;
	int location;
};

//directed graph using adjacency list representation
class Graph
{
		int numVert;					//number of vertices
		int time;						//used for discover/finish times
		list<Vertex*> adj;				//an array containing adjacency lists
		void DFSVISIT(int u);			//to be used by DFS
	public:
		Graph(int V);					//constructor
		void addNode(string, int);		//add a node to a graph
		void addEdge(string, string);	//add an edge to graph
		void DFS();						//DFS traversal of the vertices reachable from v
		void printGraph();				//print out the graph adj list
		void sortGraph();				//call each list within graph to sort itself
		void printD();					//print discover array
		void printF();					//print finish array
		void printPi();					//print parent array
		void printTopo();				//print topological sort array
};

//create a graph of a certain number of vertices
Graph::Graph(int V)
{
	numVert = V;
	color[V];
	d[V];
	f[V];
	pi[V];
	topoSort[V];
}

//add a node to the graph
void Graph::addNode(string node, int num)
{
	Vertex * newPlace = new Vertex();
	newPlace->name = node;
	newPlace->location = num;
	//newPlace->color = WHITE;

	adj.push_back(newPlace);
}

//add an edge to the graph
void Graph::addEdge(string from, string to)
{
	int loc = 0;
	for (list<Vertex*>::iterator it = adj.begin(); it != adj.end(); ++it)
	{
		if ((*it)->name.compare(to) == 0)
		{
			loc = (*it)->location;
		}
	}

	Vertex * tempPlace = new Vertex();
	for (list<Vertex*>::iterator it = adj.begin(); it != adj.end(); ++it)
	{
		if ((*it)->name.compare(from) == 0)
		{
			(*it)->routes.addElement(to, 0, loc);
			return;
		}
	}
}

//used for testing purposes, prints graph out in adjacency list format
void Graph::printGraph()
{
	for (list<Vertex*>::iterator it = adj.begin(); it != adj.end(); ++it)
	{
		cout << (*it)->name << "->";
		(*it)->routes.printList("->");
		cout << "\n";
	}
}

//sorts the linked lists in alpha order within each node
void Graph::sortGraph()
{
	for (list<Vertex*>::iterator it = adj.begin(); it != adj.end(); ++it)
	{
		(*it)->routes.sortList();
	}
}

//dfs calls this function to visit nodes adjacent to u
void Graph::DFSVISIT(int u)
{
	color[u] = GREY;
	time++;
	d[u] = time;

	//struct pointer that equals the head of the node(u)
	struct Place * temp = adj->routes->head;
	int v;

	//for every node v adjacent to u, do (so for every node in routes until null?)
	for (list<Vertex*>::iterator it = adj.begin(); it != adj.end(); ++it)	//this won't work because it is iterating the adj list
	{
		//if we haven't discovered this node yet, set the parent and recursively go into it
		if (color[(*it)->location] == WHITE)
		{
			pi[(*it)->location] = u;		//this returns an int so that won't work, need a name somehow
			DFSVISIT(u);					//recursive call on adjacent, white node
		}
	}
	//finished with this node
	color[u] = BLACK;
	time++;
	f[u] = time;

	//insert into topological sort at head
	topoSort->addElement(adj->name, 0, 0);
}

//depth first search on a graph
void Graph::DFS()
{
	//for every node u in our graph, set color and parent
	for (int i = 0; i < numVert; i++)
	{
		color[i] = WHITE;
		pi[i] = NULL;
	}
	time = 0;

	//for every node u in our graph, if it hasn't been visited we visit it
	for (int u = 0; u < numVert; u++)
	{
		if (color[u] == WHITE)
		{
			DFSVISIT(u);
		}
	}
}

//print discover array
void Graph::printD()
{
	int index = 0;
	for (list<Vertex*>::iterator it = adj.begin(); it != adj.end(); ++it)
	{
		cout << "d[" << (*it)->name << "]=";
		cout << d[index];
		index++;
		cout << "\n";
	}
}

//print finish array
void Graph::printF()
{
	int index = 0;
	for (list<Vertex*>::iterator it = adj.begin(); it != adj.end(); ++it)
	{
		cout << "f[" << (*it)->name << "]=";
		cout << f[index];
		index++;
		cout << "\n";
	}
}

//print pi(parent) array
void Graph::printPi()
{
	int index = 0;
	for (list<Vertex*>::iterator it = adj.begin(); it != adj.end(); ++it)
	{
		cout << "pi[" << (*it)->name << "]=";
		if (index == 0)
		{
			cout << "none";
		}
		else
		{
			cout << *pi[index]->name;
		}
		index++;
		cout << "\n";
	}
}

//print topological sort array
void Graph::printTopo()
{
	topoSort->printList("\n");
}