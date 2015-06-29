#include <stdio.h>

int main(){
	int m=1;
	int n=2;
	int i=0;
	m=m+n;
	for(;i<20;i++)
		m=m+i;
	printf("m=%d\n",m);
	return 0;
}
