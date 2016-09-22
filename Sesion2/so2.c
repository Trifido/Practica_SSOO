#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

int main(int argc, char *argv[])
{
	if(argc!=3)
		printf("Error: numero de argumentos distinto de 3.\n");
	else{
		//Añadir comprobacion de que el numero es octal.
		int num=strtol(argv[2],NULL,8);

		struct dirent *contenido;
		struct stat permisos_nuevos, permisos_antiguos;
		char direccion[200];

		//Abrimos el directorio
 		DIR *directorio=opendir(argv[1]);
		if(directorio==NULL){
			printf("Error: No se puede abrir el directorio.\n");
			exit(-1);
		}

		printf("<Nombre>\t  : \t<antigua>  \t<nueva> \n");
		while((contenido=readdir(directorio))!=NULL){
			if((strcmp(contenido->d_name, ".")!=0) && (strcmp(contenido->d_name, "..")!=0)){
				sprintf(direccion,"%s/%s",argv[1],contenido->d_name);
				if(stat(direccion,&permisos_antiguos) < 0) {
					printf("\nError al intentar acceder a los atributos de archivo1\n");
					perror("\nError en lstat");
					exit(-1);
				}
				umask(0);
				if(chmod(direccion,num)<0){
					printf("<%s>\t : \t%d \t<%u>\n ",contenido->d_name, errno, permisos_antiguos.st_mode);
				}
				else{
					if(stat(direccion,&permisos_nuevos) < 0) {
						printf("\nError al intentar acceder a los atributos de archivo1\n");
						perror("\nError en lstat");
						exit(-1);
					}
			
					printf("<%s>\t : \t<%u> \t<%u>\n ",contenido->d_name, permisos_antiguos.st_mode, permisos_nuevos.st_mode);
				} 			
			}
		}
		closedir(directorio);
	}
}
