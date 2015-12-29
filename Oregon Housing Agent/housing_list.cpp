// JONATHAN HARIJANTO, HW ASSIGNMENT # 5, CS162

// Include 'housing.h' so no need to retype all the  class & structs again
#include "housing.h"

//Constructor for struct
housing_data::housing_data()
{
	size= 0;
	rent = 0;
	number = 0;
	location = NULL;
	feature1 = NULL;
	feature2 = NULL;
	feature3 = NULL;
}

//Destructor for struct
housing_data::~housing_data()
{
	if (location)
		delete [] location;
	if (feature1)
		delete [] feature1;
	if (feature2)
		delete [] feature2;
	if (feature3)
		delete [] feature3;
}


//Constructor
housing::housing ()
{

	head = NULL;

}

housing::housing (char filename[])
{

	load_data(filename);

}

//Destructor
housing:: ~housing()
{

	node * current =  head;
	while (head)
	{
		head = head -> next;
		delete current;
		current = head;
	}

}

/* IGNORE THIS!!

Templates: (MEMORIZE!)
char * array;
char temp[SIZE];
cin >> temp;
array = new char[strlen(temp) + 1];
strcpy(array, temp);

*/


// Will gives a choice to user whether want to display all data or choose
// prioritize search
int housing::choice ()
{
     int reply;
     cout << "Do you want prioritize feature or ";
     cout << " display all data available in your searching ?" << endl;
     cout << "-----------------------------------------------------------------------------------" << endl;
     cout << "Press 1 to choose using PRIORITIZE" << endl;
     cout << "Press 2 to DISPLAY ALL LIST" << endl << endl;
     cout << "Enter your choice here: ";
     cin >> reply;
     cin.ignore (100, '\n');
     if ( reply != 1 && reply != 2)
     {
	cout << "You didnt choose properly!" << endl;
	return 0;
     }
     return reply;
}

// will ask user to input the mix and max price they want for the house
// then search from the loaded external data then display it if find the exact one.
void housing::rent()
{
	int min_rent;
	int max_rent;
	node * current = head;
	cout << "Enter the minimum price you are looking for the house: ";
	cin >> min_rent;
	cin.ignore(100, '\n');
	cout << "Enter the maximum price you are looking for the house: ";
	cin >> max_rent;
	cin.ignore(100 ,'\n');
	while(current)
	{
		if ( min_rent <= current->house.rent && current->house.rent <= max_rent)
			display_one(current->house);
		current = current -> next;
	}
}

// will ask user to input the min and max size they want for the house
// then it will search from the loaded external data then display
// it if the program finds the same one.
void housing::size()
{
	int min_size;
	int max_size;
	node * current = head;
	cout << "Enter the minumum size of the house you want: ";
	cin >> min_size;
	cin.ignore(100, '\n');
	cout << "Enter the maximum size of the house you want: ";
	cin >> max_size;
	cin.ignore(100, '\n');
	while (current)
	{
		if ( min_size <= current->house.size && current->house.size <= max_size )
			display_one(current->house);
		current = current -> next;
	}
}

// will ask user to input the min and max # beedroom they want for the house
// the it will search from the loaded external data then display it
// if the program finds the same one.
void housing::number()
{
	int min_number;
	int max_number;
	node * current = head;
	cout << "Enter the minimum # of bedroom in the house: ";
	cin >> min_number;
	cin.ignore(100, '\n');
	cout << "Enter the maximum # of bedroom in the house: ";
	cin >> max_number;
	cin.ignore(100, '\n');
	while (current)
	{
		if (min_number <= current->house.number && current->house.number <= max_number)
			display_one(current->house);
		current = current -> next;
	}

}

// will ask the user which location they want for the house.
// It will compare the string input by the user with the loaded external file
// then will display it if the program find the exact one.
void housing::location()
{
	char location[SIZE];
	node * current = head;
	cout << "Enter the location of the house you want (ex: Portland, Gresham): ";
	cin.get(location, SIZE_LOCATION, '\n');
	cin.ignore(100, '\n');
	while(current)
	{
		if(strcmp (location, current->house.location) == 0)
			display_one(current->house);
		current = current -> next;
	}
}

// wil ask the user what features they want for the house
// It will string compare the string input by the user with the string
// from the  loaded external files and will display it if it finds the 
// exact one. It has features1, features2, features3 to get a wider 
// and more specific search. Pretty similar with "tag search" if in internet/
void housing::feature()
{
	char feature[SIZE];
	node * current = head;
	cout << "Enter the feature you want in the house"
	     << " (ex: fitness center, modern apartment): ";
	cin.get(feature, SIZE_FEATURE, '\n');
	cin.ignore(100,'\n');
	while (current)
	{
		// current -> house.feature1 != NULL
		if ((strcmp(feature, current->house.feature1)== 0) || (strcmp(feature, current->house.feature2) == 0) || (strcmp(feature, current -> house.feature3) == 0))
			display_one(current->house);
		current = current -> next;
	}

}

// will ask the user which one they want to be prioritize
// then ask user to choose the response from 1 to 5
// If user choose 1 then the program will run the function rent
// display it. If choose 2 then the program will run the function size.
// If choose 3, will run function number. Choose 4 will run function location.
// Choose 5 will run function features.
// If choose other than that the program will print error message and quit.
void housing::prioritize ()
{
     int response;
     cout << "Which selection do you want to be prioritize first?" << endl;
     cout << "---------------------------------------------------" << endl;
     cout << "Type 1 for Rent" << endl;
     cout << "Type 2 for housing size" << endl;
     cout << "Type 3 for # of bedrooms " << endl;
     cout << "Type 4 for location" << endl;
     cout << "Type 5 for features" << endl << endl;
     cout << "Enter the number (1 - 5) for your response here: ";
     cin >> response;
     cin.ignore(100, '\n');
     cout << endl;
     if (response == 1)
     {
         rent();
     }
     else if (response == 2)
     {
         size();
     }
     else if (response == 3)
     {
          number();
     }
     else if (response == 4)
     {
          location();
     }
     else if (response == 5)
     {
          feature();
     }
     else
     {
         cout << "You didnt choose properly, the program will exit. Thank you!";
	 cout << endl;
         return;
     }
}

void housing::copy_house(housing_data & destination, housing_data & source)
{
	destination.rent = source.rent;
	destination.size = source.size;
	destination.number = source.number;
	dynamic_copy(destination.location, source.location);
	dynamic_copy(destination.feature1, source.feature1);
	dynamic_copy(destination.feature2, source.feature2);
	dynamic_copy(destination.feature3, source.feature3);
}

void housing::insert (housing_data & house)
{
	node * temp = new node;
	copy_house(temp->house, house);
	temp -> next = head;
	head = temp;
}

void housing::dynamic_copy(char * & destination, char * source)
{
	if (source ==  NULL)
		return;

	if (destination != NULL)
	{
		delete [] destination;
	}

	destination = new char[strlen(source) + 1];
	strcpy(destination, source);
}

//will load the external file into the program
void housing::load_data(const char * filename)
{
    head = NULL;
    housing_data temp_insert;

    char temp[150];

    ifstream file_in;
    file_in.open(filename);

    // condition if failed to load the file, will exit automatically
    if (!file_in)
       return;
    else
    {
       file_in >> temp_insert.rent;
       file_in.ignore(100, ';');

       // will returns true if the previous read/ input operation failed
       // will returns false if the previos read/input operation success
       // that's why give '!' to make sure it will return true if read success
       // if read success will get all the list of class 1 by 1.
       while (!file_in.eof())
       {
	     file_in >> temp_insert.size;
             file_in.ignore(100, ';');

	     file_in >> temp_insert.number;
             file_in.ignore(100, ';');

             file_in.get(temp,SIZE_LOCATION, ';');
             file_in.ignore(100 ,';');
	     dynamic_copy(temp_insert.location, temp);

             file_in.get(temp, SIZE_FEATURE, ';');
             file_in.ignore(100, ';');
	     dynamic_copy(temp_insert.feature1, temp);

             file_in.get(temp, SIZE_FEATURE, ';');
             file_in.ignore(100, ';');
	     dynamic_copy(temp_insert.feature2, temp);

             file_in.get(temp, SIZE_FEATURE, '\n');
             file_in.ignore(100, '\n');
	     dynamic_copy(temp_insert.feature3, temp);

             insert(temp_insert);

	     file_in>> temp_insert.rent;
             file_in.ignore(100, ';');

       }

       file_in.close();
    }
}

// will display all the data available from the loaded external files
// use for loop so return 1-1 for size, rent, number, location and feature
void housing::display_all()
{
     node * current = head;
     while (current)
     {
	cout << "The rent fee is: " << current->house.rent << endl;
	cout << "The size of the place is: " << current->house.size << endl;
	cout << "The number of bed available at that place is: " << current->house.number << endl;
	cout << "It is located at: " << current->house.location << endl;
	cout << "The list of features are: "<< current->house.feature1 << " "
	     << current->house.feature2 << " " << current->house.feature3 <<endl;
	cout << endl << endl;
	current = current -> next;

     }
}

// will only display specific size, rent, number, location and feature 
// according to the value of 'i'
// will not returns all of them like 'display_all'
void housing::display_one(housing_data & a_house)
{
     node * current = head;
     cout << endl;
     cout << "The rent fee is: "<< a_house.rent << endl;
     cout << "The size of the place is: " << a_house.size << endl;
     cout << "The number of bed availabe at that place is: " << a_house.number <<endl;
     cout << "It is located at: " << a_house.location << endl;
     cout << "The list of features are: "<< a_house.feature1 << " "
          << a_house.feature2 << " " << a_house.feature3 <<endl;
     cout << endl;
}
