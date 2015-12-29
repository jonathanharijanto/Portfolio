// JONATHAN HARIJANTO CS163 HW#2

#include "trivia_queue.h"
#include <fstream>

using namespace std;

const int SIZE = 200;

// Costructor of queue, that will set rear to NULL so that it will not contain
// garbage information.
queue::queue(void)
{
	rear = NULL;
}

// Deconstructor of queue that will delete all the node in the CLL by making the CLL
// become a linear linked list first and delete it using traveral.
queue::~queue(void)
{
	q_node * temp = rear -> next;
	q_node * previous = rear -> next;
	rear -> next = NULL;
	while (temp)
	{
		temp = temp -> next;
		delete previous;
		previous = temp;
	}
	previous = NULL;
	rear = NULL;
		 	
}

// Function that will copy the information to a node and then connect the node
// to the CLL. Special case if rear is zero, then it will start to create a new node
// and store the information.
int queue::enqueue (const card_entry & to_add)
{
	if (!rear)
	{
		rear = new q_node;
		rear -> entry.copy_entry(to_add);
		rear -> next = rear;
	}

	else
	{
		q_node * temp = new q_node;
		temp -> entry.copy_entry (to_add);
		temp -> next = rear -> next;
		rear -> next = temp;
		rear = temp;
	}
	
	return 1;
}

// Function that will delete a certain node according to what is pointed.
// Special case if the list is empty then it will exit directly. Another special case
// if the node is the rear it self, then it will delete directly.
int queue::dequeue(card_entry & dequeued)
{
	if (!rear)
		return 0;
	
	else if (rear == rear -> next)
	{
		dequeued.copy_entry(rear-> entry);
		delete rear;
		rear = NULL;
	}
	
	else
	{
		q_node * temp = rear -> next;
		rear -> next = temp -> next;
		dequeued.copy_entry(temp -> entry);
		delete temp;
	}

	return 1;
}

// Function that will load the data from external file to a node. Each one information
// (a question and a node) will be stored in one node, so that will not mixed.
// special case if the external file is empty then it will exit directly.
int queue::load_entry(const char * filename)
{
	rear = NULL;
	card_entry temp_entry;

	char temp_question[SIZE];
	char temp_answer[SIZE];

	ifstream file_in;
	file_in.open (filename);

	if (!file_in)
		return 0;

	else
	{
		file_in.get(temp_question, SIZE, '?');
		file_in.ignore(100, '?');
	
		while (!file_in.eof())
		{

			file_in.get(temp_answer, SIZE, '\n');
			file_in.ignore(100, '\n');

			temp_entry.create_card (temp_question, temp_answer);
			
			enqueue(temp_entry);

			file_in.get(temp_question, SIZE, '?');
			file_in.ignore(100, '?');

		}

		file_in.close();

	}

	return 1;
}

// Function that will display all the information in the CLL. To make it happen
// first the CLL changed into a LLL first then traversed it one by one while displaying
// the information inside the node at the same time. Then after it finish it will 
// reconnect again to become a CLL.
int queue::display_all(void)
{
	q_node * temp = rear -> next;
	q_node * previous = rear -> next;
	rear -> next = NULL;
	while (temp)
	{
		temp-> entry.display();
		temp = temp -> next;
	}
	rear -> next = previous;

	return 1;

}

	
