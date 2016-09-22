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

void bloquear(int dbloqueo, int orden) {
	struct flock cerrojo;
	// Inicializamos el cerrojo para bloquear todo el archivo
	cerrojo.l_type= orden;
	cerrojo.l_whence= SEEK_SET;
	cerrojo.l_start= 0;
	cerrojo.l_len= 0;

	if(fcntl(dbloqueo,F_SETLKW,&cerrojo)==-1){
		perror("Proxy: problemas al bloquear para impresion");
		exit(1);
	}
}

int main(){
	umask(0);
	FILE *temporal=tmpfile();
	FILE *pfile;
	int leido;

	while((leido=read(STDIN_FILENO,pfile,200))!=0){
		fwrite(temporal,leido,leido,pfile);
	}

	int dbloqueo= open("BLOQUEO", O_RDWR|O_CREAT);
	bloquear(dbloqueo, F_WRLCK);

	fread(temporal,leido,leido,pfile);
	write(STDOUT_FILENO,pfile,200);

	bloquear(dbloqueo, F_UNLCK);
	exit (0);
}
