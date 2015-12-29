// JONATHAN HARIJANTO CS 163 HW # 2

#include "trivia_stack.h"

const int MAX = 5;

// Constructor for stack which will set head to NULL and top_index to zero so that
// will not contain garbage information
stack::stack(void)
{
	head = NULL;
	top_index = 0;
}

// Deconstructor for stack that will delete all the nodes in the linear linked list
// however, need to be noticed that the array must be deallocated first before 
// delete the node.
stack::~stack(void)
{
	s_node * current = head;
	while (head)
	{
		head = current -> next;
		delete [] current -> entry;
		delete current;
		current = head;
	}	
}

// Function that will display all the information in the array inside of every node
// however if the list is empty it will return directly.
int stack::display_all (void)
{
	if (!head)
		return 0;
	s_node * current = head -> next;
	for (int i = 0; i < top_index; ++ i)
		head -> entry[i].display();
	while (current)
	{
		for (int i = 0; i < MAX; ++i)
			current -> entry[i].display();
		current = current -> next;
	}
	
	return 1;
}

// Function that will see the last information in the array inside of the node
int stack::peek (card_entry & top_deck)
{
	if (head)
	{
		top_deck.copy_entry(head->entry[top_index -1]);
		return 1;
	}
	else
		return 0;
}

// Function that will insert an information (question and answer) to the array
// inside of the node. Special case is given, if the list is empty, it will
// create a new node and array then will store the data into it. Also if the 
// array cant contain new information anymore, it will create a new node.
int stack::push (const card_entry & add_card)
{
	if (!head)
	{
		head = new s_node;
		head -> entry = new card_entry[MAX];
		head -> next = NULL;
		top_index = 0;
		head -> entry[top_index].copy_entry(add_card);
		++ top_index;
	}
	
	else if (top_index >= MAX)
	{
		top_index = 0;
		s_node * temp = new s_node;
		temp -> entry = new card_entry[MAX];
		temp -> next = head;
		head = temp;
		head -> entry[top_index].copy_entry(add_card);
		++ top_index;
	}

	return 1;

}

// Function that will delete the information in one of the array inside the 
// node. Special case is given if the list is empty then it will return directly.
// However if the list is not empty, this function will go to the specific location
// that the user want to remove that information.
int stack::pop (card_entry & popped)
{
	if (!head)
		return 0;
	-- top_index;

	if (top_index < 0)
	{
		s_node * current = head;
		head = current -> next;
		delete [] current -> entry;
		delete current;
		current = NULL;
		top_index = MAX;
	}

	return 1;
}

// Function that will check whether the list of stack is empty or not
// it the list will empty it will return true which later on in the main file
// it will tell the user that the list is empty.
bool stack::is_empty()
{
	if (!head || (head -> next == NULL && top_index == 0))
		return true;
	else
		return false;
}
