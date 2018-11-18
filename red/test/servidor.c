#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(void) {
  //leer el puerto en typo entero positivo
  unsigned short int prter = 10;
  printf("donne le port \n");
  scanf("%hu", &prter);
  //puro protocolo obligado para funcionar, ver manual
	struct sockaddr_in direccionServidor;
	direccionServidor.sin_family = AF_INET;
	direccionServidor.sin_addr.s_addr = INADDR_ANY;
	direccionServidor.sin_port = htons(prter);

	int servidor = socket(AF_INET, SOCK_STREAM, 0);

  int activado = 1;
  setsockopt(servidor, SOL_SOCKET, SO_REUSEADDR, &activado, sizeof(activado));

  //esto es para poder relanzar el programa cuando lo matamos a la fuerza, debido a que el bind no refresca los puertos enseguida
	if (bind(servidor, (void*) &direccionServidor, sizeof(direccionServidor)) != 0) {
		perror("error avec le bind");
		return 1;
	}

	printf("je suis pret\n");
	listen(servidor, 100);

  //------------------------------

	struct sockaddr_in direccionCliente;
	unsigned int len;
	int cliente = accept(servidor, (void*) &direccionCliente, &len);

	printf("J'ai recu une conexion en %d!!\n", cliente);
	send(cliente, "hello cliente!", 13, 0);

 //--------------------------------

 char* buffer = malloc(1000);

 while (1) {
   int bytesRecibidos = recv(cliente, buffer, 1000, 0);

   if (bytesRecibidos <= 0) {
     perror("Le client est OFF.");
     printf("fin comunication\n");
     return 1;
   }else{
     printf("Client parle\n");
   }

   buffer[bytesRecibidos] = '\0';
   printf("il est arrive des donnees %d bytes avec:  %s\n", bytesRecibidos, buffer);
   send(cliente, buffer,bytesRecibidos,0);
 }

 free(buffer);

 return 0;



}
