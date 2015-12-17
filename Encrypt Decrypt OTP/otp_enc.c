// HW PROGRAM 4 - CS 344 created by Jonathan Harijanto
// Some of these codes are inspired from TAs, Ben's slide and reference link, and Stackoverflow
//
// This file is "otp_enc.c". This program connects to otp_enc_d. It performs one time pad style encryption
// , however this doesnt do the encryption. It will output to stdout when receives the ciphertext. 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFSIZE 1024


int main(int argc, char *argv[]) {
    	// Initialize socket file description, port, server address struct
	int sockfd;
	int port_number;
	int n;
    	struct sockaddr_in server;
    	char buffer[BUFSIZE];
	char check[] = "enc_handshake";
	struct hostent* serv_addr; 

	// Check whether argument passed correctly or not
    	if (argc < 4) {
       		printf("Usage: otp_enc plaintext key port");
       		exit(1);
    	}

	// Grab the vlaue form 3rd argument and create the socket
    	port_number = atoi(argv[3]);

	// Returns hostent structure with info about the designated server 
	serv_addr = gethostbyname("localhost");
	if (serv_addr == NULL) {
		perror("ip address resolution");
		exit(1);
	}	
    
	// Fill the client socket address struct
	server.sin_family = AF_INET; // protocol family
    	server.sin_port = htons(port_number); // port number
	memcpy(&server.sin_addr,serv_addr->h_addr,serv_addr->h_length);    
	//server.sin_addr.s_addr = htonl(INADDR_ANY); // autofill local address

	// Setting up the socket	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
    	       	perror("Open for socket failed.\n");
		exit(1);
    	}

	// Check whether can connect the socket to remote address
    	if (connect(sockfd,(struct sockaddr *) &server, sizeof(server))) {
		printf("Connect failed ");
	//	printf("Could not contact otp_dec_d on port %d.\n",port_number);
		exit(2);
    	}

	memset(buffer,'\0',sizeof(buffer));

	// Handshaking: comparing first string that being recieved to verify the right
	// client is trying to use the server.  	
	write(sockfd,check,sizeof(check));
	read(sockfd,buffer,sizeof(buffer));
	if (strcmp(buffer,"handshake_with_enc_d") != 0) {
		printf("Could not contact otp_dec_d on port %d.\n",port_number);
		exit(2);
	} 

	// Store value of arg1 in char array buffer 
    	snprintf(buffer, BUFSIZE, "%s", argv[1]);
	// Send the plaintext file name
    	n = write(sockfd, buffer, strlen(buffer));
    	if (n < 0) {
        	perror("Write argv[1] to socket failed.\n");
		exit(1);
    	}

    	sleep(1);

	// Stroe value of arg2 in char array buffer
    	snprintf(buffer, BUFSIZE, "%s", argv[2]);
	// Send the key file name
    	n = write(sockfd, buffer, strlen(buffer));
    	if (n < 0) {
        	perror("Write to socket failed.\n");
		exit(1);
    	}

	// Clearn string bufer
    	bzero(buffer, BUFSIZE);
	// Wait for server to response, and read from a file
    	n = read(sockfd, buffer, BUFSIZE);
    	if (n < 0) {
        	perror("Read from socket failed.\n");
		exit(1);
    	}

	// Compare the value of char array buffer with "error" message from "otp_enc_d.c"   
	if (strstr(buffer, "error1: key too short")!= NULL) {
        	perror("Key is too short.\n");
		exit(1);
	// Compare the value of char in array buffer whether exist bad character	
    	} else if (buffer[0] < 'A' || buffer[0] > 'Z')  {
        	perror("Input contains bad characters.\n");
		exit(1);
	// No short key or bad char, then print the value of char array buffer
    	} else {
        	printf("%s\n", buffer);
    	}
    	close(sockfd);
     
    	return 0;
}
