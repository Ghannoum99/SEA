#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 100

//fonction permettant de décomposer (parser) l'entrée de l'utilisateur en tokens
void entry_parser(char str[])
{
    char * str_token = strtok(str, " ");

    while( str_token != NULL)
    {
        printf("%s\n", str_token);
        //on demande le token suivant
        str_token = strtok(NULL, " ");
    }
}


int main(int argc, char* argv[])
{
	char str[SIZE];
	//variable de test
	bool var_test = 1;

	printf("%%");
	while(var_test)
    {
        fgets(str, (int) SIZE, stdin);

        if (!strcmp(str, "exit\n"))
			var_test = 0;
		else
        {
            entry_parser(str);
            printf("%%");
        }
			 
    }
	
	return 0;
}
