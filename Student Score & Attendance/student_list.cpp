// JONATHAN HARIJANTO, HW ASSINGMENT #1 CS163

// This is the "list.cpp" files that contain all the 
// functions that will be used in the main program. All of
// these functions use from the class named "score" and struct
// student_data from ".h files" that already been declared before.
// It is written in list.cpp files so that main will not contain
// a lot of functions.

#include "student.h"

using namespace std;


// Constructor for student_data, set everything to 0 / NULL
student_data::student_data()
{
	first_name = NULL;
	last_name = NULL;
	lab_att = 0;
}

// Deconstructor for student data, deallocate dynamically allocated 
// array
student_data::~student_data()
{	if (first_name)
		delete [] first_name;
	if (last_name)
		delete [] last_name;
}

// Constructor for score list, set everything to 0
score_list::score_list()
{
	prof_score = 0;
	prog1_score = 0;
	prog2_score = 0;
	prog3_score = 0;
	prog4_score = 0;
	prog5_score = 0;
	mid_score = 0;
	final_score =0;
}

// Constructor for class score, allocate all head to NULL
scores::scores()
{
	head_name = NULL;
	head_score = NULL;
}


// Deconstructor for class scores, deallocate both head after the program ends
scores::~scores()
{
	node * current = head_name;
	while (head_name)
	{
		head_name = head_name -> next;
		delete head_name;
		current = head_name;
	}

	current = head_score;
	while (head_score)
	{
		head_score = head_score -> next;
		delete head_score;
		current = head_score;
	}
}
	
// A main insert function that contain 2 simpler insert function,
// which are insert by name and by score that going to take the lists of// data from the user  and store it into a node. Thus it takes the
// data from structure student as the argument to be passed in.
int scores::insert (student_data & student)
{
	insert_by_name(student);
	insert_by_score(student);
	return 1;
}

// An insert function that will store all the input from the user into a// node. It takes student structure as the argument,
// so that the information can be passed in into this function. 
// This insert by score is make a completely different list
// than insert by name because it will make sorting by score easier.
int scores::insert_by_score (student_data & student)
{
	node * temp = new node;
	copy_student (temp -> student, student);
	// Check whether head is pointing to null or not
	if (!head_score)
		head_score = temp;

	node * current = head_score -> next;
	node * previous = head_score;

	// Check if head is pointing to the value which is bigger
	// than the value pointed by temp.
	if (head_score -> student.student_score.prof_score < temp -> student.student_score.prof_score)
	{
		temp -> next = head_score;
		head_score = temp;
	}
	else
	{
		// Check if current not yet null and value pointed 
		// by current is smaller than the pointed by temp.
		while (current && current -> student.student_score.prof_score < temp -> student.student_score.prof_score)
		{
			previous = current;
			current = current -> next;
		}
		previous -> next = temp;
		temp -> next = current;
	}
	return 1;
}

// An insert function that will store the information passed from 
// the argument into a node. It is different with insert by score
// because this function create a new link list. This list is created
// so that the program can sort by name easily without getting mixed
// up with sort by score.
int scores::insert_by_name (student_data & student)
{
	node * temp = new node;
	copy_student (temp -> student, student);
	// Check if head points to a null
	if (!head_name)
		head_name = temp;

	node * current = head_name -> next;
	node * previous = head_name;

	// Check using string compare whether the value pointed by
	// temp need to be place before or after the value pointed
	// by head.
	if (strcmp (temp -> student.last_name, head_name -> student.last_name) < 0)
	{
		temp -> next = head_name;
		head_name = temp;
	}
	// Check using string compare whether the value pointed by
	// temp need to be place before or afterthe value pointe
	// by current.
	else
	{
		while (current && strcmp (current -> student.last_name, temp -> student.last_name) < 0 )
		{
			previous = current;
			current = current -> next;
		}
		previous -> next = temp;
		temp -> next = current;
	}
	return 1;
	
}

// Function that display the list of the data inputted by the user
// based on the proficiency score, thus pass the value of prof. score
// as the argument.
int scores::display(int prof_score)
{
	node * current = head_score;
	int number = prof_score;
	// Check whether head is pointing to NULL or not.
	if (!head_score)
		return 0;

	while (current)
	{
		// Check if the value pointed by current is equal with
		// the number passed from the function match or not.
		if (current -> student.student_score.prof_score == number)
		{
			cout << "First name: " << current -> student.first_name << endl;
			cout << "Last name: " << current -> student.last_name << endl;
			cout << "Lab attendance percentage: " << current -> student.lab_att << " %" << endl;
			cout << "Proficiency score: " << current -> student.student_score.prof_score << endl;
			cout << "Program 1 to 5 scores: " << current -> student.student_score.prog1_score << " , " << current -> student.student_score.prog2_score << " , " << current -> student.student_score.prog3_score << " , " << current -> student.student_score.prog4_score << " , " << current -> student.student_score.prog5_score << endl;
			cout << "Midterm score: " << current -> student.student_score.mid_score << endl;
			cout << "Final score: " << current -> student.student_score.final_score << endl;
			cout << endl;
		}
		current = current -> next;
	}
	return 1;
		
}

// Function that will replace the data that already been input by the user in the list before, with the new updates that the user just entered.
// Since there are two insert function, thus update both (insert by name & by score) is required!
int scores::update(student_data & student)
{
	node * current = head_score;
	// Check if head is pointing to NULL or not.
	if (!head_score)
		return 0;
	while (current)
	{
		// Check if the value pointed by current pointer, with the data that just entered by the user is the same or not.
		if (strcmp (current -> student.first_name, student.first_name) == 0 && strcmp (current -> student.last_name, student.last_name) == 0)
		{
			current -> student.student_score.prog1_score = student.student_score.prog1_score;
			current -> student.student_score.prog2_score = student.student_score.prog2_score;
			current -> student.student_score.prog3_score = student.student_score.prog3_score;
			current -> student.student_score.prog4_score = student.student_score.prog4_score;
			current -> student.student_score.prog5_score = student.student_score.prog5_score;
			current -> student.student_score.mid_score = student.student_score.mid_score;
			current -> student.student_score.final_score = student.student_score.final_score;
		}
		current = current -> next;
	}
			
	
	current = head_name;
	// Check if head is pointing to NULL or not.
	if (!head_name)
		return 0;
	while (current)
	{
		// Check if the value pointed by current pointer, with the data that just entered by the user is the same or not.
		if (strcmp (current -> student.first_name, student.first_name) == 0 && strcmp (current -> student.last_name, student.last_name) == 0)
		{
				
			current -> student.student_score.prog1_score = student.student_score.prog1_score;
			current -> student.student_score.prog1_score = student.student_score.prog1_score;
			current -> student.student_score.prog2_score = student.student_score.prog2_score;
			current -> student.student_score.prog3_score = student.student_score.prog3_score;
			current -> student.student_score.prog4_score = student.student_score.prog4_score;
			current -> student.student_score.prog5_score = student.student_score.prog5_score;
			current -> student.student_score.mid_score = student.student_score.mid_score;
			current -> student.student_score.final_score = student.student_score.final_score;
		}
		current = current -> next;
	}
	return 1;
			
}

// This function will gives different comment for each value of proficiency test score entered.
// Then it will also call the display function, to show who are the students that fall into that category. 
int scores::evaluate (int prof_score)
{
	if (prof_score == 0)
	{
		cout << "These are the students that don't pass the proficiency test: "<< endl << endl;
		display (prof_score);
	}
	else if (prof_score == 1)
	{
		cout << "These are the students that nearly not pass the proficiency test: "<< endl << endl;
		display (prof_score);
	}
	else if (prof_score == 2)
	{
		cout << "These are the students that pass the proficiency test: " << endl << endl;
		display (prof_score);
	}
	else if (prof_score == 3)
	{
		cout << "These are the students that exceed the proficiency test: " << endl << endl;
		display (prof_score);
	}
	return 1;

}

// A simple display function that will show all of the information of the student that already been entered by the user.
// This function is more likely a "print all" function in the list.
int scores::display()
{
	node * current = head_name;
	while (current)
	{
		
		cout << "First name: " << current -> student.first_name << endl;
		cout << "Last name: " << current -> student.last_name << endl;
		cout << "Lab attendance percentage: " << current -> student.lab_att << " %" << endl;
		cout << "Proficiency score: " << current -> student.student_score.prof_score << endl;
		cout << "Program 1 to 5 scores: " << current -> student.student_score.prog1_score << " , " 
		<< current -> student.student_score.prog2_score << " , " << current -> student.student_score.prog3_score 
		<< " , " << current -> student.student_score.prog4_score << " , " 
		<< current -> student.student_score.prog5_score << endl;
		cout << "Midterm score: " << current -> student.student_score.mid_score << endl;
		cout << "Final score: " << current -> student.student_score.final_score << endl;
		cout << endl;
		current = current -> next;
	}
	return 1;
}


// A function helper that will help to do a deep copy from the source to destination. So it will help the programmer
// to not hard code make a new dynamically allocated array all the time, simply can just call this function.
// It is important to check both source and destination whether it is null or not.
void dynamic_copy (char * & destination, char * source)
{
	// If nothing to copy, then exit funtion
	if (source == NULL)
		return;
	// If some data / garbage already exist, delete it first to prevent memory leak.
	if (destination == NULL)
		delete [] destination;
	destination = new char [strlen (source) + 1];
	strcpy (destination, source);
}

// Another helper function, will copy the data from the source file to the destination file. This helps the programmer
// to not type one by one if one to copy all the data members in the structs student_file.
void copy_student (student_data & destination, student_data & source)
{
	dynamic_copy(destination.first_name, source.first_name);
	dynamic_copy(destination.last_name, source.last_name);
	destination.lab_att = source.lab_att;
	destination.student_score.prof_score = source.student_score.prof_score;
	destination.student_score.prog1_score = source.student_score.prog1_score;
	destination.student_score.prog2_score = source.student_score.prog2_score;
	destination.student_score.prog3_score = source.student_score.prog3_score;
	destination.student_score.prog4_score = source.student_score.prog4_score;
	destination.student_score.prog5_score = source.student_score.prog5_score;
	destination.student_score.mid_score = source.student_score.mid_score;
	destination.student_score.final_score = source.student_score.final_score;
}	
