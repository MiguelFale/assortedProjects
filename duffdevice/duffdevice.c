#include <stdio.h>
/*#define MAX 100000*/
#define MAX 10

void printarray(const short* arr, int size) {
	int i = 0;
	for(i=0; i < size; i++) {
		printf("%d\n",arr[i]);
	}
}

void send(short* to, short* from, int count) {
	do {
		*to++ = *from++;
	} while(--count>0);
}

void sendduff(short* to, short* from, int count) {
	int n=(count+7)/8;
	printf("register %d\n",n);
	printf("register%%8 %d\n",n%8);
	switch(count%8){
		case 0:	do{	*to++ = *from++;
				printf("case 0\n");
		case 7:		*to++ = *from++;
				printf("case 7\n");
		case 6:		*to++ = *from++;
				printf("case 6\n");
		case 5:		*to++ = *from++;
				printf("case 5\n");
		case 4:		*to++ = *from++;
				printf("case 4\n");
		case 3:		*to++ = *from++;
				printf("case 3\n");
		case 2:		*to++ = *from++;
				printf("case 2\n");
		case 1:		*to++ = *from++;
				printf("case 1\n");
			}while(--n>0);
	}
}

int main() {
	short arr1[MAX] = {1,2,3,4,0,6,7,9,8,5};
	short arr2[MAX];

	printf("Now printing arr1(before)!\n");
	printarray(arr1,MAX);
	printf("Now printing arr2(before)!\n");
	printarray(arr2,MAX);

	sendduff(arr2,arr1,MAX);

	printf("Now printing arr1(after)!\n");
	printarray(arr1,MAX);
	printf("Now printing arr2(after)!\n");
	printarray(arr2,MAX);
	return 0;
}