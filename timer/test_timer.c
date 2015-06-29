#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/time.h>

int main(){
  int fd;
  int counter, old_counter;
  fd=open("/dev/timer_demo", O_RDONLY);
  if(fd != -1)
  {
       while(1)
       {
	    read(fd, &counter, sizeof(int));
	    if(counter != old_counter){
		 printf("seconds after open /dev/timer_demo: %d.\n",counter);
		 old_counter = counter;
	    }
       }
  }else
       printf("Device open failure.\n");
  close(fd);
}
