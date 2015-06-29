#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int file_handle=0;
	int cmd=0;
	int arg=0;
	
	if(argc < 4){
		printf("Usage: ioctl <dev_file> <cmd> <arg>");
		return 0;
	}
	
	cmd=atoi(argv[2]);
	arg=atoi(argv[3]);
	
	printf("dev= %s\t cmd=%d\n", argv[1], cmd);
	file_handle=open(argv[1], 0);
	
	ioctl(file_handle, cmd, arg);
	close(file_handle);
	
	return 0;
}
