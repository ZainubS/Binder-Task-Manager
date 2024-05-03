#include "binder.h"
using namespace std;

//Zainub Siddiqui, CS163, 5/5/23
//Purpose - This is the main/client program 
//for this program. It will include a menu interface
//for the user and will output error messages if failure.

//prototypes
int menu();

int main ()
{
	int choice {0};

	//stack objects
	stack my_stack;

	//binder variables
	char subject[100];
	char status[50];
	char description[200];
	int importance {0};

	//todo_item variables
	char todoName[100];
	char todoDesc[100];
	char todoWebsite[100];
	char todoDueDate[100];
	char todoChoice {' '};

    do {
		choice = menu();
		if (choice == 1)
		{
			binder my_binder;
			todo_item itemToAdd;

			cout << "\nEnter Subject: ";
			cin.get(subject, 100); cin.ignore(100, '\n');
			cout << "Enter Status: ";
			cin.get(status, 50); cin.ignore(100, '\n');
			cout << "Enter description: ";
			cin.get(description, 200); cin.ignore(100, '\n');
			cout << "Enter importance (1-5): ";
			cin >> importance; cin.ignore(100, '\n');
			
			my_binder.create_binder(subject, status, description, importance);

			//add todo item
			cout << "Would you like to add a to-do list? (y/n): ";
			cin >> todoChoice; cin.ignore(100, '\n');
			
			if (toupper(todoChoice) == 'Y')
			{
				do { 
				cout << "\nTo-Do Item -" << endl;
				cout << "Enter Name of Item: ";
				cin.get(todoName, 100); cin.ignore(100, '\n');
				cout << "Enter description of what needs to be done: ";
				cin.get(todoDesc, 100); cin.ignore(100, '\n');
				cout << "Enter website/link: ";
				cin.get(todoWebsite, 100); cin.ignore(100, '\n');
				cout << "Enter due date: ";
				cin.get(todoDueDate, 100); cin.ignore(100, '\n');

				itemToAdd.create_todo(todoName, todoDesc, todoWebsite, todoDueDate);
				 
				//call enqueue function	
				if (!my_binder.add_todo_item(itemToAdd))
					cout << "Failure - didn't add item" << endl; 

				cout << "Add another to-do item? (y/n): ";
				cin >> todoChoice; cin.ignore(100, '\n');
				} while (toupper(todoChoice) != 'N');
				
				do { //remove todo item
				cout << "Remove the oldest todo item? (y/n): ";
				cin >> todoChoice; cin.ignore(100, '\n');
					if (toupper(todoChoice) == 'Y')
					{
						//call dequeue function
						if (!my_binder.remove_todo_item())
							cout << "Failure - couldn't remove item" << endl;
					}
				} while (toupper(todoChoice) != 'N');
				
				// Ask user if they want to peek queue
				cout << "Do you want to peek the todo list (look at first item)? (y/n): ";
				cin >> todoChoice; cin.ignore(100, '\n');
				
				todo_item first_item;
				if (toupper(todoChoice) == 'Y')
				{
					if(my_binder.get_first_todo_item(first_item))
					{
						first_item.display();
					}
					else
						cout << "Unable to peek first todo item" << endl;
				}
			}
			
			//push onto stack
			if(!my_stack.push(my_binder))
				cout << "Error - Could not add binder" << endl;
		}
		else if (choice == 2) //remove top binder
		{
			if (!my_stack.pop())
				cout << "Nothing to pop!" << endl;
		}
		else if (choice == 3) //display top of stack
		{
			binder top_binder;
			if (my_stack.peek(top_binder))
			{
				top_binder.display();
			}
			else
				cout << "No Items to Display!" << endl;
		}
		else if (choice == 4) //display all binders
		{
			if (!my_stack.displayStack())
				cout << "Nothing to display!" << endl;
		}

	   } while (choice != 5);

	return 0;
}

//menu interface
int menu()
{
	int choice {0};
	cout << "\nMenu Options:" << endl
	<< "1. Add a Binder" << endl
	<< "2. Remove Most Recent Binder" << endl
	<< "3. Display Most Recent Binder" << endl
	<< "4. Display Binders" << endl
	<< "5. Quit" << endl
	<< ">> ";
	cin >> choice; cin.ignore(100, '\n');
	return choice;
}
