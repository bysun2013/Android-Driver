#include <stdio.h>
#include <errno.h>

int main(){
	int handler =open("/dev/rw_lock",0);
	char buf[5];
	if(handler>0){
		read(handler, buf, 4);
		buf[4]='\0';

		printf("%s\n",buf);
		close(handler);
	}else{
		printf("errno: %d\n",errno);
	}
	return 0;
}
