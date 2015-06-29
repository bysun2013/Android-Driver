/*
 * leds_hal_test.c
 *
 *  Created on: Oct 18, 2013
 *      Author: bing
 */


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

/*
 * when read from register, the second integer is always 33.
 *
 * */

int main(int argc, char *argv[]){
	int fd;
	if(argc < 4){
		printf("Please input again, usage is error");
		return 0;
	}
	char *cmd = argv[1];
	if(strcmp(cmd, "r") != 0 && strcmp(cmd, "w") != 0){
		printf("Please input again, usage is error");
		return 0;
	}

	char *dev_name = argv[2];
	int byte_counts = atoi(argv[3]);
	unsigned char buf[byte_counts];

	int i=0;

	if(strcmp(cmd, "w")==0){

		for(;i<byte_counts;i++)
			buf[i]= atoi(argv[4+i]);
		fd= open(dev_name, O_WRONLY);
		write(fd, buf, byte_counts);

	}else if(strcmp(cmd, "r")== 0){

		fd= open(dev_name, O_RDWR);
		buf[0] = atoi(argv[4]);
		printf("write before:\n");
		/*
		 * Right or not? argument is 1;
		 * why is 1 here?
		 * why write() syscall doesn't error?
		*/
		write(fd, buf, 1);
		printf("write after:\n");
		read(fd, buf, byte_counts);
		printf("%d bytes: ",byte_counts);
		for(;i< byte_counts; i++)
			printf("%d\t", buf[i]);
		printf("\n");

	}
		close(fd);
		return 0;

}
