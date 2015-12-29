// JONATHAN HARIJANTO CS 163 HW ASSIGNMENT # 3

// A ".h files" for entry class. In this file it contains structu of act_info and
// act_entry. The reason why I created struct act_info is to make easier to organize
// when insert in the private data member in act_entry, compare to write one by one
// in the private member which later can also make the argument really long for
// the class function.

#include <cstring> 
#include <cctype>
#include <iostream>


const int SIZE = 500;

// List  of data member that required by act_entry class. The purpose to make it
// more organized.
struct act_info
{
	// The constructor and deconstructor included in struct.
	act_info();
	~act_info();
	char * name;
	char * description;
	char * location;
	int rating;
	char * requirement;
	char * add_info;
};
	
// Class that will perform create entry, copy, retrieve, etc. The purpose is to 
// make easier later on when dealing with the entry in the node.
// No constructor and deconstructor required because already been initialized and
// deallocated by the structu itself.
class act_entry
{
	public:
		int create_entry(act_info & new_entry);
		int copy_entry(const act_entry & new_entry);
		int retrieve(char * location, act_entry & found);
		int display(void);
		int compare_entry (char * location);

	private:
		act_info activity;
};
