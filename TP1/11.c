#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>	
#define SIZE 10000

int main(int argc, char*argv [])
{
	pid_t pid;
	srand( time( NULL ) );
	int tab[SIZE];
	
	if (argc != 2)
	{
		fprintf(stderr, "le nombre d'arguments n'est pas compatible..");
		return EXIT_FAILURE;	
	}
	
	for (int i = 0; i < SIZE; i++)
		tab[i] = rand() % 1001;
	
	if (atoi(argv[1]) > 2)
	{
		for (int i = 0; i < atoi(argv[1]); i++)
		{
			switch (pid = fork())
			{
				case -1:
					fprintf(stderr, "Erreur....");
					break;
							
				case 0:
					printf("je suis le fils\n");
					for (int i = SIZE/2; i < SIZE; i++)
					{
						if (tab[i] == 42)
							printf("%d\n",i);
					}
					
				default : 
					printf("je suis le père\n");
					for (int i = 0; i < SIZE/2 ; i++)
					{
						if (tab[i] == 42)
							printf("%d\n",i);
					}
					waitpid(pid, NULL, 0);	
					break;
					
			}
		}
	}
	else if (atoi(argv[1]) == 2){
		switch (pid = fork())
		{
				case -1:
					fprintf(stderr, "Erreur....");
					break;
							
				case 0:
					printf("je suis le fils\n");
					for (int i = SIZE/2; i < SIZE; i++)
					{
						if (tab[i] == 42)
							printf("%d\n",i);
					}
					
				default : 
					printf("je suis le père\n");
					for (int i = 0; i < SIZE/2 ; i++)
					{
						if (tab[i] == 42)
							printf("%d\n",i);
					}
					waitpid(pid, NULL, 0);	
					break;
					
		}
		
	}
	
	
	return 0;
	
}
