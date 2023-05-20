#include "main.h"

/**
* parse_line - Parses a line into an array of tokens.
* @line: The input line to parse.
*
* Return: An array of tokens.
*/
char **parse_line(char *line)
{
const char *delimiters = " \t\r\n\a";
char **argv = NULL;
char *token;
int i = 0;

argv = malloc(sizeof(char *) * 64);
if (argv == NULL)
{
perror("malloc");
exit(EXIT_FAILURE);
}
token = strtok(line, delimiters);
while (token != NULL)
{
argv[i] = token;
i++;
token = strtok(NULL, delimiters);
}
argv[i] = NULL;
return (argv);
}
/**
* execute_command - Executes a command with its arguments.
* @command: The command to execute.
* @argv: An array of arguments for the command.
*
* Return: 0 on success, -1 on failure.
*/
int execute_command(char *command, char **argv)
{
if (custom_strcmp(command, "exit") == 0)
{
exit(EXIT_SUCCESS);
}
else if (custom_strcmp(command, "env") == 0)
{
char **env = environ;

while (*env != NULL)
{
custom_puts(*env);
custom_putchar('\n');
env++;
}
return (0);
}
else
{
pid_t pid = fork();
if (pid == -1)
{
handle_error("fork");
}
else if (pid == 0)
{
/* Child process */
execvp(command, argv);

/* If execvp returns, an error occurred */
handle_error("execvp");
}
else
{
/* Parent process */
int status;

if (waitpid(pid, &status, 0) == -1)
{
handle_error("waitpid");
}
}
}
return (0);
}
