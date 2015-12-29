// JONATHAN HARIJANTO, CS163 ASSIGNMENT #2

#include "trivia_entry.h"

// This is the .h files for stack, where it contains a stack node structure and class
// named stack which have functions of display all that will display everything in the
// array inside the linear linked list, peek which a function to see what is the next
// questions will contain, push function that will put the data into an array inside of the
// node and pop to remove the data from the array inside of the node. FYI, stack is 
// first in last out principle. Last but not lease, is_empty function which will check
// whether the list is empty or not.

struct s_node
{
	card_entry * entry;
	s_node * next;
};


class stack
{
	public:
		stack (void);
		~stack (void);
		int display_all (void);
		int peek (card_entry & top_deck);
		int push (const card_entry & add_card);
		int pop (card_entry & popped);
		bool is_empty();
	private:
		s_node * head;
		int top_index;

};
