#include <stdio.h>
#include <string.h>
#include <stdlib.h> //necesario para atof


int main(int argc, char *argv[]) {

	char peticion[100];
	char respuesta[100];
	
	strcpy(peticion, "Freddy/21/Juan/12/Maria/22/Marcos/19");
	//Resultado: "Freddy*21-Maria*22-Marcos*19" --- Solo mayores de edad
	
	char nombre[20];
	int edad;
	char *p = strtok(peticion, "/");
	
	
	while (p!=NULL);
	{
		strcpy(nombre,p);
		p = strtok(NULL, "/");
		edad = atoi(p);
		if (edad >18)
			sprintf(respuesta, "%s%s*%d-", respuesta, nombre, edad);
		
		p = strtok(NULL, "/");
	}
	
printf("Resultado: %s", respuesta);
	
	
	
	
	
	
}

