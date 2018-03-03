#include<stdio.h>
#include<stdlib.h>

int main(){
	pid_t pid;

	printf("parent : %d\n", getpid());

	pid = fork();

	if(pid == 0){
		printf("child : %d\n", getpid());
		sleep(2);
		printf("chiild exit\n");
		exit(1);
	}

	while(1)
	{
		sleep(1);
	}
	return 0;
}
