#include <stdio.h>
#include <errno.h>

int main(){
	int handle=open("/dev/atomic",0);
	printf("handle: %d.\n",handle);

	if(handle>0){
		getchar();
		close(handle);
	}else
		printf("Error:%d \n", errno);
	
	return 0;
}
