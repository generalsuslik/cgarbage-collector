#include <stdio.h>
#include <stdlib.h>

#include "alloc.h"

struct test {
	int *arr;	
};

int main(int argc, char **argv) 
{
	printf("\nIn main\n\n");

	int len = 20;
	char *arr = (char *)m_calloc(len, sizeof(char));
	if (arr == NULL) {
		printf("ERR\n");
		exit(EXIT_FAILURE);
	}

	printf("DONE\n");
	for (int i = 0; i < len; ++i) {
		arr[i] = i + 'A';
	}

	m_free(arr);
	printf("\narr freed\n");

	arr = (char *)m_alloc(len * sizeof(char));
	if (arr == NULL) {
		printf("Error 2\n");
		exit(EXIT_FAILURE);
	}

	printf("DONE2\n");
	for (int i = len - 1; i >= 0; --i) {
		arr[len - i - 1] = i + 'A';
	}

	m_free(arr);
	printf("\narr2 freed\n");

	return 0;	
}



