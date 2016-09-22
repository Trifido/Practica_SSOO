/*
*
*		PONER SALIDA ESTANDAR
*
*
*/
#include<sys/types.h>	
#include <sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>
#include <string.h>
int main(){
	pid_t pid, pid_hijo;
	int valor_devuelto;
	char salida[40], salida2[50], salida3[40];
	int i;
	for(i=0; i<5; i++){
		if( (pid=fork())<0){
			perror("\nError en el fork");
			exit(-1);
		}
		else if(pid==0){
			//Hijos
			sprintf(salida,"%s%d\n","Soy el hijo ",getpid());
			write(STDOUT_FILENO,salida,strlen(salida));
			exit(0);
		}	
	}
	if(pid>0){
		//Padre
		int j=5;
		while(j>0){
			pid_hijo=wait(&valor_devuelto);
			sprintf(salida2,"%s%d\n","Acaba de finalizar mi hijo con ",pid_hijo);
			write(STDOUT_FILENO,salida2,strlen(salida2));
			j--;
			if(j>0){
				sprintf(salida3,"%s%d%s\n","Sólo me quedan",j," hijos vivos.");
				write(STDOUT_FILENO,salida3,strlen(salida3));
			}
		}
	}
	exit(0);
}
