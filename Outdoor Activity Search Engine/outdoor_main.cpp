// JONATHAN HARIJANTO CS 163 HW ASSIGNMENT # 3

#include "outdoor_table.h"

// This program is sort of "search engine" program by using hash table
// as the data structure. First this program will ask which location
// around Oregon that the user want to know about the list of outdoor
// activities available. This program can remove all the information
// at that particular location, display only based on that particular 
// location and also display all the outdoor activities available not
// only in certain location but in the state of oregon.

using namespace std;

//Prototypes
bool again();
void function_test(int result);


int main()
{
	table act_journal;
	act_entry the_activities;
	act_info an_activities;
	
	act_journal.load_data ("activities.txt");

	cout << endl << "WELCOME TO OREGON OUTDOOR ACTIVITIES SEARCH ENGINE!" << endl << endl;

	int reply;	
	char answer_display [100];
	char answer_remove [100];
	char answer_retrieve [100];

	do
	{
		cout << "Press 1 to search based on location." << endl;
		cout << "Press 2 to display all." << endl;
		cout << "Press 3 to remove based on location." << endl;
		cout << "Enter your reply here: ";
		cin >> reply;
		cin.ignore (100, '\n');
		
		if (reply == 1)
		{
			cout << "Enter a location in Oregon you want to search (*starts with capital letter):  ";
			cin.get (answer_display, SIZE, '\n');
			cin.ignore (100, '\n');
			cout << endl;
			function_test(act_journal.display(answer_display));
		}
		else if (reply == 2)
		{
			cout << "These are all the list of outdoor activities that we have in Oregon: " << endl << endl;
			function_test(act_journal.display_all());
		}
		else if (reply == 3)
		{
			cout << "Enter a location in Oregon you want to remove (*starts with capital letter): ";
			cin.get (answer_remove, SIZE, '\n');
			cin.ignore (100, '\n');
			cout << endl;
			if (act_journal.remove(answer_remove) == 1)
			{
				cout << "Removal of any outdoor activities at that place success! " << endl;
				cout << "---- FUNCTION SUCCESS! ----" << endl;
			}
			else
				cout << endl<< "Sorry we dont find any outdoor activities at that place to be removed! " << endl << endl; 
		}

		else
			cout << endl << "Sorry the option you choose or the criteria you are looking for are not available" << endl << endl;


	} while (again ());

	cout << "Thank you for using our program! " << endl;

	return 0;				
}

// Function that will ask whether the user want to continue using
// the program or not. Will return true if the user type Y
bool again()
{
	char reply;
	cout << "Do you want to continue?  (Y/N): ";
	cin >> reply;
	cin.ignore (100, '\n');
	if (toupper(reply) == 'Y')
		return true;
	return false;
}

// Function that will display "Function Success" if the functions
// from hw3_table.cpp returns value 1, but it will display failed
// if the function not return 1
void function_test(int result)
{
	if (result == 1)
		cout << "---- FUNCTION SUCCESS! ----" << endl;
	else
		cout << "---- FUNCTION FAILED! ----" << endl;
}

