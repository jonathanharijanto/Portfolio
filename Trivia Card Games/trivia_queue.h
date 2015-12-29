// JONATHAN HARIJANTO, CS163 ASSIGNMENT # 2

#include "trivia_stack.h"

// This is a .h files for queue, it contains a structure of queue node and queue class.
// The class queue contains display all function that will display all the information
// in the circular linked list, load entry that will load the external file to the
// node in the circular linked list. Enqueue to connect a new node in the CLL and last
// is dequeue that will delete a certain node in CLL. FYI, queue is using first in
// first out principle.

struct q_node
{
	card_entry entry;
	q_node * next;
};


class queue
{
	public:
		queue(void);
		~queue(void);
		int display_all (void);
		int load_entry (const char * filename);
		int enqueue(const card_entry & to_add);
		int dequeue(card_entry & dequeued);

	private:
		q_node * rear;

};
