#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>	

/*
Écrivez un programme qui crée deux processus, un père qui affiche à 
l’aide de l’appel système write la chaîne "Je suis le père\n", 
et un fils qui affiche la chaîne "Je suis le fils\n". (Vous n’omettrez
pas d’attendre la mort du fils à l’aide de wait.) Quel est l’ordre 
des chaînes affichées ? Un autre résultat est-il possible ?
*/

int main()
{
	pid_t pid;
	const char message_pere[] = "je suis le père\n";
	const char message_fils[] = "je suis le fils\n";
	
	switch (pid = fork())
	{
		case -1:
			fprintf(stderr, "Erreur....");
			break;
					
		case 0:
			write( STDOUT_FILENO, message_fils, sizeof(message_fils) - 1 );
			
		default : 
			write( STDOUT_FILENO, message_pere, sizeof(message_pere) - 1 );
			waitpid(pid, NULL, 0);	
			break;
			
	}
	
	return 0;
	
}
