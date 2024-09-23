#include <stdio.h>
#include "alloc.h"

int main()
{	
	printf("META SIZE hex: %lx\n", META_SIZE);

	int *p = m_alloc(sizeof(int));
	*p = 1;

	int len = 26;
	char *str = (char *)m_alloc(len * sizeof(char));

	for (int i = 0; i < len; ++i) {
		str[i] = i + 'A';
	}

	printf("%p\n", str - 1);

	print_blocks();
	char *s = (char *)(p + 1 + META_SIZE);
	printf("%s\n", s);

	return 0;	
}



