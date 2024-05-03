#include "binder.h"
using namespace std;

//Zainub Siddiqui, CS163, 5/5/23
//Purpose - Implement the member functions
//of the binder class AND todo class.

//***** todo_item class member functions *****

//constructor - initialize data members to null
todo_item::todo_item()
{
	name = NULL;
	description = NULL;
	website = NULL;
	dueDate = NULL;
}

//destructor - deallocate dynamic memory
todo_item::~todo_item()
{
	delete [] name;
	delete [] description;
	delete [] website;
	delete [] dueDate;
	name = description = website = dueDate = NULL;
}

//create a todo-item - deep copy into data members
int todo_item::create_todo(char * nameToAdd, char * descriptionToAdd, char * websiteToAdd, char * dueDateToAdd)
{
	  if (!nameToAdd || !descriptionToAdd || !websiteToAdd || !dueDateToAdd)
	  {   
		  return 0;
      }

	  if (name)
	  {        
		  delete [] name;
	  }        
	  if (description)
	  {      
		  delete [] description;
	  }        
	  if (website)
	  {      
		  delete [] website;
	  }       
	  if (dueDate)
	  {
		  delete [] dueDate;
	  }

	  name = description = website = dueDate = NULL;

	  name = new char[strlen(nameToAdd) + 1];
	  strcpy(name, nameToAdd);
	  description = new char[strlen(descriptionToAdd) + 1];
	  strcpy(description, descriptionToAdd);
	  website = new char[strlen(websiteToAdd) + 1];
	  strcpy(website, websiteToAdd);
	  dueDate = new char[strlen(dueDateToAdd) + 1];
	  strcpy(dueDate, dueDateToAdd);
	  return 1;
}

//copy todo_item 
int todo_item::copy_todo(todo_item & copy_from)
{
	int success = 0;
	success = create_todo(copy_from.name, copy_from.description, copy_from.website, copy_from.dueDate);

	return success;
}

//retrieve todo_item 
int todo_item::retrieve_todo(todo_item & copy_to)
{
	if (!name || !description || !website || !dueDate)
	{
		  return 0;
	}

	copy_to.name = new char[strlen(name) + 1];
	strcpy(copy_to.name, name);
	copy_to.description = new char[strlen(description) + 1];
	strcpy(copy_to.description, description);
	copy_to.website = new char[strlen(website) + 1];
	strcpy(copy_to.website, website);
	copy_to.dueDate = new char[strlen(dueDate) + 1];
	strcpy(copy_to.dueDate, dueDate);

	return 1;
}

//display todo item
int todo_item::display()
{
	if (!name || !description || !website || !dueDate)
	{
		  return 0;
	}

	cout << "\t-----------------------------" << endl
	<< "\tName: " << name << "\n\tDescription: " << description
	<< "\n\tWebsite: " << website << "\n\tDue Date:  "
	<< dueDate << endl
	<< "\t-----------------------------" << endl;

	return 1;
}

//**** binder class member functions *****

//constructor - initilize data members
binder::binder()
{
	subject = NULL;
	status = NULL;
	description = NULL;
	importance = 0;
	todolist = NULL;
	listcount = 0;
}

//destructor - deallocate dynamic  memory
binder::~binder()
{
	cleanup();
}

//add todo item to binder - call enqueue()
int binder::add_todo_item(todo_item & item)
{
	int success = 0;
	if (!todolist)
	{
		todolist = new queue;
		if(success)
			++listcount;
	}

	if (todolist)
	{
		success = todolist->enqueue(item);
		if(success)
			++listcount;
	}
	return success;	
}

//remove first todo-item - call dequeue()
int binder::remove_todo_item()
{
	int success = 0;
	if (todolist)
		success = todolist->dequeue();

	if(success)
		--listcount;

	return success;	
}
//deallocates dynamic memory - clean-up function
int binder::cleanup()
{
	delete [] subject;
	delete [] status;
	delete [] description;
	delete todolist;
	subject = status = description = NULL;
	todolist = NULL;
	importance = 0;
	return 1;
}

//create binder
int binder::create_binder(char * subjectToAdd, char * statusToAdd, char * descriptionToAdd, int importanceToAdd)
{
      if (!subjectToAdd|| !statusToAdd || !descriptionToAdd)
		  return 0;

      if (subject)
      {        
          delete [] subject;
      }        
      if (status)
      {      
          delete [] status;
      }        
      if (description)
      {      
          delete [] description;
      }       

      subject = status = description = nullptr; 
               
      subject = new char[strlen(subjectToAdd) + 1];
      strcpy(subject, subjectToAdd);
      status = new char[strlen(statusToAdd) + 1];
      strcpy(status, statusToAdd);
	  description = new char[strlen(descriptionToAdd) + 1];
	  strcpy(description, descriptionToAdd);
	  importance = importanceToAdd;
	  
	  listcount = 0; 
               
      return 1;
}

//copies data members into argument 
int binder::retrieve_binder(binder & copy_to)
{
	if (!subject || !status || !description)
	{
		  return 0;
	}

	copy_to.subject = new char[strlen(subject) + 1];
	strcpy(copy_to.subject, subject);
	copy_to.status = new char[strlen(status) + 1];
	strcpy(copy_to.status, status);
	copy_to.description = new char[strlen(description) + 1];
	strcpy(copy_to.description, description);
	copy_to.importance = importance;

	copy_to.todolist = new queue;
	copy_to.todolist->copy_queue(todolist);

	return 1;

}

//copies binder
int binder::copy_binder(binder & copy_from)
{
	int success = create_binder(copy_from.subject, copy_from.status, copy_from.description, copy_from.importance);
	
	listcount = copy_from.listcount;

	if(listcount == 0)
	{
		return success; 	//there's no todo items to add
	}

	//deep copy the queue
	if(!todolist && copy_from.todolist)
	{
		todolist = new queue;
		success = todolist->copy_queue(copy_from.todolist);
	}
	else if(todolist && copy_from.todolist)
	{
		success = todolist->copy_queue(copy_from.todolist);
	}
	return success;
}

//retrieves first todo item - call peek()
int binder::get_first_todo_item(todo_item & first_item)
{
	if (!todolist)
		return 0;
	int success = todolist->peek(first_item);

	return success;
}

//displays one binder
int binder::display()
{
	if (!subject || !status || !description)
	{
		return 0;
	}
	cout << "***********************************" << endl
	<< "Subject: " << subject << "\nStatus: " << status
	<< "\nDescription: " << description << "\nImportance (1-5): "
	<< importance << endl;

	int success = 0;
	if (todolist)
	{
		success = todolist->displayQueue();
	}
	cout << "***********************************" << endl;

	return 1;
}

