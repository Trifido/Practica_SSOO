#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char *argv[])
{
	int fd1, fd2;
	char buf1[80];

	if(argc==1){
		//Entrada estandar.		
		fd1=STDIN_FILENO;
	}
	else if(argc==2){
		if( (fd1=open(argv[1],O_RDONLY,S_IRUSR|S_IWUSR))<0){
			printf("\nError %d en open",errno);
			perror("\nError en open");
			exit(-1);
		}
	}
	else{
		printf("\nError en el numero de argumentos.");
	}

	fd2=open("salida",O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR);

	int i=1,j=0;
	char numero[11];
	int fin=1;
	
	lseek(fd2,30,SEEK_SET);	//Decimos que el puntero apunte 28 posiciones mas adelante
							//Para poder meter la cadena de caracteres inicial.
	write(fd2,"\n",1);
	while(fin!=0){
		fin=read(fd1,buf1,80);    //Leo del argv1 80 bytes y lo paso al array
		if(fin!=0 && fin!=-1){
			sprintf(numero,"\nBloque %d\n",i);
			lseek(fd2,8,SEEK_END);

			write(fd2,numero,strlen(numero));	  //Escribo el numero
			lseek(fd2,strlen(numero),SEEK_END);

			write(fd2,buf1,80);		  //Escribo los 80 bytes
			lseek(fd2,80,SEEK_END);
			i++;
		}
		else if(fin==0){
			write(fd2,"\n",1);
		}
		else if(fin==-1){
			perror("Error: en read.");
			exit(EXIT_FAILURE);
		}
	}
		//Escribir al inicio del archivo
	char num[2];
	lseek(fd2,0,SEEK_SET);
	write(fd2,"El número de bloques es ",25);
	lseek(fd2,25,SEEK_SET);
	sprintf(numero,"%d",i-1);
	write(fd2, numero,1 );

	close(fd1);
	close(fd2);
}
