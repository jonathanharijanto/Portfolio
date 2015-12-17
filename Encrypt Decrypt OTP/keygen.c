// HW PROGRAM 4 - CS 344 created by Jonathan Harijanto
// Some of these codes are inspired from TAs, Ben's slide and reference link, and Stackoverflow
//
// This file is "keygen.c". It will create key file of specified length, and key generated based on 
// random char from 27 allowed character only (alphabets + blank space). When completes, it will output
// to stdout.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {

	// Check whether argument passed correctly or not
	if (argc < 2) {
		printf("Usage: kegen keyLength\n"); 
		exit(1);
	} else {
		// Generate random number seed.
		srand(time(NULL)); 
		int i; 
		int key_length = atoi(argv[1]); 
		char randChar; 
		// Initialize char array to store the key
		char newKey[key_length+1]; 
		
		// Loop that will generate random key char based on the specified length
		// and store it to new defined char array
		for (i = 0; i < key_length; i++){ 
			randChar = "ABCDEFGHIJKLMNOPQRSTUVWXYZ "[random () % 27];
			newKey[i] = randChar; 
		}

		// Add null terminate at the end of the message
		newKey[key_length] = 0; 
		// print the output to stdout
		printf("%s\n", newKey); 
	}

	return 0;
}
