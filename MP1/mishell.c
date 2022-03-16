#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZE 4096


//fonction permettant de décomposer (parser) l'entrée de l'utilisateur en tokens
void entry_parser(char cmd[], char ** tokens)
{
    for (int i = 0; i < SIZE; i++)
    {   //recuperer l'entrée de l'utilisateur et la décomposer en tokens
        tokens[i] = strsep(&cmd, " \t\n");
        if (tokens[i] == NULL)
            break;
        if (strlen(tokens[i]) == 0)
            i--;
    }
}

//fonction permettant d'executer une commande (autre que exit et cd) entrée par l'utilisateur
void execute_cmds(char **tokens)
{
	pid_t	pid = 0;
	int	status = 0;

	// On fork
	pid = fork();

	if (pid == -1)
		perror("fork");

	// Si le fork a reussit, le processus pere attend l'enfant (process fork)
	else if (pid > 0) {

		// On block le processus parent jusqu'a ce que l'enfant termine puis		
		waitpid(pid, &status, 0);

	} else {

		// Le processus enfant execute la commande ou exit si execve echoue
		if (execvp(tokens[0], tokens) == -1)
			perror("shell");

		exit(EXIT_FAILURE);
	}
}

//fonction permettant d'identifier la commande entree par l'utilisateur
// si la cmd = "exit" --> on quitte le programme
// si la cmd = "cd <arg>" on change le repertoire courant
//si autre cmd on appelle la fct execute_cmd
void identify_cmd(char ** tokens)
{
    int nb_cmds = 2;
    int switch_own_cmds = 0;
    char * list_own_cmds[nb_cmds];

    list_own_cmds[0] = "exit";
    list_own_cmds[1] = "cd";

    for (int i = 0; i < nb_cmds; i++)
    {
        if (strcmp(tokens[0], list_own_cmds[i]) == 0)
        {
            switch_own_cmds = i + 1;
            break;
        }
    }

    switch (switch_own_cmds)
    {
        case 1:
            exit(0);

        case 2:
            if (tokens[1] == NULL)
                printf("%s\n", tokens[0]); 

            //faut ajouter une condition pour afficher une erreur si le tokens[1] n'existe pas 
            //Pour l'instant si le repertoire reste toujours le même alors tokens[1] (argument) n'existe pas
            chdir(tokens[1]);
            break;

        default:
            //printf("%s\n", tokens[0]);
            execute_cmds(tokens);
    }
}

//fonction permettant d'afficher le repertoire courant
void print_dir()
{
    char cwd[SIZE];
    printf("%s %%", getcwd(cwd, sizeof(cwd)));
}

int main()
{
	char cmd[SIZE];
    char ** tokens = NULL;

    //allocation dynamique de tokens
    tokens = (char **)malloc(sizeof(char*)*SIZE);

    //on verifie si la memoirea été allouée
    if (tokens == NULL)
    {
        printf("Échec de l'allocation\n");
        return EXIT_FAILURE;
    }

    for(int i = 0; i < SIZE; i++) 
    {
        tokens[i] = malloc(sizeof(char)*SIZE);
        if (tokens[i] == NULL)
        {
            printf("Échec de l'allocation\n");
            return EXIT_FAILURE;
        }  
    }
    
	while(!feof(stdin))
    {
        print_dir();
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strlen(cmd)-1]='\0';

        entry_parser(cmd, tokens);
        exec_cmd(tokens);	 
    }

    //desallocation de tokens
    //for(int i = 0; i < SIZE; i++) 
      //  free(tokens[i]);

    free(tokens);
 
	return 0;
}
