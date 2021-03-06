#define _UNICODE
#define UNICODE
#include <stdio.h>
#include <errno.h>
#include <strings.h>
#include <string.h>
#include <iostream>
#include <sys/types.h> //for sockadd_in
#include <unistd.h> //for fork execl,
#include <sys/wait.h> //for waitpid
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../include/LogInterface.h"
#include "../include/Func.h"
#include "NetConstant.h"
#include <iconv.h>
#pragma comment(lib,"libiconv.lib")
using namespace std;


//when child exit,call this func to protect it become zombie
void sig_chld_exit(int signo){
	pid_t pid;
	int stat;
	while((pid=waitpid(-1,&stat,WNOHANG))>0)
		printf("child %d terminated\n",pid);
	return ;


}
struct Test{
	int first;
	int second;
	//char msg[10];
	//wchar_t msg[10];
	string msg;

};
ssize_t readn(int fd,void *vptr,size_t n){
	size_t nleft;
	ssize_t nread;
	char *ptr;
	
	ptr=(char*)vptr;
	nleft=n;

	while(nleft>0){
		if((nread=read(fd,ptr,nleft))<0){
			if(errno==EINTR)
				nread=0;
			else
				return (-1);
			
		}else if(nread==0)
			break;
		nleft=nleft-nread;
		ptr=ptr+nread;
	
	

	}
	return (n-nleft);



}

ssize_t writen(int fd,const void *vptr,size_t n){
	
	size_t nleft;
	ssize_t nwritten;

	const char *ptr;
	ptr=(char*)vptr;
	//wcout<<"start write"<<endl;
	nleft=n;
	
	while(nleft>0){
		if((nwritten=write(fd,ptr,nleft))<=0){
			if(nwritten<0&&errno==EINTR){
				wcout<<"nwritten<0"<<endl;
				nwritten=0;
			}else{
				wcout<<"-1"<<endl;
				return (-1);
			}

		}
		nleft=nleft-nwritten;
		ptr=ptr+nwritten;
//		wcout<<"yes"<<endl;

	}
	//wcout<<"write complete"<<endl;
	return n;

}

int main(){
	int listenfd;//the listen fd
	int connfd;//the client fd
	
	struct sockaddr_in cliaddr;//client addr
	struct sockaddr_in servaddr;//server addr
	
	//listen
	if(-1==(listenfd=socket(AF_INET,SOCK_STREAM,0))){//use IPv4 and tcp
		wcout<<"socket init failed"<<endl;
		exit(1);
	}
	
	bzero(&servaddr,sizeof(servaddr));//zero the server addr

	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(PORT);
	servaddr.sin_addr.s_addr=INADDR_ANY;


	//bind the socket port
	if(-1==bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))){
		wcout<<"bind failed!"<<endl;
		exit(1);
	}
	
	if(-1==listen(listenfd,BACKLOG)){
		wcout<<"listen failed!"<<endl;
		exit(1);
	}
	
	//signal(SIGCHLD,sig_chld_exit);//recive the child process SIGCHLD signal
	
	for(;;){
		socklen_t clilen=sizeof(cliaddr);	
		
		connfd=accept(listenfd,(struct sockaddr*)&cliaddr,&clilen);//accept the client connections
		
		//wcout<<"at time "<<GetTimeNow()<<" "<<inet_ntoa(cliaddr.sin_addr)<<" connectiosn"<<endl;
		
		//fork the child process
	//	if(fork()==0){
			wcout<<"sizeof(string)="<<sizeof(string)<<endl;
			Test msg;
			while(true){
				//memset(&msg,0,sizeof(msg));
				//char buf[MAXSIZE];
				//int rval;
				//read the stream
				//if((rval=read(connfd,buf,MAXSIZE))>0){
				//	wcout<<"read the msg "<<buf<<endl;
				//}
				ssize_t n;
				if((n=readn(connfd,&msg,sizeof(msg)))==0)
					continue;
				wcout<<"msg.first="<<msg.first<<" ,msg.second="<<msg.second<<endl;
				//wcout<<"msg.msg="<<msg.msg<<endl;
				//int sum=msg.first+msg.second;
				//string welcome="hello,welcome to guang server\n";
				//string ms=welcome+IntToStr(sum);
				
				Test sersum;
				sersum.first=33;
				sersum.second=44;
				sersum.msg="guangs";
				writen(connfd,&sersum,sizeof(sersum));
				//writen(connfd,&msg,sizeof(msg));
				
				/**if(send(connfd,ms.c_str(),ms.length(),0)==-1){
					wcout<<"send error!\n"<<endl;
					close(connfd);
					exit(0);
				}*/
				
			}

	//	}
		close(connfd);
	

	}
	
}
