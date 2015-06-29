#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

#define LEN 100
int fd;

void signal_handler(int signo){

	static int count =0;
	fd_set rfds, wfds;
	char buf[LEN];
	memset(buf, 0, LEN);

	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	FD_SET(fd, &rfds);
	FD_SET(fd, &wfds);

	select(fd+1, &rfds, &wfds, NULL, NULL);

	if(FD_ISSET(fd, &rfds)){
		printf("Data can be read!\n");
		read(fd, buf, LEN);
		printf("value:%s\n",buf);
	}

	if(FD_ISSET(fd, &wfds))
		printf("Data can be written!\n");

	printf("signal:%d \n",signo);
	printf("count: %d\n",++count);
	printf("-----------------\n");
}

int main(){
	int flag;
	fd=open("/dev/signal", O_RDWR);
	if(fd>0){
		signal(SIGIO, signal_handler);
		fcntl(fd, F_SETOWN, getpid());
		flag = fcntl(fd, F_GETFL);
		fcntl(fd, F_SETFL, flag|FASYNC);
		while(1)
			sleep(100);
	}else
		printf("Error occurred in open file.\n");
}

