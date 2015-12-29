// JONATHAN HARIJANTO CS 163 HW ASSIGNMENT # 3

// This is the .cpp files for the table data structure. It contains all the function that being mentioned in the table class.

#include "outdoor_table.h"
#include <fstream>

using namespace std;

// Constructor for hash table
table::table(int size)
{
	hash_table = new node * [size];
	hash_table_size = size;
	// Initialized one by one
	for (int i = 0;i < hash_table_size; ++i)
		hash_table[i] = 0;

}

// Deconstructor for hash table
table::~table()
{
	// Deallocate the list in each element of array one by one
	for (int i=0; i < hash_table_size; ++i)
	{
		if (!hash_table[i])
			return;
		else
		{
			node * temp = hash_table[i];
			while (hash_table[i])
			{
				hash_table[i] = temp -> next;
				delete temp;
				temp = hash_table[i];
			}
		}
	}
	delete [] hash_table;
}

// Function that will insert the information into a new node, as soon
// as the index of the slot of the array are being determined by
// the hash function.
int table::insert (char * location, const act_entry & to_add)
{
	int index;
	index = hash_function (location);
	// If the slot of array still have no nodes, create new one
	if (!hash_table[index])
	{
		node * temp = new node;
		temp -> entry.copy_entry(to_add);
		hash_table[index] = temp;
		temp -> next = NULL;
	}
	// If the slot of array already have list of nodes, add at the end
	else
	{
		node * temp = new node;
		temp -> entry.copy_entry(to_add);
		temp -> next = hash_table[index];
		hash_table[index] = temp;
	}		
}

// Function that will load all the information from external files into
// the programs. Deep copy required to copy the information because most
// of the data members in the struct are characters, except the "rating"
int table::load_data (const char * filename)
{
	act_entry temp_insert;
	act_info temp_info;

	char temp [500];
	int temp2;
	
	ifstream file_in;
	file_in.open (filename);

	if (!file_in)
		return 0;
	else
	{
		file_in.get(temp, SIZE, ',');
		file_in.ignore(100, ',');
		temp_info.name = new char [strlen (temp) + 1];
		strcpy (temp_info.name, temp);
		
		while (!file_in.eof())
		{
			file_in.get (temp, SIZE, ',');
			file_in.ignore(100, ',');
			temp_info.description = new char [strlen (temp) + 1];
			strcpy (temp_info.description, temp);
			
			file_in.get(temp, SIZE, ',');
			file_in.ignore(100, ',');
			temp_info.location = new char [strlen (temp) + 1];
			strcpy (temp_info.location, temp);

			file_in >> temp2;
			file_in.ignore(100 , ',');
			temp_info.rating = temp2;

			file_in.get(temp, SIZE, ',');
			file_in.ignore(100, ',');
			temp_info.requirement = new char [strlen (temp) + 1];
			strcpy (temp_info.requirement, temp);

			file_in.get(temp, SIZE, ';');
			file_in.ignore(100, ';');
			temp_info.add_info = new char [strlen (temp) + 1];
			strcpy (temp_info.add_info, temp);	

			temp_insert.create_entry(temp_info);
			insert (temp_info.location, temp_insert);
		
			file_in.get(temp, SIZE, ',');
			file_in.ignore(100, ',');
			temp_info.name = new char [strlen (temp) + 1];
			strcpy (temp_info.name, temp);
		}

		file_in.close();
	}

	return 1;
		 
}

// Function that will take the location and supply back to the
// calling routine information about the information of the certain 
// activities.
int table::retrieve (char * location, act_entry & found)
{
	int index;
	int sum = 0;
	bool success = false;
	index = hash_function (location);
	hash_table [index];
	// If no list of nodes in the slot of array
	if (!hash_table[index])
		return 0;
	// If list of nodes exist in the certian slot of the array
	node * current = hash_table [index];
	while (current && !success)
	{
		success = current -> entry.retrieve (location, found);
		current = current -> next;
		
	}
	if (success)
		return 1;
	else
		return 0;
	
}

// Function that will display only the location that the user
// wanted to search. It will search through out the whole array and
// the list of nodes inside of them, and if it is found it will print
// it.
int table::display (char * location)
{
	int index;
	index = hash_function (location);
	node * current = hash_table [index];
	while (current)
	{
		if (current -> entry.compare_entry (location) == 1)
			current -> entry.display();
		current = current -> next;
	}
	return 1;

}

// Function that will display all the list of nodes in each element of the
// array. It will keep displaying until the end of the array.
int table::display_all (void)
{
	// Go to each slot of element of array one by one.
	for (int i = 0; i < hash_table_size; ++i)
	{	
		node * current = hash_table [i];
		while (current)
		{
			current-> entry.display();
			current = current -> next;
		}
	
	}
	return 1;
			
}

// Function that will determine which data are going to be store in
// a certain slot of array. It takes "location" as argument then
// takes the certain words in order to get the index value.
int table::hash_function (char * location)
{
	int index;
	index = ((location [0] * 2) + (location [2]+ 1) ) % hash_table_size;
	return index;
}

// Function that will remove the data of the certain location that already
// been determined by the user in the main program. If the user type
// Portland, then it means that all of activities located at Portland
// will be removed from the hash_table.
int table::remove (char * location)
{
	int index;
	index = hash_function (location);
	// If no list of nodes exist in the certain slot of array
	if (!hash_table[index])
		return 0;
	node * current = hash_table [index];
	node * previous = NULL;
	node * temp = NULL;
	while (current)
	{
		// If the location match with first node
		if (hash_table[index] -> entry.compare_entry(location) == 1)
		{
			hash_table[index] = current -> next;
			delete current;
			current = hash_table[index];
		}
		// If the location match other than the first node
		else if (current -> entry.compare_entry (location) == 1)
		{
			temp = current;
			previous -> next = current->next;
			delete temp;
			current = previous;
		}
		previous = current;
		current = current -> next;
	}
	return 1; 
}
