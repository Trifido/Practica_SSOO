#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

void Busqueda(char *direccion, int *num_archivos, int *espacio_ocupado){
	DIR *directorio=opendir(direccion);
	struct dirent *contenido;
	struct stat atributos;
	while((contenido=readdir(directorio))!=NULL){
		char subdir[200];

		sprintf(subdir,"%s/%s",direccion,contenido->d_name);
		stat(subdir,&atributos);

		//Comprobamos si es un archivo regular o un directorio
		if(S_ISREG(atributos.st_mode)){
			//Comprobamos si el archivo regular tiene permisos de ejecucion para grupo y otros
			if((atributos.st_mode & S_IXGRP) && (atributos.st_mode & S_IXOTH)){
				printf("%s  %u\n",subdir,atributos.st_ino);
				(*num_archivos)+=1;
				(*espacio_ocupado)+=atributos.st_size;
			}
		}
		else if(S_ISDIR(atributos.st_mode)){
			//Evitamos entrar un bucle infinito con los directorio . y ..
			if((strcmp(contenido->d_name, ".")!=0) && (strcmp(contenido->d_name, "..")!=0)){
				Busqueda(subdir,num_archivos,espacio_ocupado);
			}
		}
	}
	closedir(directorio);
}

int main(int argc,char *argv[]){
	char direccion[200];
	if(argc==2){
		sprintf(direccion,"%s",argv[1]);
	}
	else if(argc==1){
		sprintf(direccion,"%s",".");
	}
	else{
		printf("Error: Número de argumentos incorrecto.\n");
		exit(-1); 
	}

	int num_archivos=0, espacio_ocupado=0;
	printf("El PATH es: %s\n",argv[1]);
	printf("Los i-nodos son:\n");

	Busqueda(direccion,&num_archivos,&espacio_ocupado);
	printf("Existen %i archivos regulares con permiso x para grupo y otro.\n",num_archivos);
	printf("El tamaño total ocupado por dichos archivos es %i bytes.\n",espacio_ocupado);

}
