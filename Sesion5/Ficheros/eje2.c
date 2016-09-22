#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>

int cont[64];

static void manejador(int sigNum){
	if ( (sigNum != 9) && (sigNum != 19) && (sigNum != 32) && (sigNum != 33) ){
		printf("La señal %d se ha recibido %d veces.\n",sigNum,cont[sigNum]);
		cont[sigNum]++;
	}
	else
		printf("No se puede manejar la señal %d",sigNum);
}

int main(int argc, char *argv[]){
	printf("No puedo manejar la señal 9\n");
	printf("No puedo manejar la señal 19\n");
	printf("No puedo manejar la señal 32\n");
	printf("No puedo manejar la señal 33\n");
	printf("Esperando envio de señales...\n");

	int i;
	for(i=0; i<64; i++)
		cont[i]=1;

	struct sigaction sig_USR_nact;

	sig_USR_nact.sa_handler= manejador;
	sigemptyset (&sig_USR_nact.sa_mask);

	int num;

	for(num=1; num<65; num++){
		if((num != 9) && (num != 19) && (num != 32) && (num != 33)){
			if( sigaction(num,&sig_USR_nact,NULL)==-1){
				perror("\nError al intentar establecer el manejador de señal");
				exit(-1);
			}
		}
	}
	for(;;){
	}
	
}
