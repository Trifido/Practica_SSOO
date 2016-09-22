#include<sys/types.h>	
#include <sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int main(){
	pid_t pid, pid_h;
	int pid1, pid2, pid3, pid4, pid5;
	int valor_devuelto;
	int i;
	for(i=0; i<5;i++){
		if( (pid=fork())<0){
			perror("\nError en el fork");
			exit(-1);
		}
		else if(pid==0){
			//Hijos
			printf("Soy el hijo %d\n",getpid());
			exit(-1);
		}
		if(pid>0){
		
		}	
	}
	exit(0);
}
