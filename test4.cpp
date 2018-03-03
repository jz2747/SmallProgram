#include<iostream>
#include<sys/socket.h>
#include<stdlib.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
using namespace std;
void *receive(void* i){
	int client = socket(AF_INET, SOCK_STREAM,0);

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1500);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	socklen_t addrlen = sizeof(server_addr);

	if (connect(client,(struct sockaddr*)&server_addr, addrlen) < 0){
		cout << "cannot connect to server..." << endl;
	        exit(1);
	}	
	char re[100];
	bool isExit = false;
	while (!isExit){
		if(recv(client, re, sizeof(re), 0) < 0){
			cout << RED << "Connection terminatedif..." << RESET << endl;
			exit(1);
		}
		cout << CYAN << "Server: " << re << RESET << endl;
		if (*re == '#')
			isExit = true;
	}
	pthread_exit(NULL);
}

void *send(void *i){
	int client = socket(AF_INET, SOCK_STREAM,0);

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1501);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	socklen_t addrlen = sizeof(server_addr);

	if (connect(client,(struct sockaddr*)&server_addr, addrlen) < 0){
		cout << "cannot connect to server..." << endl;
	        exit(1);
	}	
	char re[100];
	bool isExit = false;
	while (!isExit){
		cin >> re;
		if(send(client, re, sizeof(re), 0) < 0){
			cout << RED << "Connection terminated..." << RESET << endl;
			exit(1);
		}
		if (*re == '#')
			isExit = true;
	}
	pthread_exit(NULL);
}
int main(){
	pthread_t receivethread, sendthread;
	int rc;
	long i = 1;
	rc = pthread_create(&receivethread, NULL, &receive, (void*)i);
	if (rc){
		cout << "Cannot create receive thread..." << endl;
		exit(1);
	}
	rc = pthread_create(&sendthread, NULL, &send, (void*)i);
	if (rc){
		cout << "Cannot create send thread..." << endl;
		exit(1);
	}
	pthread_exit(NULL);
}	
