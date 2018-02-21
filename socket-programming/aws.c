
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

uint16_t DST_PORT_A  = 21882;
uint16_t DST_PORT_B = 22882;
uint16_t DST_PORT_C = 23882;
uint16_t SRC_PORT  =  24882;
uint16_t TCP_PORT  =  25882;

#define PORT 25882
#define IP "127.0.0.1"

double UDP_A(char input[1024]) 
{
    struct sockaddr_in addr, srcaddr; 
    int fd,n;
    unsigned int length1; /*socklen*/
    unsigned int length2;
    char buf[1024];
    strcpy(buf,input);

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }
    /* Reused code from geekforgeeks*/
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(IP);
    addr.sin_port = htons(DST_PORT_A);
    length1=sizeof(struct sockaddr_in);

    memset(&srcaddr, 0, sizeof(srcaddr));
    srcaddr.sin_family = AF_INET;
    srcaddr.sin_addr.s_addr =  inet_addr(IP);
    srcaddr.sin_port = htons(SRC_PORT);
    length2=sizeof(struct sockaddr_in);

    if (bind(fd, (struct sockaddr *) &srcaddr, sizeof(srcaddr)) < 0) {
        perror("bind");
        exit(1);
    } 

   n=sendto(fd,buf,strlen(buf),0,(const struct sockaddr *)&addr,length1);
   if (n < 0) 
    {
     printf("Sendto error");
     exit(-1);
    }
   n = recvfrom(fd,buf,256,0,(struct sockaddr *)&srcaddr,&length2);
   float receivedvalue = atof(buf);
   if (n < 0) 
  { 
   printf("recvfrom error");
   exit(-1);
   }
   close(fd);  
  return (receivedvalue);
}

double UDP_B(char input[1024])
{
   struct sockaddr_in addr, srcaddr;
   int fd,n;
   unsigned int length1; /*socklen*/
   unsigned int length2;
   char buf[1024];
   strcpy(buf,input);

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(IP);
    addr.sin_port = htons(DST_PORT_B);
    length1=sizeof(struct sockaddr_in);

    memset(&srcaddr, 0, sizeof(srcaddr));
    srcaddr.sin_family = AF_INET;
    srcaddr.sin_addr.s_addr = INADDR_ANY;
    srcaddr.sin_port = htons(SRC_PORT);
    length2=sizeof(struct sockaddr_in);

    if (bind(fd, (struct sockaddr *) &srcaddr, sizeof(srcaddr)) < 0) {
        perror("bind");
        exit(1);
    } 

   n=sendto(fd,buf,strlen(buf),0,(const struct sockaddr *)&addr,length1);
   if (n < 0) 
    {
     printf("Sendto error");
     exit(-1);
    }
   n = recvfrom(fd,buf,256,0,(struct sockaddr *)&srcaddr,&length2);
   float receivedvalue = atof(buf);
   
   if (n < 0) 
  { 
   printf("recvfrom error");
   exit(-1);
   }
   
   close(fd);
   return (receivedvalue);  
}


double UDP_C(char input[1024])
{
   struct sockaddr_in addr, srcaddr;
   int fd,n;
   unsigned int length1; /*socklen*/
   unsigned int length2;
   char buf[1024];
   strcpy(buf,input);

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(IP);
    addr.sin_port = htons(DST_PORT_C);
    length1=sizeof(struct sockaddr_in);

    memset(&srcaddr, 0, sizeof(srcaddr));
    srcaddr.sin_family = AF_INET;
    srcaddr.sin_addr.s_addr =  inet_addr(IP);
    srcaddr.sin_port = htons(SRC_PORT);
    length2=sizeof(struct sockaddr_in);


    if (bind(fd, (struct sockaddr *) &srcaddr, sizeof(srcaddr)) < 0) {
        perror("bind");
        exit(1);
    } 

   n=sendto(fd,buf,strlen(buf),0,(const struct sockaddr *)&addr,length1);
   if (n < 0) 
    {
     printf("Sendto error");
     exit(-1);
    }
   n = recvfrom(fd,buf,256,0,(struct sockaddr *)&srcaddr,&length2);
   float receivedvalue = atof(buf);
   
   
  if (n < 0) 
  { 
   printf("recvfrom error");
   exit(-1);
   }
   
   close(fd);
   return (receivedvalue);  
}

void calculation_part(int sock);

int main()
{
    int sock, new_socket;
    int pid;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    
      
    // Creating socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
   printf("The AWS is up and running\n");
      
    // Forcefully attaching socket to the port 8080
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
      
    // Forcefully attaching socket to the port 25882
    if (bind(sock, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(sock, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
while(1)/*reused this code from linuxhowtoos*/
{
    new_socket = accept(sock, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen);
   if(new_socket<0)
    {
        printf("Error in accepting");
        exit(EXIT_FAILURE);
    }
   pid=fork();
   if(pid<0)
  {
    printf("Error in creating fork");
  }
 if (pid == 0)  {
             close(sock);
             calculation_part(new_socket);
             exit(0);
         }

   else close(new_socket);
 }
close(sock);
return(0);
}


void calculation_part(int sock)  /*Reused this function methodology from linuxhowtos*/

{
    
   int valread,n;
   char buffer[1024];
   valread = read( sock , buffer, 1024);
   char str1[256] = " ";
   char str2[256] = " ";
   char *p;
   p =strtok(buffer," ");
   if (p !=NULL)
   {
     strcpy(str1,p);
     p = strtok(NULL," ");
     if (p!= NULL)
       strcpy(str2,p);
    }
   
   printf("The AWS received <%s>",str2);
   printf(" and function <%s>",str1);
   printf(" from the client using TCP over port <%d>\n",TCP_PORT);
   double x_power_1= atof(str2);
  
  
/*String comparison*/
 char string_comp1[] ="LOG";
 char string_comp2[] = "Log";
 char string_comp3[]="log";
 char string_comp4[] ="DIV";
 char string_comp5[] = "Div";
 char string_comp6[] = "div" ; 
 int result1= strcmp(str1,string_comp1);
 int result2= strcmp(str1,string_comp2);
 int result3= strcmp(str1,string_comp3);
 int result4 = strcmp(str1,string_comp4);
 int result5 = strcmp(str1,string_comp5);
 int result6= strcmp(str1,string_comp6);

{ 
if(result1==0 || result2==0 || result3==0)
 {
   /*Receiving the square value and fourth value power from server A*/
printf("The AWS sent <%s>",str2);
printf(" to Backend-Server A\n");
     char conv_1[1024];
     double square_value= UDP_A(str2);
     snprintf(conv_1,sizeof(conv_1),"%.10f",square_value);
     printf("The AWS received <%g>",square_value);
     printf(" Backend-Server A");
     printf(" using the UDP over port <%d>\n",DST_PORT_A);
     char conv_2[1024];
     snprintf(conv_2,sizeof(conv_2),"%.8f",square_value);
     float fourth_power_value=UDP_A(conv_1);
     printf("The AWS received <%g>",fourth_power_value);
     printf(" Backend-Server A");
     printf(" using the UDP over port <%d>\n",DST_PORT_A);
     


/*Receiving the cube value and 6th power value from server B*/
printf("The AWS sent <%s>",str2);
printf(" to Backend-Server B\n");
     double cube_value= UDP_B(str2);
    printf("The AWS received <%g>",cube_value);
     printf(" Backend-Server B");
     printf(" using the UDP over port <%d>\n",DST_PORT_B);
    char conv_3[1024];
    snprintf(conv_3,sizeof(conv_3),"%.8f",cube_value);
    double sixth_value=UDP_B(conv_1);
    printf("The AWS received <%g>",sixth_value);
     printf(" Backend-Server B");
     printf(" using the UDP over port <%d>\n",DST_PORT_B);
    
  
/*Receiving the 5th power value from server C*/
   printf("The AWS sent <%s>",str2);
 printf(" to Backend-Server C\n");
  double fifth_value=UDP_C(str2);
  printf("The AWS received <%g>",cube_value);
     printf(" Backend-Server C");
     printf(" using the UDP over port <%d>\n",DST_PORT_C);
   
  

/*Final values received by the AWS server*/
printf("Values of power received by AWS:");
printf("[%g,%g,%g,%g,%g,%g]\n",x_power_1,square_value,cube_value,fourth_power_value,fifth_value,sixth_value);

/*Log function calculation*/

   double logarithm;
   logarithm= -((x_power_1) + (square_value/2) + (cube_value/3) + (fourth_power_value/4) + (fifth_value/5) + (sixth_value/6));
   char send_back_to_client[1024];
   snprintf(send_back_to_client,sizeof(send_back_to_client),"%.8f",logarithm);
   printf("AWS calculated <%s>",str1);
   printf(" on <%s>",str2);
   printf(" : <%g>\n",logarithm);
  

/*sending back the result to the client*/

n = write(sock,send_back_to_client,strlen(send_back_to_client));
 if (n < 0) 
    {
     printf("ERROR writing to socket");
     exit(-1);
     }
 }
 else if(result4==0 || result5==0 || result6==0)
  {
  /*AWS sending values to the backend server and receiving value from A*/
    printf("The AWS sent <%s>",str2);
    printf(" to Backend-Server A\n");
     char conv_1[1024];
     double square_value= UDP_A(str2);
     snprintf(conv_1,sizeof(conv_1),"%.10f",square_value);
     printf("The AWS received <%g>",square_value);
     printf(" Backend-Server A");
     printf(" using the UDP over port %d\n",DST_PORT_A);
     char conv_2[1024];
     snprintf(conv_2,sizeof(conv_2),"%.10f",square_value);
     double fourth_power_value=UDP_A(conv_1);
     printf("The AWS received %g",fourth_power_value);
     printf(" Backend-Server A");
     printf(" using the UDP over port %d\n",DST_PORT_A);
     
/*Receiving the cube value and 6th power from server B*/    
printf("The AWS sent <%s>",str2);
printf(" to Backend-Server B\n");
     double cube_value= UDP_B(str2);
    printf("The AWS received <%g>",cube_value);
     printf(" Backend-Server B");
     printf(" using the UDP over port <%d>\n",DST_PORT_B);
    char conv_3[1024];
    snprintf(conv_3,sizeof(conv_3),"%.10f",cube_value);
    double sixth_value=UDP_B(conv_1);
    printf("The AWS received <%g>",sixth_value);
     printf(" Backend-Server B");
     printf(" using the UDP over port <%d>\n",DST_PORT_B);

/*Receiving the 5th power from the server C */    
printf("The AWS sent <%s>",str2);
 printf(" to Backend-Server C\n");
  double fifth_value=UDP_C(str2);
  printf("The AWS received <%g>",fifth_value);
  printf(" Backend-Server C");
  printf(" using the UDP over port <%d>\n",DST_PORT_C);
  
  
/*Final values received by the AWS server*/
printf("Values of power received by AWS:");
printf("[%g,%g,%g,%g,%g,%g]\n",x_power_1,square_value,cube_value,fourth_power_value,fifth_value,sixth_value);

/*Division function calculation*/

   double division;
   division= (1 + (x_power_1) + (square_value) + (cube_value) + (fourth_power_value) + (fifth_value) + (sixth_value));
   char send_back_to_client[1024];
   snprintf(send_back_to_client,sizeof(send_back_to_client),"%.8f",division);
   printf("AWS calculated <%s>",str1);
   printf(" on <%s>",str2);
   printf(" : <%g>\n",division);
  
/*sending back the result to the client*/

n = write(sock,send_back_to_client,strlen(send_back_to_client));
 if (n < 0) 
    {
     printf("ERROR writing to socket");
     exit(-1);
     }
  }
else
{
  printf("Wrong input\n");
  exit(-1);
 }
}
}
    

