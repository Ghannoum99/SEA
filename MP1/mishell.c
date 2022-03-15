#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 1000
#define PATH_SIZE 4096

/*
//fonction permettant de décomposer (parser) l'entrée de l'utilisateur en tokens
void entry_parser(char cmd[])
{
    char * tokens = strtok(cmd, " \t\n");
    char * directory;
    char cwd[PATH_SIZE];
    bool cd_args = false;

    while( tokens != NULL)
    {
        //on teste si l'utilisateur a entré la chaine "exit"
        if (!strcmp(tokens, "exit"))
            exit(0);

        //si la commande entrée est un cd
        else if (!strcmp(tokens, "cd"))
        {
            //printf("2\n");
            directory = tokens;
            
            chdir(directory);
            //printf("%s %%", getcwd(cwd, sizeof(cwd)));
            //printf("1\n");
        }
            
        else
        {
            printf("1\n");
            printf("%s\n", tokens);
        }
        //on demande le token suivant
        tokens = strtok(NULL, " \t\n");
    }
}
*/

//fonction permettant de décomposer (parser) l'entrée de l'utilisateur en tokens
void entry_parser(char cmd[], char ** tokens)
{
    for (int i = 0; i < SIZE; i++)
    {
        tokens[i] = strsep(&cmd, " \t\n");
        if (tokens[i] == NULL)
            break;
        if (strlen(tokens[i]) == 0)
            i--;
    }
}

//fonction permettant d'executer la commande selon sa nature.
void exec_cmd(char ** tokens)
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
            //si le repertoire reste toujours le même alors tokens[1] (argument) n'existe pas
            chdir(tokens[1]);
            break;

        default:
            printf("%s\n", tokens[0]);
    }
}

//fonction permettant d'afficher le repertoire courant
void print_dir()
{
    char cwd[PATH_SIZE];
    printf("%s %%", getcwd(cwd, sizeof(cwd)));
}

int main()
{
	char cmd[SIZE];
    char ** tokens;

    tokens = malloc(sizeof(char*)*SIZE);
    for(int i = 0; i < SIZE; i++) 
    {
        tokens[i] = malloc(sizeof(char)*SIZE);  
    }
    
	while(!feof(stdin))
    {
        print_dir();
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strlen(cmd)-1]='\0';

        entry_parser(cmd, tokens);
        exec_cmd(tokens);
			 
    }
	


    for(int i = 0; i < SIZE; i++) 
        free(tokens[i] );
    free(tokens); 
	return 0;
}
