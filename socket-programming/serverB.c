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
uint16_t SRC_PORT  =  22882;
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
printf("The Server B is up and running using UDP on port <%i>\n",SRC_PORT);  

   while(1)
    { 
       n = recvfrom(fd,buf,256,0,(struct sockaddr *)&addr,&formlength);  
       printf("The Server B received the input <%s>\n",buf);
    if (n < 0) 
      { 
       printf("recvfrom error");
       exit(-1);
       }

/* cube calculation*/
     
     
     double convertedresult=atof(buf);
    double cube_value = pow(convertedresult,3);
   /* double cube_value = (convertedresult)*(convertedresult)*(convertedresult); */
     printf("The server B calculated cube: <%g>\n",cube_value); 
     char buf_send[1024];  
     snprintf(buf_send,sizeof(buf_send),"%.10f",cube_value);
      
       n = sendto(fd,buf_send,sizeof(buf_send),0,(struct sockaddr *)&addr,formlength); 
       if (n  < 0) 
       {
        printf("sendto error");
        exit(-1);
        }
      printf("The server B finished sending the output to AWS\n"); 
     }

   close(fd);
    return 0;
}

