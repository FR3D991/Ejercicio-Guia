#include <stdio.h>
#include <string.h>
#include <stdlib.h> //necesario para usar el atof y atoi

int main(int argc, char *argv[]) {
	
	char peticion [100];
	
	//TEnemos el siguiente nombre
	strcpy(peticion, "4/Freddy/21/1.75");
	
	//QUeremos descomponerlo en sus pedazos
	
	//Primero cogemos la parte del numero (4) hasta la barra
	int codigo;
	char nombre[20];
	int edad;
	float altura; //NUmero real
	
	//EScogemos el nombre que viene después del numero y la barra
	char *p = strtok(peticion, "/");
	codigo = atoi(p); //convertir la string en numero
	p = strtok (NULL, "/");
	strcpy(nombre, p);
	
	//EScogemos la edad que es entero
	p = strtok(NULL, "/");
	edad = atoi(p);
	
	//EScogemos la altura que es float
	p = strtok(NULL, "/");
	altura = atof(p);//AL ser float tenemos que poner atof en vez de atoi
	
	printf("codigo: %d, nombre: %s, edad: %d, altura: %f\n", codigo, nombre, edad, altura);
	
	
	//VAmos a crear una respuesta
	char respuesta[100];
	//El sprintf va muy bien para construir respuestas es un printf sobre un string
	//VA a imprimirlo sobre un string
	if(edad > 18)
		sprintf(respuesta, "%s es mayor de edad por que tiene %d años", nombre, edad);
	else
		sprintf(respuesta, "%s no es mayor de edad", nombre);
	
	printf("Respuesta: %s\n", respuesta);
	
	
}

