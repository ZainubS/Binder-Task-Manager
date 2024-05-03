#include "binder.h"
using namespace std;

//Zainub Siddiqui, CS163, 5/5/23
//This file will implement the member functions of the queue
//class. Data structure that will be used is a circular 
//linked list.

//constructor - inilitize data members
queue::queue()
{
	rear = nullptr;
}

//destructor - deallocate dynamic memory
queue::~queue()
{
	if (!rear)
		return;
	q_node * temp = rear->next;
	rear->next = nullptr;
	while (temp)
	{
		rear = temp->next;
		delete temp;
		temp = rear;
	}
	rear = nullptr;
}

//copies a queue pointer's CLL to another queue pointer
int queue::copy_queue(queue * copy_from)
{
	int success {0};
	if (copy_from && copy_from->rear)
	{
		q_node * temp = copy_from->rear->next;
		do {
			success = enqueue(temp->q_object);
			temp = temp->next;
		} while (temp != copy_from->rear->next);
	}

	return success;
}

//enqueue - add an item to the end of the list
int queue::enqueue(todo_item & to_add)
{
	int success {0};

	if (!rear)
	{
		rear = new q_node;
		rear->next = rear;
		success = rear->q_object.copy_todo(to_add);
	}
	else
	{
		q_node * temp = rear->next;
		rear->next = new q_node;
		rear = rear->next;
		success = rear->q_object.copy_todo(to_add);
		rear->next = temp;
	}

	return success;	
}

//dequeue - remove an item from the front of the list
int queue::dequeue()
{
	if (!rear)
		return 0;
	//one item
	if (rear == rear->next)
	{
		delete rear; rear = nullptr;
	}
	else
	{
		q_node * temp = rear->next;
		rear->next = temp->next;
		delete temp;
	}
	return 1;
}

//display queue recursively
int queue::displayQueueHelper(q_node * temp, q_node * real_rear)
{
	if (temp == real_rear)
	{
		temp->q_object.display();
		return 1;
	}

	temp->q_object.display();
	return displayQueueHelper(temp->next, real_rear);
}

//display queue wrapper
int queue::displayQueue()
{
	if (!rear)
		return 0;
	if (rear == rear->next)
	{
		rear->q_object.display();
		return 1;
	}
	return displayQueueHelper(rear->next, rear);
}

//peek queue - retrieve what is the first in the queue
int queue::peek(todo_item & at_top)
{
	if (!rear || !rear->next)
		return 0;
	int success {0};
	success = rear->next->q_object.retrieve_todo(at_top);
	
	return success;
}

