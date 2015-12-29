// JONATHAN HARIJANTO, HW ASSIGNMENT #1 CS163

// This is the ".h files" that contain #include, constants,
// structures, prototypes and class. The purporse that need to create 
// a separate ".h files" is to make the program look more
// clean and organize. So that main programs will contain
// only the important lines of code and functions.

#include <iostream>
#include <cctype>
#include <cstring>


// Constants
const int SIZE = 20;

// Structure that contain all scores needed for a student
struct score_list
{
	score_list();
	int prof_score;
	float prog1_score;
	float prog2_score;
	float prog3_score;
	float prog4_score;
	float prog5_score;
	float mid_score;
	float final_score;
};

// Structure that contain all the information about student
struct student_data
{
	student_data();
	~student_data();
	char * first_name;
	char * last_name;
	float lab_att;
	score_list student_score;
};

// Structure for a node
struct node
{
	student_data  student;
	node * next;
};

// Class that is going to be used for the program
class scores
{
	public:
		scores();
		~scores();
		int insert (student_data & student);
		int insert_by_score (student_data & student);
		int insert_by_name (student_data & student);
		int update (student_data & student);
		int display ();
		int display (int prof_score);
		int evaluate (int prof_score);	 
	private:
		node * head_name;
		node * head_score;
};

// Prototypes	
void dynamic_copy (char * & destination, char * source);
void copy_student (student_data & destination, student_data & source);
