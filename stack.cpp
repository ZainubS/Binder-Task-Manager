#include "binder.h"
using namespace std;

//Zainub Siddiqui, CS163, 5/5/23
//Purpose: This file will implement the member functions
//of the stack ADT class. Data structure used is
//flexible array - LLL of arrays.

//constructor - initilize data members
stack::stack()
{
	head = NULL;
	top_index = 0;	
}

//destructor - deallocate dynamic memory
stack::~stack()
{
	s_node * temp = NULL;
	while (head != NULL)
	{
		temp = head->next;
		delete [] head->collection;
		delete head;
		head = temp;
	}

	head = NULL;
	top_index = 0;
}

//push - add a binder to the top
int stack::push(binder & to_add)
{
	s_node * temp = NULL;

	if (!head) 
	{
		head = new s_node;
		head->collection = new binder[MAX];
		head->next = NULL;
		top_index = 0;
		if (head->collection[top_index].copy_binder(to_add))
		{
			++top_index;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
	if (top_index < MAX)
	{
			if (head->collection[top_index].copy_binder(to_add))
			{
				++top_index;	
				return 1;
			}
			else
			{
				return 0;
			}
    }
	else if (top_index == MAX) //new node
	{
		temp = head;
		head = new s_node;
		head->collection = new binder[MAX];
		head->next = temp;
		top_index = 0;

		if (head->collection[top_index].copy_binder(to_add))
		{
			++top_index;	
			return 1;
		}
		else
		{
			return 0;
		}
	}

	return 1;
}

//Display all binders
int stack::displayStack()
{
	int index {0};
	if (!head)
		return 0;
	s_node * current = head;

	while (current)
	{
		index = MAX-1;
		while(index >= 0)
		{
			current->collection[index].display();
			--index;
		}
		
		current = current->next;
	}
	return 1;
}

//pop the most recent binder (remove) 
int stack::pop()
{
	if (!head)
		return 0;
	s_node * temp = head->next;
	if (top_index == 0 || top_index == 1)
	{
		if (head->collection)
		{
			delete [] head->collection;
		}
		delete head;
		head = temp;
		if (head)
		{
			top_index = MAX;
		}
		else
			top_index = 0;
		return 1;
	}
	else // top_index > 1
	{
		--top_index;
		head->collection[top_index].cleanup();
	}
	return 1;
}

//peek - See which binder is at top and return through argument
int stack::peek(binder & at_top)
{
	if (!head || top_index == 0)
		return 0;
	
	head->collection[top_index-1].retrieve_binder(at_top);
	return 1;
}
