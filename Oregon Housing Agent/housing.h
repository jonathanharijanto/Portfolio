// JONATHAN HARIJANTO, HW ASSIGNMENT # 5 , CS162
// This is the '.h' files that contains #include, using namespace
// constants, structure and also class
// The purpose making it seperate into 3 files '.h' and '.cpp'
// is no other than to have a good practice so that 1 file will not
// contain a bunch of different code, and also I believe in this way
// the code looks neat and nice!

#include <iostream>
#include <cctype>
#include <cstring>
#include <fstream>

using namespace std;

const int SIZE_LOCATION = 150;
const int SIZE_FEATURE = 150;
const int SIZE_FILENAME = 150;
const int SIZE = 150;



// Defining the structure name 'housing data'. Noticed that for
// location and feature1-3, they are using pointer dyanmically allocated array
// because their size of array can be changing anytime, so it is better
// to use dynamically allocated array so that can have flexible size array.
struct housing_data
{
       int rent;
       int size;
       int number;
       char * location;
       char * feature1;
       char * feature2;
       char * feature3;
       housing_data();
       ~housing_data();
};

struct node
{
	housing_data house;
	node * next;
};

// Defining class name 'housing'. The public contains all of my
// function that are going to be used later in 'cs162_hw4_list.cpp'
class housing
{
      public:
        housing(char filename[]);
        housing();
        ~housing();
        void prioritize();
        void display_all();
        int choice();
        void rent();
        void size();
        void number();
        void location();
        void feature();
        void load_data(const char * filename);
        void display_one(housing_data & a_house);
	void insert(housing_data & house);
	void dynamic_copy(char * & destination, char * source);
	void copy_house (housing_data & destination, housing_data & source);

      private:
	node * head;
};
