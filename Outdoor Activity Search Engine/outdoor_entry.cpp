// JONATHAN HARIJANTO CS 163 HW ASSIGNMENT # 3

// A ".cpp" files for entry. In this file, all the functions that mentioned in the 
// act_entry class are written. It also contain the Constructor and Deconstructor
// of the struct act_info too!

#include "outdoor_entry.h"

using namespace std;

// Constructor of a struct!
act_info::act_info()
{
	name = NULL;
	description = NULL;
	location = NULL;
	rating = 0;
	requirement = NULL;
	add_info = NULL;
}

// Deconstructor of a struct!
act_info::~act_info()
{
	if (name)
		delete [] name;
	if (description)
		delete [] description;
	if (location)
		delete [] location;
	if (requirement)
		delete [] requirement;
	if (add_info)
		delete [] add_info;
}

// Function that will perform a deep copy to an empty entry from source file of data
int act_entry::create_entry(act_info & new_entry)
{
	activity.name = new char [strlen (new_entry.name) + 1];
	strcpy (activity.name, new_entry.name);

	activity.description = new char [strlen (new_entry.description) + 1];
	strcpy (activity.description, new_entry.description);

	activity.location = new char [strlen (new_entry.location) + 1];
	strcpy (activity.location, new_entry.location);

	activity.rating = new_entry.rating;

	activity.requirement = new char [strlen (new_entry.requirement) + 1];
	strcpy (activity.requirement, new_entry.requirement);

	activity.add_info = new char [strlen (new_entry.add_info) + 1];
	strcpy (activity.add_info, new_entry.add_info);
}

// Function that will perform a deep copy from source file of data to destination.
int act_entry::copy_entry(const act_entry & new_entry)
{
	if (new_entry.activity.name)
	{
		activity.name = new char [strlen (new_entry.activity.name) + 1];
		strcpy (activity.name, new_entry.activity.name);
	}

	if (new_entry.activity.description)
	{
		activity.description = new char [strlen (new_entry.activity.description) + 1];
		strcpy (activity.description, new_entry.activity.description);
	}
	
	if (new_entry.activity.location)
	{
		activity.location = new char [strlen (new_entry.activity.location) + 1];
		strcpy (activity.location, new_entry.activity.location);
	}

	if (new_entry.activity.rating)
		activity.rating = new_entry.activity.rating;

	if (new_entry.activity.requirement)
	{
		activity.requirement = new char [strlen (new_entry.activity.requirement) + 1];
		strcpy (activity.requirement, new_entry.activity.requirement);
	}
	
	if (new_entry.activity.add_info)
	{
		activity.add_info = new char [strlen (new_entry.activity.add_info) + 1];
		strcpy (activity.add_info, new_entry.activity.add_info);
	}
}

// Function that will check if location from what the user entered with the available 
// location from entry same or node. If same, it will call the copy_entry function
// This is like the "prerequisite" inorder for copy_entry to be called.
int act_entry::retrieve(char * location, act_entry & found)
{
	if (strcmp (found.activity.location, location) == 0)
	{
		copy_entry(found);
		return 1;
	}
	return 0;
}

// Function that will print all the informations contain in one entry.
int act_entry::display(void)
{
	if (activity.name)
		cout << "Name: " << activity.name << endl;
	if (activity.description)
		cout << "Description: " << activity.description << endl;
	if (activity.location)
		cout << "Location: " << activity.location << endl;
	if (activity.rating)
		cout << "Rate of Difficulty (1; no prior knowledge - 5; requires training): " << activity.rating << endl;
	if (activity.requirement)
		cout << "Equipment requirement? : " << activity.requirement << endl;
	if (activity.add_info)
		cout << "Additional information: " << activity.add_info << endl << endl;
}

// Function that will compare the location information from the what been passed 
// from the program with the location in that particular entry. If match will return 1.
int act_entry::compare_entry (char * location)
{
	if (strcmp (location, activity.location) == 0)
		return 1;
	return 0;
}
