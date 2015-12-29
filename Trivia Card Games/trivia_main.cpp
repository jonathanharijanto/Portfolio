// JONATHAN HARIJANTO, CS163 HW ASSIGNMENT #2
// THE PURPOSE OF THIS PROGRAM IS TO PRACTICE USING STACK AND QUEUE BY CREATING SORT OF A CARD GAME.
// First the player is asked either want to answered trivial questions from unasnwered deck or discarded deck. If the user choose
// discarded deck but is empty then the user will be directed automatically to the unasnwered deck. In answered deck the user will be asked
// a simple trivial questions, if can answered it then the card will be put in the bottom of the deck and user will be asked again 
// to answered in discarded or unasnwered deck. However if the user answer is wrong, then the questions will be remove from uanswered deck
// using dequeue and put "always on top" on the discarded deck using stack function push. Now if the user choose discarded deck and he/she correct
// then the question will be discarded using pop function from stack to be removed from both discarded and answered deck. However if the user
// still answer incorrectly from the discarded deck, then the card will still be put back on top of the discarded card using pop function.
// For every correct answer, user will get +1 score and if user reach the score of 5, the game will tell "congratulation" and exit the game.


#include "trivia_queue.h"

using namespace std;

// Prototypes
bool again();
int choices();
int unanswered_deck(queue & q_card, stack & s_card, card_entry & card, int & player_score);
int discarded_deck(queue & q_card, stack & s_card, card_entry & card, int & player_score);
void function_test (int value);

const int SIZE = 100;

int main ()
{	
	
	queue q_card;
	stack s_card;
	card_entry card;
	q_card.load_entry("trivial.txt");
	int player_score = 0;

	cout << endl << "WELCOME TO TRIVIAL CARD GAMES! " << endl;
	
	do 
	{
		int the_answer;
		the_answer = choices();
		if (the_answer== 1)
			function_test (unanswered_deck(q_card, s_card, card, player_score));
		else if (the_answer == 2)
			function_test (discarded_deck(q_card, s_card, card, player_score));
		if (player_score == 5)
			cout << "Congratulation! You win the game! " << endl;


	} while (again () && (player_score < 5));

	cout << "List of cards in unasnwered deck: " << endl; 
	q_card.display_all();
	cout << endl << "List of cards in discarded deck : " << endl;
	s_card.display_all();

	
	cout << "Thank you for playing! " << endl;
	
	return 0;
}

// Function that will ask user to either answer choice # 1 or # 2
int choices()
{
	int reply;
	cout << "Do you want to draw an unanswered deck or discarded deck?" << endl;
	cout << "Type 1 for unanswered deck or type 2 for discarded deck: ";
	cin >> reply;
	cin.ignore(100, '\n');
	return reply;
}
	
// Function for unanswered deck, first will dequeue a card from the deck and reveal the question to the user. If user answered correctly then will
// be enqueue back to CLL but to bottom of deck. If user answered incorrectly then will be push or "moved" to discarded deck.  User also will get + 1 pts
// for every correct answer.
int unanswered_deck(queue & q_card, stack & s_card, card_entry & card, int & player_score)
{
	char * answer;
	char temp [SIZE];
	cout <<  "You are now drawing a card from an unanswered deck" << endl;
	function_test(q_card.dequeue(card));
	function_test(card.display_question());
	cout << "Your answer is: ";
	cin.get(temp, SIZE, '\n');
	cin.ignore(100, '\n');
	answer = new char [strlen (temp) + 1];
	strcpy (answer, temp);
	if (card.verify(answer))
	{
		cout << "You are correct! " << endl;
		function_test(q_card.enqueue(card));
		cout << "Your point is : " << ++ player_score << " ";
	}
	else 
	{	
		cout << "You aren't correct! " << endl;
		function_test(s_card.push(card));
	}		

	return 1;	
}

// Function for discarded deck, first will check if the deck empty it will redirect to the unanswered deck. However if the deck exist, user can see the question first
// and have the rights to take the question or change to unanswered deck. If the user answer correctly, he/she will get + 1 pts then the card will be pop which mean
// will be removed from the discarded deck. However if the user is wrong, then it will be put back to top of the discarded deck.
int discarded_deck(queue & q_card, stack & s_card, card_entry & card, int & player_score)
{
	cout << "You are now drawing a card from a discarded deck" << endl;
	int value;
	if (s_card.is_empty())
	{
		cout << "Sorry but the discarded deck is now empty, you will be directed to unanswered deck! " << endl;
		function_test(unanswered_deck(q_card, s_card, card, player_score));
	}
	else
	{
		function_test(s_card.peek (card));
		function_test(card.display_question());
		cout << endl << "Do you want to answer this question or choose the other deck? (choose 1 to answer this deck or choose 2 to answer the other deck): " << endl;
		cin >> value;
		cin.ignore(100, '\n');	
		if (value == 1)
		{
			char * answer;
			char temp [SIZE];
			function_test(s_card.pop(card));
			function_test(card.display_question());
			cout << "Your answer is: ";
			cin.get(temp, SIZE, '\n');
			cin.ignore(100, '\n');
			answer = new char [strlen (temp) + 1];
			strcpy (answer, temp);
			if (card.verify(answer))
			{	
				cout << "You are correct! " << endl;
				cout << "Your point is: " << ++ player_score << " ";
			}
			else
			{	
				cout << "You aren't correct! " << endl;
				function_test(s_card.push(card));
			}
		}
		else if (value == 2)
			function_test(unanswered_deck(q_card, s_card, card, player_score));
	}

	return 1;
}

// Function that will ask whether the user want to continue or not. Will return true if yes and return false if answere no.
bool again()
{
	char response;
	cout << "Do you want to continue? (Y/N)";
	cin >> response;
	cin.ignore(100 , '\n');
	if (toupper (response) == 'Y')
		return true;
	else
		return false;
}

// Function that will check the function whether it success or not. Every succeed function will return 1 in the end, thus can know
// whether a certain function at certain class perform its job correctly or not. Will print "Function Success" if it gets the value of 1/
void function_test(int value)
{
	if (value == 1)
		cout << "FUNCTION SUCCESS " << endl;
	else
		cout << "FUNCTION FAILED " << endl;
}
