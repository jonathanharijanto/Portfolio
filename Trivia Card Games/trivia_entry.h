// JONATHAN HARIJANTO, CS163 ASSIGNMENT # 2

// This is a .h file for entry which contain all the #include and also a class
// name card entry. In this class it contains create card display card, copy entry 
// and verify. create card means to create a card that contains a question with the
// help of copy entry, that copies the data using deep copy. Display question
// will only show the question instead of the answer too. Verify is a function
// that will make sure whether the user answer will be the same or not.


#include <cstring>
#include <cctype>
#include <iostream>

class card_entry
{
	public:
		card_entry (void);
		~card_entry (void);
		int create_card (char * question_source, char * answer_source);
		int display (void);
		int display_question(void);
		int copy_entry (const card_entry & copy_from);
		bool verify (char * user_answer);
	private:
		char * question;
		char * answer;
};
