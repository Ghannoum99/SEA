#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>	

/*
 Écrivez un programme qui crée deux processus, un père qui affiche à 
 * l’aide de l’appel système write la chaîne “a” 10 000 fois, et un fils
 *  qui affiche la chaîne “b” 10 000 fois. (Comme d’habitude, pensez à 
 * wait.) Que constatez-vous ?
 */ 


int main()
{
	pid_t pid;
	switch (pid = fork())
	{
		case -1:
			fprintf(stderr, "Erreur....");
			break;
					
		case 0:
			for (int i = 1; i <= 10000; i++)
				write( STDOUT_FILENO, "b\n", sizeof("b\n") - 1 );
			
		default : 
			for (int i = 1; i <= 10000; i++)
				write( STDOUT_FILENO, "a\n", sizeof("a\n") - 1 );
				
			waitpid(pid, NULL, 0);
			break;
			
	}
	
	return 0;
}
