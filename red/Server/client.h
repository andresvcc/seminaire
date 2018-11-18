#ifndef CLIENT_H
#define CLIENT_H
#define PORT	 	1977
#define BUF_SIZE	1024
#include "server.h"

typedef struct
{
   SOCKET sock;
   char name[BUF_SIZE];
}Client;

#endif /* guard */
