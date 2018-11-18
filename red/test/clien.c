#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(void) {
  //leer la direccion ip
  char direIP [9];
  printf("donne la ip \n");
  scanf ("%9s",direIP);
  //leer el puerto en typo entero positivo
  unsigned short int prter = 10;
  printf("donne le port \n");
  scanf("%hu", &prter);
  //--------------------------------------
  printf("conexion to %s\n", direIP);
  //--------------------------------------
	struct sockaddr_in direccionServidor;
	direccionServidor.sin_family = AF_INET;
	direccionServidor.sin_addr.s_addr = inet_addr(direIP);
	direccionServidor.sin_port = htons(prter);

	int cliente = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(cliente, (void*) &direccionServidor, sizeof(direccionServidor)) != 0) {
		perror("pas posible de se conecter");
		return 1;
	}

  char* buffer = malloc(1000);

	while (1) {


    int bytesRecibidos = recv(cliente, buffer, 1000, 0);

    if (bytesRecibidos <= 0) {
      perror("Le Server est OFF.");
      return 1;
    }else{
      printf("Server parle\n");
    }

    buffer[bytesRecibidos] = '\0';
    printf("il est arrive des donnees %d bytes avec:  %s\n", bytesRecibidos, buffer);


    char mensaje[1000];
    scanf("%s", mensaje);
    send(cliente, mensaje, strlen(mensaje), 0);

	}

	return 0;
}
