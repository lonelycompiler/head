/*
This file prints to screen the top 10 lines by default of a file
If a valid flag is given, it'll print x amount of lines/bytes of the file
-n flag is the number of lines
-c flag is number of bytes
*/

#include "head.h"

/* takes whatever is given in stdin and prints it to stdout (the screen)
   Will go for linecount number of times.*/
void 
stdin_to_stdout_with_count(int linecount)
{
    char buffer[MAX_BUFFER_SIZE];
    for (int counter = 0; counter < linecount; counter++)
    {
        scanf("%s",buffer);
        printf("%s\n",buffer);
    }
    exit_success();
}

/* takes whatever is given in stdin and prints it to stdout (the screen).
   While loop means only SIGKILL can end it */
void 
stdin_to_stdout(void)
{
    char buffer[MAX_BUFFER_SIZE];
    while(true)
    {
        scanf("%s",buffer);
        printf("%s\n",buffer);
    }
}

/* prints usage is incorrect and exits program*/
void
incorrect_usage(void)
{
    exit_bc_failure("usage: head [-n lines | -c bytes] file");
}

/* main shell for head.c */
int
main(int argc, char *argv[])
{
    printf("entered main function\n");
    /* if countlines=0, countbytes is the argument */
    int countlines = 10;
    bool flags = false;

    /* if no flags or textfile given */
    if (argc == 1)
    {
        stdin_to_stdout();
    }
    
    /* is the first argument a flag?? */
    if (argv[1][0] == '-')
    {
        flags = true;
        /* check if flag is valid, '-n' or '-c' */
        if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "-n") == 0 )
        {
            if (strcmp(argv[1], "-c") == 0)
            {
                countlines = false;
            }
            else
            {
                /* count lines flag works */
                countlines = atoi(argv[2]);

                /* Error handling, if next argument isn't an integer */
                if (countlines <= 0)
                {
                    char err_msg[MAX_BUFFER_SIZE];
                    strcpy(err_msg, "head: illegal line count -- ");
                    strcat(err_msg, argv[2]);
                    exit_bc_failure(err_msg);
                }

                /* if there's no file provided */
                if (argc == 3)
                {
                    stdin_to_stdout_with_count(countlines);
                }
            }
        }
        else
        {
            /* invalid flag */
            char err_msg[MAX_BUFFER_SIZE];
            strcpy(err_msg, "head: illegal option -- ");
            strcat(err_msg, argv[1]);
            exit_bc_failure(err_msg);
        }
    }

    /* At this point, there either is flags + a file, or just a file */

    char filename[100];

    /* If there are flags, -n or -c */
    if (flags == true)
    {
        strcpy(filename, argv[3]);
    }
    else
    {
        strcpy(filename, argv[1]);
    }
    // open file as read only
    int fd;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        exit_bc_failure("file could not be opened!");

    // read file from file descriptor
    char buffer[MAX_BUFFER_SIZE];
    if (read(fd, buffer, MAX_BUFFER_SIZE-1) == -1)
        exit_bc_failure("file could not be read!");

    int currentLine = 1;
    int i;
    // start reading file
    for (i = 0; buffer[i] != '\0'; i++)
    {
        printf("%c", buffer[i]);
        
        // if new line, 
        if (buffer[i] == '\n')
        {
            currentLine++;
            
            // edgecase with greater/equal than 2 newlines
            if (buffer[i+1] != '\0')
            {
                if (buffer[i+1] == '\n') { buffer[i+1] = 0; }
                if (currentLine == 11) { break;}
            }
        }
    }
    if (buffer[i] != '\n') printf("\n");
    return 0;
}