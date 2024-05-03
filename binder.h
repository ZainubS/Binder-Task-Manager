#include <cstring>
#include <cctype>
#include <iostream>

//Zainub Siddiqui, CS163, 5/5/23
//Purpose: This header file will include the class interfaces
//of the Stack ADT, Queue ADT, binder class, and to-do item class.
//It will include global constants and function prototypes.

//constants
const int MAX = 5;

//queue - CLL
class todo_item
{
	public:
	todo_item();
	~todo_item();
	int create_todo(char * nameToAdd, char * descriptionToAdd, char * websiteToAdd, char * dueDateToAdd);
	int copy_todo(todo_item & copy_from);
	int retrieve_todo(todo_item & copy_to);
	int display();
	private:
	char * name;
	char * description;
	char * website;
	char * dueDate;
};

struct q_node
{
	todo_item q_object; 
	q_node * next;
};

class queue
{
	public:
	queue();
	~queue();
	int displayQueue();
	int enqueue(todo_item & to_add);
	int dequeue();
	int peek(todo_item & at_top);
	int copy_queue(queue * copy_from);
	private:
	int displayQueueHelper(q_node * temp, q_node * real_rear);
	q_node * rear;
};

//stack - LLL of arrays
class binder
{
	public:
	binder();
	~binder();
	int create_binder(char * subjectToAdd, char * statusToAdd, char * descriptionToAdd, int importanceToAdd);
	int add_todo_item(todo_item & item);
	int get_first_todo_item(todo_item & first_item);
	int remove_todo_item();
	int copy_binder(binder & copy_from);
	int retrieve_binder(binder & copy_to);
	int cleanup();
	int display();
	private:
	char * subject;
	char * status;
	char * description;
	int importance; 
	int listcount;
	queue * todolist;
};

struct s_node
{
	binder * collection;
	s_node * next;
};

class stack
{
	public:
	stack();
	~stack();
	int displayStack();
	int peek(binder & at_top);
	int pop();
	int push(binder & to_add);
	private:
	s_node * head;
	int top_index;
};

