#include<iostream>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<arpa/inet.h>
using namespace std;

void *receive(void *i){
	int client = (int)(long)i;
	char msg[1024];
	do{
		if(recv(client,msg,sizeof(msg),0) < 0 || *msg == '#')
			break;
		cout << msg;
	}while(1);
	pthread_exit(NULL);
}

void *send(void *i){
	int client = (int)(long)i;
	char msg[1024];
	do{
		cin >> msg;
		if(*msg == '#' || send(client,msg,sizeof(msg),0) < 0)
			break;
	}while(1);
	pthread_exit(NULL);
}

int main(){
	int client;
	pthread_t sendpt, recvpt;

	struct sockaddr_in server_addr;
	socklen_t addrlen;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(1500);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addrlen = sizeof(server_addr);
	client = socket(AF_INET, SOCK_STREAM, 0);
	if(client < 0){
		cout << "Cannot create a socket..." << endl;
		exit(1);
	}

	if(connect(client, (struct sockaddr*)&server_addr, addrlen) < 0){
		cout << "cannot connet to server... " << endl;
		exit(1);
	}
	
	pthread_create(&sendpt,NULL, send, (void *)(long)client);
	pthread_create(&recvpt,NULL, receive, (void *)(long)client);
	pthread_exit(NULL);
}
