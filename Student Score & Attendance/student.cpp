// JONATHAN HARIJANTO, CS 163 ASSIGNMENT #1 , KARLA FANT

// The purpose of this program is to store, update and isplay students data. This application// is created to help the professor to easily see the list of his/ her students complete
// with the score and attendance information. This function used 2 linked list, one for
// sort the student based on the last name and the other is to sort the student based
// on their proficiency score. It is purporsely created 2 linked list so that more easily
// organize the database and prevent overlapping. 

#include "student.h" 

using namespace std;

// Prototypes
int choices (scores & my_scores);
int questions (scores & my_score);
int updates (scores & my_score);
bool again();
void function_call(int value);

int main()
{

	// define the object of the classes
	scores my_score;

	int answer;
	// A simple loop to begin the program with; either can continue or exit!
	do
	{	
		cout << endl << "WELCOME TO STUDENT DATA ORGANIZER!" << endl << endl;
		cout << "Press 1 to continue OR Press 2 to exit! Enter here: ";
		cin >> answer;
		cin.ignore (100 , '\n');
		if (answer == 1)
			// A function that takes the input of choices from user
			// and processing it according to what the user want
			choices (my_score);
		else if (answer == 2)
			return 0;
	} while (again ());


}

// Function that will ask the user to input reply "1 , 2 , 3, 4, or 5". If the user 
// press 1 then it will asked the user several questions to be stored in data based. If
// the user type 2 then it will asked the user what kind of scores need to  be updated.
// If the user type 3 then it will display all the list of students that the user
// just entered. If the user type 4 then it will display the students only with the
// certain proficiency score that the user wanted to see. Lastly if the user type 5
// then it will output a variety of comment based on the proficiency score and it will
// also show the list of students that fall under that comment category.
// Also, if user doesnt enter 1, 2, 3, 4 or 5 then the program will keep ask!
int choices(scores & my_score)
{
	int reply;
	int var;

	do
	{
		cout << endl << endl;
		cout << "Welcome to the the FRONT PAGE MAIN MENU !!" << endl;
		cout << "Press 1 to insert data" << endl;
		cout << "Press 2 to update data" << endl;
		cout << "Press 3 to display all" << endl;
		cout << "Press 4 to display based on proficiency score" << endl;
		cout << "Press 5 to display the evaluation on proficiency score" << endl;
		cout << "Enter your reply here: ";
		cin >> reply;
		cin.ignore(100 , '\n');
		cout << endl ;
		if (reply == 1)
		{
			do
			{
				// call the function and catch the value at the same time.
				function_call (questions(my_score));

			} while (again ());
			
			
		}
		else if (reply == 2)
		{
			// call the function and catch the value at the same time
			function_call (updates (my_score));
		}
		else if (reply == 3)
		{
			// call the function and catch the value at the same time
			cout << endl;
			cout << "These are the list of students that you currently have: " << endl << endl;
			function_call (my_score.display());
		}
		else if (reply == 4)
		{
			// call the function and catch the value at the same time
			int number;
			cout << "Enter the score of proficiency test to see the list of students who get the score (Remember! U = 0, IP = 1, P = 2, E = 3): ";
			cin >> number;
			cin.ignore (100, '\n');
			cout << endl;
			function_call (my_score.display(number));
		}
		else if (reply == 5)
		{
			// call the function and catch the value at the same time
			int number;
			cout << "Enter the proficiency scores you want to see with the evaluation (Remember! U = 0, IP = 1, P = 2, E = 3): ";
			cin >> number;
			cin.ignore (100, '\n');
			cout << endl;
			function_call (my_score.evaluate (number));
		}
			
	} while ( reply != 1 || reply != 2 || reply != 3 || reply !=4);		
}			

// Function that will ask the user to input more information about a student.
// Starting from name, % attendance, and score. A deep copy performed in this function.
// To enter proficiency score, user must type 0 for U, 1 for IP, 2 for P, and 3 for E.
int questions(scores & my_score)
{
	student_data temp;
	char alt [SIZE];
	cout << "Enter the student's first name: ";
	cin.get(alt, SIZE, '\n');
	cin.ignore (100, '\n');
	dynamic_copy (temp.first_name, alt);
	cout << "Enter the student's last name: ";
	cin.get(alt, SIZE, '\n');
	cin.ignore(100, '\n');
	dynamic_copy (temp.last_name, alt);
	// U = 0, IP = 1, P = 2, E = 3
	cout << "Enter the student's profficiency score (U = 0, IP = 1, P = 2, E = 3): ";
	cin >> temp.student_score.prof_score;
	cin.ignore (100, '\n');
	cout << "Enter the student's lab attedance percentage: ";
	cin >> temp.lab_att;
	cin.ignore (100, '\n');
	cout << "Enter the student's program 1 score: ";
	cin >> temp.student_score.prog1_score;
	cin.ignore(100, '\n');
	cout << "Enter the student's program 2 score: ";
	cin >> temp.student_score.prog2_score;
	cin.ignore(100, '\n');
	cout << "Enter the student's program 3 score: ";
	cin >> temp.student_score.prog3_score;
	cin.ignore(100, '\n');
	cout << "Enter the student's program 4 score: ";
	cin >> temp.student_score.prog4_score;
	cin.ignore(100, '\n');
	cout << "Enter the student's program 5 score: ";
	cin >> temp.student_score.prog5_score;
	cout << "Enter the student's Mid-term Exam score: ";
	cin >> temp.student_score.mid_score;
	cin.ignore(100, '\n');
	cout << "Enter the student's Final Exam score: ";
	cin >> temp.student_score.final_score;
	cin.ignore(100 , '\n');
	// Call a function insert at the end, to pass the data that just input
	// by the user to a new node.
	my_score.insert(temp);
	return 1;
	
}

// Function that will ask the user which student that the user want to update the score.
// Will ask user, after type the student's name, to enter the new scores. If no updates
// simply user can type the same score like he/she typed before.
int updates (scores & my_score)
{
	student_data temp;
	char alt [SIZE];
	cout << endl;
	cout << "Enter the student name you want to find & update: " << endl << endl;
	cout << "Enter the student's first name: ";
	cin.get(alt, SIZE, '\n');
	cin.ignore(100, '\n');
	dynamic_copy (temp.first_name, alt);
	cout << "Enter the student's last name: ";
	cin.get(alt, SIZE, '\n');
	cin.ignore(100, '\n');
	dynamic_copy (temp.last_name, alt);
	cout << endl << endl;
	cout << "Enter the updated score from proficiency to finals here: " << endl << endl;
	// U = 0, IP = 1, P = 2, E = 4
	cout << "Enter the student's profficiency score (U =0, IP = 1, P = 2, E = 3):";
	cin >> temp.student_score.prof_score;
	cin.ignore (100, '\n');
	cout << "Enter the student's lab attendance percentage: ";
	cin >> temp.lab_att;
	cin.ignore (100, '\n');
	cout << "Enter the student's program 1 score: ";
	cin >> temp.student_score.prog1_score;
	cin.ignore(100, '\n');
	cout << "Enter the student's program 2 score: ";
	cin >> temp.student_score.prog2_score;
	cin.ignore(100, '\n');
	cout << "Enter the student's program 3 score: ";
	cin >> temp.student_score.prog3_score;
	cin.ignore(100, '\n');
	cout << "Enter the student's program 4 score: ";
	cin >> temp.student_score.prog4_score;
	cin.ignore(100, '\n');
	cout << "Enter the student's program 5 score: ";
	cin >> temp.student_score.prog5_score;
	cout << "Enter the student's Mid-term Exam score: ";
	cin >> temp.student_score.mid_score;
	cin.ignore(100, '\n');
	cout << "Enter the student's Final Exam score: ";
	cin >> temp.student_score.final_score;
	cin.ignore(100, '\n');
	// Call function update here to take the data that just input by the user
	// and store it in a node so that can be replaced later in the update
	// function.
	my_score.update(temp);
	return 1;

}

bool again ()
{
	char response;
	cout << "Do you want to continue? (Y/N)? ";
	cin >> response;
	cin.ignore(100, '\n');
	if (toupper (response) == 'Y')
		return true;
	else
	{
		cout << "Thank you!" << endl;
		return false;
	}
}

// Function that will catch the value return from a function, then will tell whether that functions performs like what the programmers
// wanted or not. This is more like a test function.	
void function_call (int value)
{
	if (value != 0)
		cout << endl << "----- Function Success!! ----- " << endl;
	else
		cout << endl << "----- Function sucess ----- " << endl;
}
