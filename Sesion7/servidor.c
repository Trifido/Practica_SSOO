#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include<dirent.h>
#include<unistd.h>
#include<string.h>


static void mimanejador(int senal){
	pid_t pid=wait(NULL);
}

int main(){
	umask(0);
	signal(SIGCHLD, mimanejador);

	mkfifo ("FIFOe",S_IFIFO);
	mkfifo ("FIFOs",S_IFIFO);
	int dfe, dfs;
	dfe=open("FIFOe",O_RDWR,S_IRWXU);
	dfs=open("FIFOs",O_RDWR,S_IRWXU);

	int dbloqueo=open("BLOQUEO",O_RDWR,S_IRWXU);

	int leido;
	int pid;
	char cadena[80],buf[80];
	while((leido=read(dfe,buf,80))!=0){
		if((pid=fork())==0){
			pid_t mipid= getpid();
			sprintf(cadena,"FIFO%d",mipid);
			mkfifo(cadena,S_IFIFO);
			write(dfs,&mipid,6);
			int defpid=open(cadena,O_RDWR,S_IRUSR);
			dup2(defpid,STDIN_FILENO);	//redirigir la entrada estandar
			execlp("./proxy","proxy",NULL); //proceso proxy
		}
		else if(pid<0){
			perror("\nError en el fork");
			exit(-1);
		}
		else{
			waitpid(&pid);
		}
	}
}
