#include <stdio.h>
#include <string.h>    
#include <sys/socket.h>
#include <arpa/inet.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc , char *argv[])
{
    int socket_desc;
    struct sockaddr_in server;
    char *message , server_reply[2000];
     
   		 //Création du socket.

    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Impossible de créer le socket");
    }
     puts("\n\nSocket crée! \n "); 
   
    server.sin_addr.s_addr = inet_addr("173.194.34.63");
    server.sin_family = AF_INET;
    server.sin_port = htons( 80 );
 
    		//Connection au server distant

    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("\nConnection impossible, vérifiez l'ip et le port\n");
        return 1;
    }
     
    puts("\nConnecté!\n");
     
   		 //Envoi d'un message au server distant.

    message = "GET / HTTP/1.1\r\n\r\n";
    if( send(socket_desc , message , strlen(message) , 0) < 0)
    {
        puts("\nEchec d'envoi du méssage!\n");
        return 1;
    }
    puts("\nMessage envoyé avec succès!\n");
     
    		//Reception du message de retour.

    if( recv(socket_desc, server_reply , 2000 , 0) < 0)
    {
        puts("\nEchec de la réception du mesage retour\n\n");
    }
    puts("\nMessage retour reçu avec succès!\n\n");
    puts(server_reply);
     
    return 0;
}
