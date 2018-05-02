#include <stdio.h>


void fun(void)
{
		int *p = NULL;
		*p = 9;
}

int main(void)
{
		fun();

		return 0;
}
