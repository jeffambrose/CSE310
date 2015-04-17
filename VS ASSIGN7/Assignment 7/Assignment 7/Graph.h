// Assignment #7
// Name: Jeff Ambrose
// ASU Email Address: jeffrey.ambrose@asu.edu
// Arizona State University CSE310
// Description: Sets up an adjacency list of vertexes that point to edges.

#include <iostream>
#include <iomanip>
#include <string>
#include <list>
#include <array>
#include "LinkedList.h"

using namespace std;

//constant colors used for dfs
const string WHITE = "white";
const string GREY = "grey";
const string BLACK = "black";

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
		list<Vertex*> adj;				//adjacency list
		void DFSVISIT(Vertex * u);		//to be used by DFS
		string * color;					//to store colors
		int * d;						//to store discover time
		int * f;						//to store finish time
		string * pi;					//to store parent node
		LinkedList * topoSort;			//to store topological sort order
		int loc = 0;
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
	color = new string[numVert];
	d = new int[numVert];
	f = new int[numVert];
	pi = new string[numVert];
	topoSort = new LinkedList[numVert];
}

//add a node to the graph
void Graph::addNode(string node, int num)
{
	Vertex * newPlace = new Vertex();
	newPlace->name = node;
	newPlace->location = num;
	newPlace->color = WHITE;

	adj.push_back(newPlace);
}

//add an edge to the graph
void Graph::addEdge(string from, string to)
{
	for (list<Vertex*>::iterator it = adj.begin(); it != adj.end(); it++)
	{
		if ((*it)->name.compare(to) == 0)
		{
			loc = (*it)->location;
			break;
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
		cout << (*it)->name << "(" << (*it)->location << ")->";
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
void Graph::DFSVISIT(Vertex * u)
{
	u->color = GREY;
	color[u->location] = GREY;
	time++;
	d[u->location] = time;

	//for every node v adjacent to u, do
	for (Place * current = u->routes.head; current != NULL; current = current->next)
	{
		//if we haven't discovered this node yet, set the parent and recursively go into it
		if (color[current->location] == WHITE)
		{
			pi[current->location] = u->name;					//store the parent node

			//find the vertex we should go into
			for (list<Vertex*>::iterator it = adj.begin(); it != adj.end(); ++it)
			{
				//if we find it let's visit it
				if ((*it)->location == current->location)
				{
					DFSVISIT(*it);
				}
			}						
		}
	}
	//finished with this node
	u->color = BLACK;
	color[u->location] = BLACK;
	time++;
	f[u->location] = time;

	//insert into topological sort at head
	topoSort->addElement(u->name, 0, 0);
}

//depth first search on a graph
void Graph::DFS()
{
	//for every node u in our graph, set color and parent
	for (int i = 0; i < numVert; i++)
	{
		color[i] = WHITE;
		pi[i] = "none";
	}
	time = 0;

	//for every node u in our graph, if it hasn't been visited we visit it
	for (list<Vertex*>::iterator it = adj.begin(); it != adj.end(); ++it)
	{
		if ((*it)->color == WHITE)
		{
			DFSVISIT(*it);
		}
	}
}

//print discover array
void Graph::printD()
{
	int index = 0;
	cout << "" << endl;
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
	cout << "" << endl;
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
	cout << "" << endl;
	for (list<Vertex*>::iterator it = adj.begin(); it != adj.end(); ++it)
	{
		cout << "pi[" << (*it)->name << "]= ";
		cout << pi[index];
		index++;
		cout << "\n";
	}
}

//print topological sort array
void Graph::printTopo()
{
	topoSort->printList("");
}
