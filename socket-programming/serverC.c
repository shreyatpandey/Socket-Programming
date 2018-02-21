#include<stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <netdb.h>
#include<math.h>


uint16_t DST_PORT  =  24882;
uint16_t SRC_PORT  =  23882;
#define IP      "127.0.0.1"


int main() 
  {
    struct sockaddr_in addr, srcaddr;
    int fd,n;
    socklen_t formlength;
    char buf[1024];
    float value;

    if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(IP);
    addr.sin_port = htons(DST_PORT);

    memset(&srcaddr, 0, sizeof(srcaddr));
    srcaddr.sin_family = AF_INET;
    srcaddr.sin_addr.s_addr =  inet_addr(IP);
    srcaddr.sin_port = htons(SRC_PORT);

    if (bind(fd, (struct sockaddr *) &srcaddr, sizeof(srcaddr)) < 0) {
        printf("binding error");
        exit(-1);
    } 
formlength=sizeof(struct sockaddr_in);
printf("The Server C is up and running using UDP on port <%i>\n",SRC_PORT);  

while (1) {
       n = recvfrom(fd,buf,256,0,(struct sockaddr *)&addr,&formlength);  
       printf("The Server C received the input <%s>\n",buf);
    if (n < 0) 
      { 
       printf("recvfrom error");
       exit(-1);
       }

/* fifth power calculation */
     
    
     double convertedresult=atof(buf);
     double fifth_value=pow(convertedresult,5);
    
     printf("The server C calculated 5th power: <%g>\n",fifth_value);
     char buf_send[1024];  
     snprintf(buf_send,sizeof(buf_send),"%.10f",fifth_value);
       printf("The server C finished sending the output to AWS\n");
       n = sendto(fd,buf_send,strlen(buf_send),0,(struct sockaddr *)&addr,formlength); 
       if (n  < 0) 
       {
        printf("sendto error");
        exit(-1);
        } 
     }
   close(fd);
    return 0;
}
