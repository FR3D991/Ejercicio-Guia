#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int sock_conn, sock_listen, ret;
	struct sockaddr_in serv_adr;
	char peticion[512];
	char respuesta[512];
	
	// INICIALITZACIONS (Siempre serás iguales)
	// Obrim el socket
	if ((sock_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		printf("Error creant socket");
	// Fem el bind al port
	
	
	memset(&serv_adr, 0, sizeof(serv_adr));// inicialitza a zero serv_addr
	serv_adr.sin_family = AF_INET;
	
	// asocia el socket a cualquiera de las IP de la m?quina. 
	//htonl formatea el numero que recibe al formato necesario
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	// escucharemos en el port 9050
	serv_adr.sin_port = htons(9050);
	if (bind(sock_listen, (struct sockaddr *) &serv_adr, sizeof(serv_adr)) < 0)
		printf ("Error al bind");
	//La cola de peticiones pendientes no podr? ser superior a 4
	if (listen(sock_listen, 3) < 0)
		printf("Error en el Listen");
	
	int i;
	// Atenderemos solo 5 peticiones, es un bucle que implementará el servidor
	for(i=0;i<5;i++){
		printf ("Escuchando\n");
		
		sock_conn = accept(sock_listen, NULL, NULL);
		printf ("He recibido conexion\n");
		//sock_conn es el socket que usaremos para este cliente
		
		// Ahora recibimos su nombre (recoger la peticion), que dejamos en peticion
		ret=read(sock_conn,peticion, sizeof(peticion));
		printf ("Recibido\n");
		
		// Tenemos que añadirle la marca de fin de string 
		// para que no escriba lo que hay despues en el buffer
		peticion[ret]='\0';
		
		//Escribimos el nombre en la consola
		
		printf ("Peticion: %s\n",peticion);
		
		
		char *p = strtok(peticion, "/"); //Cortar la peticion por donde hay "/"
		int codigo =  atoi (p);//Coje el trozo que hay desde el inicio hasta la "/"
		p = strtok( NULL, "/");//Corte hasta la siguiente barra o hasta el final de string
		char nombre[20];
		strcpy (nombre, p);//copiamos el segundo trozo y lo copiamos en nombre
		printf ("Codigo: %d, Nombre: %s\n", codigo, nombre);
		
		if (codigo ==1) //piden la longitd del nombre (Primer servicio)
			sprintf (respuesta,"%d",strlen (nombre));//La va a escribir en un stringy lo va a colocar en respuesta
		//Printf lo escribe solo en consola
		else if (codigo ==2) //SEgundo servicio
				// quieren saber si el nombre es bonito
				if((nombre[0]=='M') || (nombre[0]=='S'))
				strcpy (respuesta,"SI");
				else
					strcpy (respuesta,"NO");
			else  //Decir si es alto (Tercer servicio)
				{
					p = strtok(NULL, "/"); //Cortar la peticion por donde hay "/"
					float altura =  atof (p); //COnvertir en un numero real
					if(altura > 1.70)
						sprintf(respuesta, "%s: eres alto", nombre);
					else
						sprintf(respuesta, "%s: eres bajito", nombre);
				}
		
			printf ("%s\n", respuesta);
			// Y lo enviamos
			write (sock_conn,respuesta, strlen(respuesta)); //Enviar por el socket la respuesta y el tamaño
			
			// Se acabo el servicio para este cliente
			close(sock_conn); 
	}
}
