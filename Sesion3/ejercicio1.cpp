#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	if(argc!=2){
		perror("\nError: número de argumentos incorrecto");
		exit(-1);
	}
	pid_t pid;
	int num=strtol(argv[1],NULL,10);

	if((pid=fork())<0) {
		perror("\nError en el fork");
		exit(-1);
	}
	else if(pid==0){
		if(num%2==0){
			write(STDOUT_FILENO,"El número es par\n",20);
		}
		else
			write(STDOUT_FILENO,"El número es impar\n",21);
	}
	else{
		if(num%4==0){
			write(STDOUT_FILENO,"El número es divisible por 4\n",32);
		}		
		else
			write(STDOUT_FILENO,"El número no es divisible por 4\n",34);
	}
}
