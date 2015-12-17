// HW PROGRAM 4 - CS 344 created by Jonathan Harijanto
// Some of these codes are inspired from TAs, Ben's slide and reference link, and Stackoverflow
//
// This file is "otp_enc_d.c". This program will run in bg as daemon. Basically it will encrypt a 
// plainttext into ciphertext when passed with plaintext and key. First, it will listen to 
// certain port then receive plaintext and key if the connection is successfully made. If
// connection not successful, error message will appear. Then it will return the ciphertext
// to the "otp_enc.c" 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h> // letter to number conversion
#include <sys/wait.h>
#include <fcntl.h>	

#define BUFSIZE 1024 // Controls the length of all string buffers


// Function that converts char values to integers
int charToInt(char c) {
	if (c == ' ') {
		return 26;
	} else {
		return (c - 'A');
	}
	return 0;
}

int main(int argc, char *argv[]) {

	// Initialize socket file descriptor, port, length of client address, and both
	// client and server address strct
    	int sockfd;
	int client_sockfd;
	int port_number; 
	socklen_t client_length; 
    	char recvbuf[BUFSIZE];
	char sendbuf[BUFSIZE]; 
    	struct sockaddr_in server;
	struct sockaddr_in client; 
    	int n;
	int i;

	int pid;
	int status;

	// Check whether argument passed correctly or not
    	if (argc < 2) { 
        	printf("Usage: otp_enc_d listening_port");
        	exit(1);
    	}

	port_number = atoi(argv[1]); 

	// Fill the client socket address struct 
	server.sin_family = AF_INET; // protocol family
    	server.sin_port = htons(port_number); // port number
    	server.sin_addr.s_addr = INADDR_ANY; // autofill local address

	// Create the socket
    	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){  
        	perror("ERROR opening socket.\n");
		exit(1);
    	}
    
    	// Bind socket to the port  
    	if (bind(sockfd, (struct sockaddr *) &server, sizeof(server)) == -1) {
        	perror("Bind call failed.\n");
		exit(1);
    	}

    	// Listen for incoming connections (*5 because up to 5) 
    	if (listen(sockfd, 5)== -1 ) {
		perror("Listen call failed. \n");
		exit(1);
	}


    	// Loop to handle to continously handle 'listening'
    	while (1) {

		// Grab length of client address
	    	client_length = sizeof(client); 

        	// Wait for any connection from the client processes
        	client_sockfd = accept(sockfd, (struct sockaddr *) &client, &client_length);
        	if (client_sockfd < 0) {
            		perror("Accept call failed.\n");
	    		exit(1);
        	}
		
		pid = fork();
		if (pid < 0 ) {
			perror("fork failed!");
			exit(1);
		}

		if (pid == 0) {

    			bzero((char *) &server, sizeof(server)); 
			// Handshaking process: sending first string and also comparing string
			// received. This to verify the right client is trying to use the server 
			read(client_sockfd,recvbuf,sizeof(recvbuf)-1);
			if (strcmp(recvbuf,"enc_handshake")!=0) {
				printf("Connected to the wrong client!");
				char reply[] = "Invalid! Connecting to wrong client";
				write(client_sockfd,reply,sizeof(reply));
				_exit(2);
			} else {
				char reply[]= "handshake_with_enc_d";
				write(client_sockfd,reply,sizeof(reply));
			}
			
			// Read #1 for plain
			// Clear string buffer and read any incoming message from client         	
			bzero(recvbuf, BUFSIZE); 
			n = read(client_sockfd, recvbuf, BUFSIZE); 
			if (n < 0) {
				perror("Read from socket failed.\n");
				exit(1);
			}

			// Attempt to open the file named was in the message
			FILE *fp;
			fp = fopen(recvbuf, "r");
			if (fp == NULL) {
				perror("Open plain text file failed.\n");
				exit(1);	
			}
			
			// Initialize for storage of plaintext that going to be extracted 
			char plaintext[BUFSIZE]; 
			fgets(plaintext, BUFSIZE, fp); 

			// Convert all char in plaintext into uppercase (*for convenient usage only*)
			for (i = 0; i < strlen(plaintext); i++) { 
				plaintext[i] = toupper(plaintext[i]);
			}
			
			// Close the file
			fclose(fp);

			// Read #2 for keys
			// Clear string buffer and read any incoming message from client         	
			bzero(recvbuf, BUFSIZE); 
			n = read(client_sockfd, recvbuf, BUFSIZE); 
			if (n < 0) {
				perror("Read from socket failed.\n");
				exit(1);
			}

			// Attempt to open the file named was in the message
			fp = fopen(recvbuf, "r");
			if (fp == NULL) {
				perror("Open key file failed.\n");
				exit(1);
			}

			// Initialize for storage of keystring that going to be extracted 
			char keytext[BUFSIZE]; 
			fgets(keytext, BUFSIZE, fp); 

			fclose(fp);

			// Encryption process	 
			// Check whether keytext larger than plaintext. If keytext smaller, then	
			if (strlen(keytext) < strlen(plaintext)) {
				bzero(sendbuf, BUFSIZE); // Clear string buffer
				// Store cipher string into the character array sendbuf
				snprintf(sendbuf, BUFSIZE, "%s", "error1: key too short");
				// Write the 'error' message to client
				n = write(client_sockfd, sendbuf, strlen(sendbuf)); 
				if (n < 0) {
					perror("Write to socket failed.\n");
					exit(1);
				}
				continue;
			}

			// Initialize for storage of ciphertext 
			char ciphertext[strlen(plaintext)]; 
			// Initialize for storage of the message in form of number (1 - 27)
			int plainNumb[strlen(plaintext)], keyNumb[strlen(plaintext)], cipherNumb[strlen(plaintext)];
			static const char possibleChar[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ "; //A to Z, with blank space too 

			// Loop that will iterate per character in plain text and be converted to random numbers
			// for both plaintext and keytext. The sum of the numbers is the ciphertext and
			// convert it back to random alphabet as ciphertext (using the conversion technique asked
			// from the assignment) 
			for (i = 0; i < strlen(plaintext); i++) {   
				plainNumb[i] = charToInt(plaintext[i]);      
				keyNumb[i] = charToInt(keytext[i]);      
				cipherNumb[i] = plainNumb[i] + keyNumb[i];     
				if (cipherNumb[i] > 26) {                
					cipherNumb[i] -= 27;
				}
				ciphertext[i] = possibleChar[cipherNumb[i]];          
			}
			// Add null terminate at the end of the message
			ciphertext[strlen(plaintext)-1] = '\0'; 

			// Clear string buffer
			bzero(sendbuf, BUFSIZE); 
			// Store cipher string into the character array sendbuf
			snprintf(sendbuf, BUFSIZE, "%s", ciphertext); 
			// Write the message to the client
			n = write(client_sockfd, sendbuf, strlen(sendbuf)); 
			if (n < 0) {
				perror("Write to socket error.\n");
				exit(1);
			}
		}
		close(client_sockfd);
		// parent wait children to finish	
		while (pid > 0) {
			pid = waitpid(-1,&status,WNOHANG);
		} 			
    	}
	close(sockfd);	
    	return 0;
}
