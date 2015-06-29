#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

int main(){
	int fd, num;
	fd_set rfds, wfds;
	char buf[20];

	memset(buf,0,20);
	fd=open("/dev/poll_select", O_RDWR|O_NONBLOCK);
	if(fd !=-1){
		while(1){
			FD_ZERO(&rfds);
			FD_ZERO(&wfds);
			FD_SET(fd, &rfds);
			FD_SET(fd, &wfds);

			select(fd+1, &rfds, &wfds, NULL, NULL);

			if(FD_ISSET(fd, &rfds)){
				printf("Data can be read!\n");
				read(fd, buf, 20);
				printf("value:%s\n",buf);
				memset(buf,0,20);
			}

			if(FD_ISSET(fd, &wfds))
				printf("Data can be written!\n");
			
			sleep(1);
		}
	}else
		printf("Device open fail!\n");
}

