// Assignment #7
// Name: Jeff Ambrose
// ASU Email Address: jeffrey.ambrose@asu.edu
// Arizona State University CSE310
// Description: This program takes a number of nodes followed by node names
//				and enters them into a linked list. It then takes edges between
//				the nodes and registers them. Using this data we will implement
//				topological sort.
//
//				1. Using the given input, store this information as an adjacency list or an adjacency matrix. You should
//				   store them in alphabetical order so that DFS can be performed in alphabetical order. Note that you can
//				   assume that node names start with each of 'A', 'B', 'C', 'D', etc. each node for each upper case letter
//				   of the alphabet for simplicity (therefore, there will be at most 26 nodes in this case). However, node 
//				   names can be different depending on each input. For instance, instead of "ARUBA" to start with 'A', you
//				   might have "AUSTRALIA" instead as a name to start with an 'A'.
//				2. Using the same data set, perform the Depth First Search, starting with the node/vertex 'A' (thus for the
//				   above example, starting with "ARUBA"), and visits its adjacent notes in alphabetical order.
//				3. In the Depth First Search algorithm:
//						Create arrays pi, color, d (for discover time of each node), and f (for finish time of each node).
//						As you compute the finish time for each node, you will need to insert it into the beginning of your
//						linked list. This needs to be done within the Depth First Search.
//				   In summary, you need to have at least the following data structures:
//						-One of an adjacency list or an adjacency matrix
//						-Four arrays, pi, color, d, and f
//						-A Linked List to store all nodes in the order of Topological Sort
//				4. To complete the step 3 above, you will need to implement LinkedList class with insertElement function to
//				   insert each node at the beginning and a printList function to print the content of the LinkedList.
//				5. You should implement a driver class with a main method which takes input from a keyboard.

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <list>

#include "Graph.h"

using namespace std;

//declare helpers
string * split(string str, char delim);
int numVert = 0;
int numEdge = 0;

//run the program
int main() 
{
	string line;
	string * rawInput;

	//grab the array size
	cin >> numVert;
	cin.ignore(20, '\n');		//flush buffer

	Graph adjList(numVert);

	//input the data into an adjacency list at zero
	for (int i = 0; i < numVert; ++i)
	{
		//grab each array element and enter into array
		getline(cin, line);
		adjList.addNode(line, i);
	}

	//grab the number of edges
	cin >> numEdge;
	cin.ignore(20, '\n');		//flush buffer

	//loop through the next lines creating edges in the list
	for (int i = 0; i < numEdge; i++)
	{
		getline(cin, line);
		rawInput = &line;

		//split the input into a to and from component
		rawInput = split(line, '-');
		string from = rawInput[0];
		string to = rawInput[1];

		//insert from into to's list
		adjList.addEdge(from, to);
	}

	adjList.sortGraph();			//sort the lists in adj list into alphabetical order
	adjList.printGraph();			//test that the adj list is being correctly created
	adjList.DFS();					//call DFS on our adjacency list to populate values

	//print array pi
	cout << "The array pi content:\n\n";
	adjList.printPi();

	//print array d
	cout << "\n\nThe array d content:\n\n";
	adjList.printD();

	//print array f
	cout << "\n\nThe array f content:\n\n";
	adjList.printF();

	//print topological sort
	cout << "\n\nTopological order:\n\n";
	adjList.printTopo();
}

//helper function to split the class number and title string into two
string * split(string str, char delim)
{
	string * result = new string[2];

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == delim)
		{
			result[0] = str.substr(0, i);
			result[1] = str.substr(i + 2, str.length() - 1);
			break;
		}
	}
	return result;
}
