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
     
   		 //Socket initialization.

    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Cannot create socket");
    }
     puts("\n\nSocket created! \n "); 
   
    server.sin_addr.s_addr = inet_addr("173.194.34.63");
    server.sin_family = AF_INET;
    server.sin_port = htons( 80 );
 
    		//Connection initialization

    if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("\nCannot connect, please check IP & PORT\n");
        return 1;
    }
     
    puts("\nConnected!\n");
     
   		 //Sending message to HOST.

    message = "GET / HTTP/1.1\r\n\r\n";
    if( send(socket_desc , message , strlen(message) , 0) < 0)
    {
        puts("\nCannot send message!\n");
        return 1;
    }
    puts("\nMessage send!\n");
     
    		//Reply message.

    if( recv(socket_desc, server_reply , 2000 , 0) < 0)
    {
        puts("\nDid not receive the reply message\n\n");
    }
    puts("\nReply message received!\n\n");
    puts(server_reply);
     
    return 0;
}
