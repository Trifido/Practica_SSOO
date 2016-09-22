#include<sys/types.h>	
#include <sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]){
	if(argc<2){
		perror("Error: número de argumentos.");
		exit(-1);
	}
	else if(argc>1){
		pid_t pid_hijo;
		int argtotal;

		if(strcmp(argv[argc-1],"bg")==0)
			argtotal=argc-2;
		else
			argtotal=argc-1;

		int i;
		char *arg[10];

		for(i=0; i<argtotal; i++){
			arg[i]=argv[i+1];
			printf("%s\n",arg[i]);
		}
		arg[i]=NULL;

		if((pid_hijo=fork())<0){
			perror("\nError en el fork");
			exit(-1);
		}
		if(pid_hijo==0){
printf("argv[1]: %s",argv[1]);
			execv(argv[1],arg);  
		}
		else{
			if(strcmp(argv[argc-1],"bg")!=0)
				wait(NULL);
		}
	}
    exit(0);
}
