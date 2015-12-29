// JONATHAN HARIJANTO, CS163 HW #2

#include "trivia_entry.h"

using namespace std;

// This is a constructor for card entry, where question and answer are set to null
// so that it will not contain a garbage.
card_entry::card_entry (void)
{
	question = NULL;
	answer = NULL;
}

// A deconstructor that make sure both question and answer will be deallocated after the
// program ends so that will not cause a seg fault.
card_entry::~card_entry (void)
{
	if (question)
		delete [] question;
	if (answer)
		delete [] answer;
}


// Function that will create a new card by undergoing a deep copy from the 
// source question and answer to the destination of question and answer.
int card_entry::create_card (char * question_source, char * answer_source)
{

	// In case that question and answer of destionation is filled with garbage
	// so it must be deallocated first.
	if (question)
		delete [] question;
	if (answer)
		delete [] answer;	

	question = new char [strlen (question_source) + 1];
	strcpy (question, question_source);
	
	answer = new char [strlen (answer_source) + 1];
	strcpy (answer, answer_source);
	
	return 1;
}

// Function that will copy the data of answer and questions from source to destionation
// technically the same with function create card but the difference is this function
// is passed with an argument of the card_entry class itself
int card_entry::copy_entry (const card_entry & copy_from)
{
	if (question)
		delete [] question;
	if (answer)
		delete [] answer;

	if (copy_from.question)
	{
		question = new char [strlen (copy_from.question) + 1];
		strcpy(question, copy_from.question);
	}
	
	if (copy_from.answer)
	{
		answer = new char [strlen (copy_from.answer) +1];
		strcpy (answer, copy_from.answer);
	}

	return 1;
}

// Function that will display the questions only.
int card_entry::display_question(void)
{
	if (question)
		cout << question << "? ";

	return 1;
}

// Function that will display the question and answer at the same time.
int card_entry::display(void)
{
	if (question)
		cout << question;
	if (answer)
		cout << answer;

	return 1;
}

// Function that will check whether the answer from the user to a certain question
// is the same with the real answer or not. If yes it will return true. Capital letter
// and small letter does matter, all answer must be answered in small letter.
bool card_entry::verify(char * user_answer){
	if (strcmp (user_answer, answer) == 0)
		return true;
	else
		return false;

	return 1;
}
