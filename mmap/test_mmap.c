#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>

#define PAGE_SIZE 4096*2
int main(){
     int fd;
     void *start;

     fd= open("/dev/mmap_demo", O_RDWR);
     start= mmap(NULL, PAGE_SIZE, PROT_READ, MAP_PRIVATE, fd, 0);
     if(start==MAP_FAILED){
	  printf("mmap error.\n");
	  return 0;
     }
     puts(start);
     munmap(start, PAGE_SIZE);
}
