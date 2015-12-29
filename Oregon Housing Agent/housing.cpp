// JONATHAN HARIJANTO, HW ASSIGNMENT #5, CS162
// The purpose of this program is to be sort of 'house listing' search
// engine like "craiglist" but this is the much simpler type.
// The user will be asked to enter whether they want to search specific
// category (size of house, price or # of bedrooms, even location)
// or just want to see all the house listing.
// If the user choose display all, it means the program will show
// all of the house list available complete with the price, size, etc
// However, if the user wants to search more specific, the program will ask
// which category the user wants to be specific (price, size, feature, location)
// For price , size and # of bedroom, the user will be given a max and min
// range so that the search result can be more specific.
// After the data input by the user match with the category in the data
// it will print and show to the user. But if the program can't find
// what the user want it will show blank and ask to continue.



// Include the file 'cs162_hw4_list.cpp' so that no need to re-write all
// in this file. More simple!
#include "housing.h"

bool answer();

int main()
{
    //Variables
    int reply;

    //Object of the class
    housing findHouse;

    //Call the member functions
    findHouse.load_data("housing_list.txt");
    do
    {
      cout << endl;
      cout << "WELCOME TO OREGON HOUSING AGENT!" << endl;
      cout << "We will help you find the best housing!!" << endl<< endl << endl;
      reply= findHouse.choice();
      if (reply == 1)
      {
	  cout << endl;
          findHouse.prioritize();
      }
      else if (reply == 2)
      {
          cout << endl;
	  cout << "HERE'S WHAT WE CAN FIND FOR YOU! " << endl;
	  cout << "-------------------------------- " << endl << endl;
          findHouse.display_all();
      }

     } while (answer());

     return 0;
}

// will return true if reponse 'Y'
// will print 'thank you' and return false if response other than 'Y'
bool answer()
{
     char response;
     cout << "Do you want to continue? (Y/N): ";
     cin >> response;
     cin.ignore (100, '\n');
     if (toupper(response) == 'Y')
         return true;
     else
     {
         cout<< "Thank you!"<<endl;
         return false;
     }
}
