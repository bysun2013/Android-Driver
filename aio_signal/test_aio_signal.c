/*
 * test_aio_signal.c
 *
 *  Created on: Oct 9, 2013
 *      Author: bing
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <aio.h>

#define BUF_SIZE 100
#define MAX_LIST 1

struct aiocb my_aiocb;
const struct aiocb* cblist[MAX_LIST];

void signal_handler(int signo){
	int ret;
	ret=aio_read(&my_aiocb);
	if(ret <0)
		perror("aio_read");

	ret=aio_suspend(cblist, MAX_LIST, NULL);
	if(ret <0)
		perror("aio_suspend");

	if((ret=aio_return(&my_aiocb)) >0)
	{
		printf("value:%s\n", (char*)my_aiocb.aio_buf);
		memset((char*)my_aiocb.aio_buf, 0, BUF_SIZE);
	}
}

int main(){
	int flag, fd, ret;
	fd=open("/dev/aio_signal", O_RDWR);
	if(fd<0)
		printf("Error occurred in open file.\n");

	bzero((void*)&my_aiocb, sizeof(struct aiocb));
	bzero((void*)&cblist, sizeof(cblist));
	cblist[0]=&my_aiocb;
	if(!(my_aiocb.aio_buf=malloc(BUF_SIZE+1)))
		perror("malloc error");

	my_aiocb.aio_fildes=fd;
	my_aiocb.aio_nbytes=BUF_SIZE;
	my_aiocb.aio_offset=0;

	signal(SIGIO, signal_handler);
	fcntl(fd, F_SETOWN, getpid());
	flag = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, flag|FASYNC);

	while(1)
		sleep(100);

	return 0;
}

