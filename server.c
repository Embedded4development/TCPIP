#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 
#include<signal.h>

//Server...

int status = 1;
void myfunction(int S)
{
  printf("closing\n");
  status = 0;

}


int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

    char sendBuff[1025];
    char ack[15];
    time_t ticks; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    struct sigaction handler;
    handler.sa_handler = myfunction;
    sigemptyset(&handler.sa_mask);
    handler.sa_flags = 0;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 

    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 

       // ticks = time(NULL);
       if(fork()==0)
       {
        snprintf(sendBuff, sizeof(sendBuff), "%s\r\n","connection established");
        write(connfd,sendBuff,strlen(sendBuff)); 

      	 while(1)
       	 {  
            if(read(connfd,ack, strlen(ack)))
            {
      	      printf("%s\n",ack);
              
             }
        //     sleep(1);
          }
      
        sigaction(SIGINT,&handler,NULL);

        if(status == 0)
         {
            close(connfd);
            exit(1);
          }
       sleep(1);
      }
    }
}
