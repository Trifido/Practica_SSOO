#include<sys/types.h>	
#include <sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]){
	if(argc==2){
		execl(argv[1],NULL);
	}
	else if(argc=>3){
		pid_t pid_hijo;
		if(strcmp(argv[2],"bg")!=0){
			execl(argv[1],NULL);
		}
		else{
			if( (pid_hijo=fork())<0) {
				perror("\nError en el fork");
				exit(-1);
			}
			if(pid_hijo==0){
				execl(argv[1],argv[2],NULL);
				exit(0);
			}
		}
	}
	else if(argc>3){
		if(strcmp(argv[argc-1],"bg")==0){
			
		}
		else{
			//Ejecutamos en Foreground
		}
	}
	wait(NULL);
    exit(0);
}
