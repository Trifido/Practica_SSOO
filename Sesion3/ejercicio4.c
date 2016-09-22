#include<sys/types.h>	
#include <sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>
#include <string.h>

int aux1;
int terminado[5]={0,0,0,0,0};

int main(){
	pid_t pid[5],pid_hijo;

	char salida[40], salida2[50], salida3[40];
	int i;
	for(i=0; i<5; i++){
		if( (pid[i]=vfork())<0){
			perror("\nError en el fork");
			exit(-1);
		}
		else if(pid[i]==0){
			//Hijos
			sprintf(salida,"%s%d\n","Soy el hijo ",getpid());
			write(STDOUT_FILENO,salida,strlen(salida));
			terminado[i]=1;
			exit(0);
		}	
	}
	int impares=3, pares= 2;
	if(pid>0){
		//Padre
		int j=5;
		while(impares>0){
			if(terminado[0]==1){
				pid_hijo=waitpid(pid[0],NULL,0);
				sprintf(salida2,"%s%d\n","Acaba de finalizar mi hijo con ",pid_hijo);
				write(STDOUT_FILENO,salida2,strlen(salida2));
				terminado[0]=0;
				impares--;
			}
			else if(terminado[2]==1){
				pid_hijo=waitpid(pid[2],NULL,0);
				sprintf(salida2,"%s%d\n","Acaba de finalizar mi hijo con ",pid_hijo);
				write(STDOUT_FILENO,salida2,strlen(salida2));
				terminado[2]=0;
				impares--;
			}
			else if(terminado[4]==1){
				pid_hijo=waitpid(pid[4],NULL,0);
				sprintf(salida2,"%s%d\n","Acaba de finalizar mi hijo con ",pid_hijo);
				write(STDOUT_FILENO,salida2,strlen(salida2));
				terminado[4]=0;
				impares--;
			}
		}
		while(pares>0){
			if(terminado[1]==1){
				pid_hijo=waitpid(pid[1],NULL,0);
				sprintf(salida2,"%s%d\n","Acaba de finalizar mi hijo con ",pid_hijo);
				write(STDOUT_FILENO,salida2,strlen(salida2));
				terminado[1]=0;
				pares--;
			}
			else if(terminado[3]==1){
				pid_hijo=waitpid(pid[3],NULL,0);
				sprintf(salida2,"%s%d\n","Acaba de finalizar mi hijo con ",pid_hijo);
				write(STDOUT_FILENO,salida2,strlen(salida2));
				terminado[3]=0;
				pares--;
			}
		}
	}
	exit(0);
}
