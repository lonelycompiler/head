/*
HEAD

NAME
     head -- display first lines of a file

SYNOPSIS
     head [-n count | -c bytes] [file ...]

DESCRIPTION
     This filter displays the first count lines or bytes of each of the speci-
     fied files, or of the standard input if no files are specified.  If count
     is omitted it defaults to 10.

     If more than a single file is specified, each file is preceded by a
     header consisting of the string ``==> XXX <=='' where ``XXX'' is the name
     of the file.

EXIT STATUS
     The head utility exits 0 on success, and >0 if an error occurs.
(END)
*/

#include "head.h"

/* takes whatever is given in stdin and prints it to stdout (the screen) */
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

/* Exits the program with failure */
void
exit_bc_failure(void)
{
    _exit(EXIT_FAILURE);
}

/* prints usage is incorrect and exits program*/
void
incorrect_usage(void)
{
    printf("usage: head [-n lines | -c bytes] file\n");
    exit_bc_failure();
}

/* main shell for head.c */
int
main(int argc, char *argv[])
{
    printf("entered main function\n");

    /* if no flags or textfile given */
    if (argc == 1)
    {
        stdin_to_stdout();
    }
    bool 
    /* if first argument's first char is '-', it's a flag */
    if (argv[1][0] == '-')
    {
        /* check if flag is valid, '-n' or '-c' */
        if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "-n") == 0 )
        {
            
        }
        else
        {
            /* invalid flag */
        }
    }
            // require arg if third argument not given (# of lines/bytes)
            if (argc < 3)
            {
                printf("head: option requires an argument -- %c\n", argv[1][1]);
                incorrect_usage();
            }

        }
        else
        {
            if (strlen(argv[1]) >= 2)
            {
                // otherwise its incorrect flag, give error
                printf("head: illegal option -- %c\n", argv[1][1]);
            }
            else
            {
                printf("head: -: No such file or directory");
            }
        }
    }

    // make sure that there's another 2 arguments on top of that, otherwise require argument
    // otherwise first argument is file, error out if flag doesn't work

    // 

    // if both flags given with no file, or file and one flag given
    /*if (argc == 3)
    {
        //if only flag and file given, in that order
        // illegal [line/byte] count
        if (strlen(argv[1]) == 2 )
        {
            // -n flag + some_other_argument
            if (strcmp(argv[1], NEWLINES_FLAG) == 0)
            {
                printf("head: illegal line count -- %s\n", argv[2]);
            }
            // -c flag + some_other_argument
            else if (strcmp(argv[1], COUNTBYTES_FLAG) == 0)
            {
                printf("head: illegal byte count -- %s\n", argv[2]);
            }
            else
            {
                // if its a flag, say its unknown, otherwise
                // those two flags are probably 
                if(argv[])
                else
                {
                    printf("head: %s: No such file or directory\n");
                    incorrect_usage();
                }
            }
        }
        incorrect_usage();
    }*/

    if (argc == 2)
    {    
        // open file as read only
        int fd;
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
            exit_bc_failure();

        // read file from file descriptor
        char buffer[MAX_BUFFER_SIZE];
        if (read(fd, buffer, MAX_BUFFER_SIZE-1) == -1)
            exit_bc_failure();

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
                if (buffer[i+1] == '\n')
                {
                    buffer[i+1] = 0;
                }
                if (currentLine == 11) break;
            }
        }
        if (buffer[i] != '\n') printf("\n");
    }
    return 0;
}