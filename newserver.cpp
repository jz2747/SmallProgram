#include<iostream>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<vector>
#include<pthread.h>
using namespace std;


// fix how to talk to clients now
// server can receive messages now,
// but can't talk to clients
//
//
//

void *receive(void *i){
	int client = (int)(long)i;
	char msg[1024];
	do{
		if(recv(client,msg, sizeof(msg),0) < 0 || *msg == '#')
			break;
		cout << msg << endl;
	}while(1);
	pthread_exit(NULL);
}

void *send(void *i){
	int client = (int)(long)i;
	char msg[1024];
	do{
		cin >> msg;
		if(*msg == '#' || send(client, msg, sizeof(msg),0) < 0)
			break;
	}while(1);
	pthread_exit(NULL);
}

int main(){
	int listener;
	vector<int*> clients;
	vector<pthread_t*> threads;

	struct sockaddr_in server_addr;
	socklen_t addrlen;

	listener = socket(AF_INET, SOCK_STREAM, 0);
	if (listener < 0){
		cout << "cannot create a listener..." << endl;
		exit(1);
	}
	cout << "Listener created!" << endl;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1500);
	server_addr.sin_addr.s_addr = htons(INADDR_ANY);
	addrlen = sizeof(server_addr);

	if(bind(listener, (struct sockaddr*)&server_addr, addrlen) < 0){
		cout << "Cannot bind a name to a socket..." << endl;
		exit(1);
	}

	if(listen(listener, 2) < 0){
		cout << "Cannot set listener listening..." << endl;
		exit(1);
	}

	int* client;
	pthread_t* thread;
	while(1){
		client = new int;
		*client = accept(listener, (struct sockaddr*) &server_addr, &addrlen);
		if(*client < 0){
			cout << "Cannot accept the request... " << endl;
			exit(1);
		}
		cout << "New client has been connected!" << endl;
		clients.push_back(client);   //client or *client?
		thread = new pthread_t;
		pthread_create(thread, NULL, receive, (void*)(long)(*client));
		threads.push_back(thread);  //thread  or *thread ?
		thread = new pthread_t;
		pthread_create(thread, NULL, send, (void*)(long)(*client));
		threads.push_back(thread);
	}

	vector<int*>::iterator intit;
	vector<pthread_t*>::iterator pthreit;
	for(intit = clients.begin(); intit != clients.end(); intit++){
		delete *intit;
	}
	for(pthreit = threads.begin();pthreit != threads.end(); pthreit++ ){
		delete *pthreit;
	}
	pthread_exit(NULL);
}
		


