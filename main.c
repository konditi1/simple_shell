#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* prompt - Displays the command prompt.
*/
void prompt(void)
{
/* Display the prompt */
custom_puts(" $ ");
}

/**
* handle_error - Handles error conditions and exits.
* @message: The error message to display.
*/
void handle_error(const char *message)
{
/* Print error message and exit */
perror(message);
exit(EXIT_FAILURE);
}

/**
* handle_other_errors - Handles other error conditions.
*
* This function is responsible for handling other error conditions,
* such as when the line length exceeds a certain limit.
*/
void handle_other_errors(void)
{
/* Handle other error conditions, such as line length exceeding a limit */
fprintf(stderr, "Error: Line too long\n");
}

/**
* main - Entry point of the program.
*
* This function implements the main loop of the program,
* where it prompts the user for input, reads the input line,
* and executes the specified command.
*
* Return: Always 0.
*/
int main(void)
{
char *line = NULL;
ssize_t read_status;
size_t bf = 0;
char **argv = NULL;

while (1)
{
prompt();
read_status = getline(&line, &bf, stdin);
if (read_status == -1)
{
if (errno == 0)
{
custom_putchar('\n');
exit(EXIT_SUCCESS);
}
else
{
handle_error("getline");
}
}
else if (read_status == -2)
{
handle_other_errors();
continue;  /* Skip executing the command and go back to the prompt */
}
else
{
line[read_status - 1] = '\0'; /* Remove the newline character */
argv = parse_line(line);
if (argv[0] != NULL)
{
execute_command(argv[0], argv);
}
free(argv);
}
}

free(line);
return (0);
}

