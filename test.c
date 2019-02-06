#include <stdio.h>

void	func(int * const p)
{
	printf("*p = %d\n", *p);
	p[0] = 50;
	p = NULL;
}

int main(void)
{
	int b;
	int *p;

	
	b = 20;
	p = &b;
	b = 30;
	printf("b = %d\n", b);
	func(p);
	printf("b = %d\n", b);

	p = NULL;
	
	return (0);
}
