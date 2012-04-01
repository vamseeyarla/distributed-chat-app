/* 
 * File:   main.cpp
 * Author: VamseeKYarlagadda
 *
 * Created on March 27, 2012, 9:55 PM
 */

#include <cstdlib>
#include<unistd.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include <arpa/inet.h>
#include<sys/poll.h>
#include<iostream>


#define PORT 1111
using namespace std;

/*
 * 
 */
int main(int argc, char* argv[]) {
  bool host;
  char* name;
  int socdesc;
  char buffer[100];
  int n;
  struct sockaddr_in hostaddr, clientaddr, incaddr;
  socklen_t length=sizeof(clientaddr);
  struct pollfd descriptors[2];
  int pollVal;
  char *incomingAddress;
  
  if(argc == 2){
    host = 1;
  }
  else{
    host = 0;
    char* ip_addr = strtok(argv[2],":");
    int port = atoi(strtok(NULL, ":"));
    
    hostaddr.sin_port=htons(port);
    hostaddr.sin_family=AF_INET;
    inet_aton(ip_addr,&hostaddr.sin_addr);
  }
  clientaddr.sin_port=htons(PORT);
  clientaddr.sin_family=AF_INET;
  clientaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  
  name = argv[2];
  
  if((socdesc=socket(AF_INET,SOCK_DGRAM,0))==-1)
  {
      perror("Socket!");
      exit(1);
  }
    
    
    
    if((bind(socdesc, (struct sockaddr *)&clientaddr, sizeof(struct sockaddr))==-1))
    {
        perror("Bind!");
        exit(1);
    }
    
    
    descriptors[0].fd=fileno(stdin);
    descriptors[0].events=POLLIN;
    
    descriptors[1].fd=socdesc;
    descriptors[1].events=POLLIN;
    
    
    while(1)
    {
      //  perror("Value Up:");
       // cout<<"Value: "<<fileno(stdin);
        
        pollVal=poll(descriptors,2,-1);
       
              
        if(pollVal ==-1)
        {
            perror("Poll!");
            exit(1);
        }
        else if(pollVal==0)
        {
            perror("Poll Timeout!");
        }
        else
        {
       
            if(descriptors[1].revents & POLLIN)
            {
     //reset buffer             
     if( (n=recvfrom(socdesc,buffer,sizeof(buffer),0, (struct sockaddr *)&incaddr,&length))==-1)
     {
         perror("RecvFrom!");
         exit(1);
     }
     
     //function call to requestHandler
     
     
//     incomingAddress = inet_ntoa(cliaddr.sin_addr);
//     write(1,strcat(incomingAddress,":"),strlen(incomingAddress)+1);
//   
//    buffer[n]='\0';
//    write(1,buffer,strlen(buffer));
//    
//      if(strcmp(buffer,"bye\n")==0)
//    {
//        break;
//    }
            }
            
            if(descriptors[0].revents & POLLIN)
            {     
    n=read(fileno(stdin),buffer,sizeof(buffer));
    buffer[n]='\0';
    
    //this will be another method(request global sequence id)
    
//    if(sendto(socdesc,buffer,strlen(buffer),0,(struct sockaddr *)&cliaddr, sizeof(cliaddr))==-1)
//    {
//        perror("SendTo!");
//        exit(1);
//    }
//    
//    if(strcmp(buffer,"bye\n")==0)
//    {
//        break;
//    }
            }
        }
    
    }
    perror("Program Shutdown!");
    close(socdesc);
    
}

