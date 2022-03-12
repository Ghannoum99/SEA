#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 1000

//fonction permettant de décomposer (parser) l'entrée de l'utilisateur en tokens
void entry_parser(char cmd[])
{
    char * tokens = strtok(cmd, " \t\n");

    while( tokens != NULL)
    {
        //on teste si l'utilisateur a entré la chaine "exit"
        if (!strcmp(tokens, "exit"))
            exit(0);
        
        else
            printf("%s\n", tokens);
        
        //on demande le token suivant
        tokens = strtok(NULL, " \t\n");
    }
}

int main(int argc, char* argv[])
{
	char cmd[SIZE];
    char cwd[SIZE];

	while(!feof(stdin))
    {
        printf("%s %%", getcwd(cwd, sizeof(cwd)));
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strlen(cmd)-1]='\0';

        entry_parser(cmd);
			 
    }
	
	return 0;
}
