#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <string.h>

int main(){
	
	int WRITE = 1;
	int READ = 0;

	int to_kid[2];
	int from_kid[2];
	pipe (to_kid);
	pipe (from_kid);
	
	int num = 0;
	int cpid = fork();

	if (cpid){

		close (to_kid [READ]);
		close (from_kid [WRITE]);	

		srand ( time(NULL) );
		num = rand() % 100;

		printf("PID [%d]\tOriginal Number [%d]\n", getpid(), num);

		int s = write (to_kid [WRITE], &num, sizeof(int));  	

	}

	else{

		close (to_kid [WRITE]);
		close (from_kid [READ]);

		int temp = 2;		
		
		read (to_kid [READ], &temp, sizeof(int));

		printf("PID [%d]\tParent should recieve [%d]\n", getpid(), temp * temp);
		
		temp = temp * temp;
		write (from_kid [WRITE], &temp, sizeof(int)); 
	
	}
	
	if(cpid){
		
		wait();

		read( from_kid [READ], &num, sizeof(int));

		printf("PID [%d]\tRecieved [%d]\n", getpid(), num);	
	}
			
	return 0;
}
