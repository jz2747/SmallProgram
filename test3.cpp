#include<iostream>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<pthread.h>
#include<cstdlib>
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

void* receive(void *i){
	int listener, server;
	listener = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1501);
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	socklen_t addrlen = sizeof(server_addr);

	if (bind(listener,(struct sockaddr *)&server_addr,  addrlen) < 0){
		cout << "Cannot bind a name to a socket..." << endl;
		exit(1);
	}
	if(listen(listener,1) < 0){
		cout << "cannot set listen..." << endl;
		exit(1);
	}

	server = accept(listener, (struct sockaddr*)&server_addr, &addrlen);
	if (server < 0){
		cout << "cannot accept a new connection request..." << endl;
		exit(1);
	}

	char message[100];
	bool isExit = false;
	while(!isExit){
		if(recv(server, message, sizeof(message),0)<0){
			cout << RED << "Connection terminated..." << RESET << endl;
			exit(1);
		}
		cout << CYAN << "Client: " << message << RESET << endl;
		if (*message == '#')
			isExit = true;
	}
	pthread_exit(NULL);
}

void* send(void* i){
	int listener, server;
	listener = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1500);
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	socklen_t addrlen = sizeof(server_addr);

	if (bind(listener,(struct sockaddr *)&server_addr,  addrlen) < 0){
		cout << "Cannot bind a name to a socket..." << endl;
		exit(1);
	}
	if(listen(listener,1) < 0){
		cout << "cannt set listen..." << endl;
		exit(1);
	}

	server = accept(listener, (struct sockaddr*)&server_addr, &addrlen);
	if (server < 0){
		cout << "cannot accept a new connection request..." << endl;
		exit(1);
	}

	char message[100];
	bool isExit = false;
	while(!isExit){
		cin >> message;
		if (*message == '#')
			isExit = true;
		if(send(server, message, sizeof(message),0)<0){
			cout << RED << "Connection Terminated..." << RESET << endl;
			exit(1);
		}
	}
	pthread_exit(NULL);
}
int main(){
	pthread_t recethread, sendthread;
	int rc;
	long i;
	rc = pthread_create(&recethread, NULL, &receive, (void*)i);
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
