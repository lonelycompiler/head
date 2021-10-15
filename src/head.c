/*
This file prints to screen the top 10 lines by default of a file
If a valid flag is given, it'll print x amount of lines/bytes of the file
-n flag is the number of lines
-c flag is number of bytes
*/

#include "head.h"

Transaction head_status;
/*
    Takes user inputand prints it to the screen
    stdin -> stdout, called when no file given when calling program
    Works with no flag, linecount or bytecount flag to read
*/

void 
stdin_to_stdout(void)
{
    /* store what to put to stdout here */
    char temp_buffer[MAX_BUFFER_SIZE];

    /* if no flag, infinite while -- only SIGKILL can end it */
    if (head_status.flag == no_flags)
    {
        while(true)
        {
            fgets(temp_buffer, sizeof temp_buffer, stdin);
            printf("%s", temp_buffer);
        }
    }
    else if(head_status.flag == count_lines_flag)
    {
        /* gets input and prints output only up to the set # of lines */
        for (int line = 0; line < head_status.countlines; line++)
        {
            fgets(temp_buffer, sizeof temp_buffer, stdin);
            printf("%s", temp_buffer);
        }
        strcpy(temp_buffer, "");
    }
    else
    {
        int bytes_to_read = head_status.countbytes;
        
        /*
            if # of bytes is odd 
            bytes to read will read half of bytes to count
            and those bytes are then printed
        */

        /* this is input initialized */
        char buf[MAX_BUFFER_SIZE];

        /* initialize strings */
        strcpy(buf, "");
        strcpy(temp_buffer, "");

        /*
            input is first gotten, 
            then it is counted line by line,
            upto bytes_to_read
            printed after while
        */
        while (bytes_to_read > 0 && fgets(buf, sizeof buf, stdin) != NULL)
        {
            /* loop through string */
            for (int i = 0; buf[i] != '\0'; i++)
            {
                bytes_to_read--;

                /* if new line as last character, remove it, because
                   at line 80 we do newline anyhow :/ */
                if (bytes_to_read == 0 && buf[i] == '\n') buf[i] = '\0';
                
                strncat(temp_buffer, &buf[i], 1);
                if (bytes_to_read == 0) break;
            }
        }
        printf("%s\n",temp_buffer);
    }
    exit_success();
}

/* prints usage is incorrect and exits program*/
void
incorrect_usage(void)
{
    exit_failure("usage: head [-n lines | -c bytes] file");
}

/* main shell for head.c */
int
main(int argc, char *argv[])
{
    head_status.flag = no_flags;
    head_status.countlines = 10;
    head_status.countbytes = MAX_BUFFER_SIZE;

    printf("entered main function\n");
    /* if countlines=0, countbytes is the argument */

    /* if no flags or textfile given */
    if (argc == 1)
    {
        stdin_to_stdout();
    }
    
    /* is the first argument a flag?? */
    if (argv[1][0] == '-')
    {
        /* check if flag is valid, '-n' or '-c' */
        if (strcmp(argv[1], "-c") == 0 || strcmp(argv[1], "-n") == 0 )
        {
            if (strcmp(argv[1], "-c") == 0)
            {
                head_status.flag = count_bytes_flag;
                /* assuming its an int, reads arg 2's bytes from file */
                head_status.countbytes = atoi(argv[2]);

                /* Error handling, if next argument isn't an integer */
                if (head_status.countbytes <= 0)
                {
                    char err_msg[MAX_BUFFER_SIZE];
                    strcpy(err_msg, "head: byte line count -- ");
                    strcat(err_msg, argv[2]);
                    exit_failure(err_msg);
                }

                /* if there's no file provided */
                if (argc == 3)
                {
                    stdin_to_stdout();
                }
            }
            else
            {
                head_status.flag = count_lines_flag;
                /* count lines flag works */
                head_status.countlines = atoi(argv[2]);

                /* Error handling, if next argument isn't an integer */
                if (head_status.countlines <= 0)
                {
                    char err_msg[MAX_BUFFER_SIZE];
                    strcpy(err_msg, "head: illegal line count -- ");
                    strcat(err_msg, argv[2]);
                    exit_failure(err_msg);
                }

                /* if there's no file provided */
                if (argc == 3)
                {
                    stdin_to_stdout();
                }
            }
        }
        else
        {
            /* invalid flag */
            char err_msg[MAX_BUFFER_SIZE];
            strcpy(err_msg, "head: illegal option -- ");
            strcat(err_msg, argv[1]);
            exit_failure(err_msg);
        }
    }

    /* If there are valid flags, test file is third arg */
    if (head_status.flag == count_lines_flag)
    {
        /* open file as read only */
        int fd;
        fd = open(argv[1], O_RDONLY);
        if (fd == -1)
            exit_failure("file could not be opened!");
        
        /* if counting lines
            read file from file descriptor */
        char buffer[MAX_BUFFER_SIZE];
        if (read(fd, buffer, MAX_BUFFER_SIZE) == -1)
            exit_failure("file could not be read!");
        int currentLine = 1;
        int i;

        /* start reading file */
        for (i = 0; buffer[i] != '\0'; i++)
        {
            printf("%c", buffer[i]);
            
            /* if new line, */
            if (buffer[i] == '\n')
            {
                currentLine++;
                
                /* edgecase with greater/equal than 2 newlines */
                if (buffer[i+1] != '\0')
                {
                    if (buffer[i+1] == '\n') { buffer[i+1] = 0; }
                    if (currentLine == 11) { break;}
                }
            }
        }
        if (buffer[i] != '\n') printf("\n");
    }
    else if (head_status.flag == count_bytes_flag)
    {
        /* open file as read only */
        int fd;
        fd = open(argv[3], O_RDONLY);
        if (fd == -1)
            exit_failure("file could not be opened!");
        
        /* if counting lines
            read file from file descriptor */
        char buffer[MAX_BUFFER_SIZE];
        if (read(fd, buffer, head_status.countbytes) == -1)
            exit_failure("file could not be read!");
        
       printf("%s\n", buffer);
    }
    else
    {
        exit_failure("");
    }

    return 0;
}
