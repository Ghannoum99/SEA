#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 10000

int main()
{
	pid_t pid;
	srand( time( NULL ) );
	
	int tab[SIZE];
	
	for (int i = 0; i < SIZE; i++)
		tab[i] = rand() % 1001;
		
	for (int i = 0; i < SIZE; i++)
	{
		if (tab[i] == 42)
			printf("%d\n",i);
	}
	
	return 0;
}
	
