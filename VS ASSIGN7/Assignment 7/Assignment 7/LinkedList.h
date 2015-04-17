// Assignment #7
// Name: Jeff Ambrose
// ASU Email Address: jeffrey.ambrose@asu.edu
// Arizona State University CSE310
// Description: Sets up a linked list to print topological sort. Inserts at head of list then prints.

#include <iostream>		//to use cout
#include <iomanip>		//to format output
#include <string>		//to use strings

using namespace std;

//struct represents some place information
struct Place
{
	string title;
	struct Place * next;
	int location;
};

//class LinkedList will contain a linked list of places
class LinkedList {
private:

public:
	LinkedList();
	~LinkedList();
	bool addElement(string title, int index, int num);
	void printList(string newLine);
	void sortList();
	int getSize();
	struct Place * head;
};

//constructor to initialize the linked list
LinkedList::LinkedList()
{
	head = NULL;
}

//destructor
LinkedList::~LinkedList()
{
	Place * current = head;
	while (current != 0)	//cycle through and delete all places keeping count
	{
		Place * next = current->next;
		delete current;
		current = next;
	}
	head = NULL;	//reset head to NULL
}

//addElement to head of list
bool LinkedList::addElement(string newTitle, int index, int num)
{
	//check if index is less than zero
	if (index < 0)
	{
		return false;
	}

	struct Place * newPlace = new Place;
	newPlace->title = newTitle;
	newPlace->next = NULL;
	newPlace->location = num;

	//check if head is null (no list exists) create list
	if (head == NULL)
	{
		if (index == 0)
		{
			head = newPlace;
			return true;
		}
		return false;
	}
	//if index is zero, add at zero
	else if (index == 0)
	{
		newPlace->next = head;
		head = newPlace;
		return true;
	}
	//else, add at index requested
	else
	{
		int count = 0;
		Place * prev = head;
		Place * current = head;
		do    //cycle through to requested index location
		{
			count++;
			prev = current;
			current = current->next;
			if (index == count)		//reset pointers to correct locations
			{
				prev->next = newPlace;
				newPlace->next = current;
				return true;
			}
		} while (current->next != NULL);
		if (current->next == NULL && count <= index)	//if last item, set node
		{
			current->next = newPlace;
			return true;
		}
	}
	return false;
}

//printList starting at head
void LinkedList::printList(string newline)
{
	//check if empty list
	if (head == NULL)
	{
		cout << "NULL";
	}
	else    //otherwise cycle through and print list in order
	{
		Place * next = head;
		while (next != NULL)
		{
			cout << next->title << newline;
			next = next->next;
		}
	}
}

//compare list title values starting at head and sort as needed
void LinkedList::sortList()
{
	//check if empty list or single member list, no need to sort
	if (head == NULL || head->next == NULL)
	{
		return;
	}
	else    //otherwise we have a list to sort so we sort it
	{
		for (Place *index = head; index->next != nullptr; index = index->next) 
		{
			for (Place *selection = index->next; selection != nullptr; selection = selection->next) 
			{
				if (index->title.compare(selection->title) > 0) 
				{
					swap(index->title, selection->title);
					swap(index->location, selection->location);
				}
			}
		}
	}
}
