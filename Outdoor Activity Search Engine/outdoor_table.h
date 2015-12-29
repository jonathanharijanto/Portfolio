// JONATHAN HARIJANTO CS 163 HW ASSIGNMENT # 3

// This is the ".h files" for table data structure. It contains the structure of
// node and also the class of table. 

#include "outdoor_entry.h"


struct node
{
	act_entry entry;
	node * next;
};

class table
{
	public:
		// Set the value of the table size at the constructor
		table(int size = 5);
		~table(void);
		int insert(char * location, const act_entry & add);
		int load_data (const char * filename);
		int retrieve(char * location, act_entry & found);
		int display(char * location);
		int display_all(void);
		int remove (char * location);
	private:
		int hash_function (char * location);
		// Pointer to a pointer to the hash_table 
		node ** hash_table;
		int hash_table_size;
};
		
