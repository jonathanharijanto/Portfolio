// HW PROGRAM 4 - CS 344 created by Jonathan Harijanto
// Some of these codes are inspired from TAs, Ben's slide and reference link, and Stackoverflow
//
// This file is "otp_dec.c". This program connects to otp_dec_d. It will ask to decrypt ciphertext
// using passed in ciphertext and key, however this doesnt do the decryption. 
// It will output to stdout when receives the plaintext. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>	

#define BUFSIZE 1024


int main(int argc, char *argv[]) {
	// Initialize sock file description, port, server address struct    
	int sockfd;
	int port_number; 
	int n;
    	struct sockaddr_in server;
    	char buffer[BUFSIZE];
	char check[] = "dec_handshake";
	struct hostent* serv_addr;

	// Check whether argument passed correctly or not
    	if (argc < 4) {
       		printf("Usage: otp_dec ciphertext key port");
       		exit(1);
    	}

	// Grab the value from 3rd argument and create the socket
    	port_number = atoi(argv[3]);
 
	// Returns hostent structure with info about the designated server
	serv_addr = gethostbyname("localhost");
	if (serv_addr == NULL) {
		perror("Hostname not found");
		exit(1);
	}

	// Fill the client socket address struct
	server.sin_family = AF_INET; // protocol family
    	server.sin_port = htons(port_number); // port number
	memcpy(&server.sin_addr, serv_addr->h_addr, serv_addr->h_length);    

	// Setting up the socket
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if (sockfd < 0) {
		perror("Open for socket failed");
		exit(1);
	}	

	// Check whether can connect the socket to remote address
    	if (connect(sockfd,(struct sockaddr *) &server, sizeof(server))) {
		printf("Connect failed");
	//	printf("Error: could not contact otp_enc_d on port %d.\n",port_number);
		exit(2);
    	}

	memset(buffer,'\0',sizeof(buffer));
	
	// Handshaking: comparing first string that being recieved to verify the right
	// client is trying to use the server.  	
	write(sockfd,check,sizeof(check));
	read(sockfd,buffer,sizeof(buffer));
	if (strcmp(buffer, "handshake_with_dec_d") != 0) {
		printf("Error: could not contact otp_enc_d on port %d.\n",port_number);
		exit(2);
	}

    	// Store value of arg2 in char array buffer
    	snprintf(buffer, BUFSIZE, "%s", argv[1]);
	// Send the ciphertext file name
    	n = write(sockfd, buffer, strlen(buffer));
    	if (n < 0) {
        	perror("Write argv[1] to socket failed.\n");
        	exit(1);
    	}

    	sleep(1);

	// Store value of arg2 in char array buffer
    	snprintf(buffer, BUFSIZE, "%s", argv[2]);
	// Send the key file name
    	n = write(sockfd, buffer, strlen(buffer));
    	if (n < 0) {
        	perror("Write to socket failed.\n");
        	exit(1);
    	}

	// Clear string buffer
    	bzero(buffer, BUFSIZE);
	// Wait for server to response
    	n = read(sockfd, buffer, BUFSIZE);
    	if (n < 0) {
        	perror("Read from socket failed.\n");
        	exit(1);
    	}

	// No more checking for bad char because ciphertext exist will definetly not bad char
	// since already been checked during conversion of plain to chiper
	// Print value of char array buffer
    	printf("%s\n", buffer);
    	close(sockfd);
     
    	return 0;
}
