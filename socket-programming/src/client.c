
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<errno.h>
#include<sys/wait.h>
#include<signal.h>
#include<netdb.h>
#define PORT 25882
#define IP "127.0.0.1"
  
int main(int argc, char const *argv[]) /*from Beej Tutorial*/
{
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in clientaddr;
   
    char buffer[1024] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("Error in creating a socket\n");
        return -1;
    }
  printf("The client is up and running\n");
    memset(&clientaddr, '0', sizeof(clientaddr));
  
    clientaddr.sin_family = AF_INET;
    clientaddr.sin_port = htons(PORT);
      
    /*reused code from geekforgeeks*/
    if(inet_pton(AF_INET,IP, &clientaddr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
  
    if (connect(sock, (struct sockaddr *)&clientaddr, sizeof(clientaddr)) < 0)
    {

        printf("\nConnection Failed \n");
        return -1;
    }
  
sprintf(buffer,"%s %s",argv[1],argv[2]);


/*Error checking for various type of input*/
char string_comp1[]="LOG";
char string_comp2[]="Log";
char string_comp3[]="log";
char string_comp4[]="DIV";
char string_comp5[]="Div";
char string_comp6[]="div"; 
int result1=strcmp(argv[1],string_comp1);
int result2=strcmp(argv[1],string_comp2);
int result3=strcmp(argv[1],string_comp3);
int result4=strcmp(argv[1],string_comp4);
int result5=strcmp(argv[1],string_comp5);
int result6=strcmp(argv[1],string_comp6);

if(result1 !=0 && result2 !=0 && result3 !=0 && result4 !=0 && result5 !=0 && result6 !=0)
{
  printf("This is the wrong input\n");
   exit(-1);
  } 

printf("The client sent <%s>",argv[2]);
printf(" and <%s>",argv[1]);
printf(" to AWS\n");
   send(sock , buffer , strlen(buffer) , 0 );
   valread = read( sock , buffer, 1024);
   printf("According to AWS <%s>",argv[2]);
   printf(" on <%s>",argv[1]);
   printf(" : <%s>\n",buffer);
    
    return 0;
}
