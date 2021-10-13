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
        for (int line = 0; line < head_status.countlines; line++)
        {
            fgets(temp_buffer, sizeof temp_buffer, stdin);
            printf("%s", temp_buffer);
        }
    }
    else
    {
        int bytes_to_read = head_status.countbytes;
        
        /* if # of bytes is odd */
        if (bytes_to_read %2 != 0)
            bytes_to_read = (bytes_to_read+1) / 2;
        else
            bytes_to_read = (bytes_to_read) / 2;

        char buf[bytes_to_read+1]; // +1 is \0
        strcpy(buf, "");
        strcpy(temp_buffer, "");
        printf("bytes_to_read=%d\n", bytes_to_read);

        while (fgets(buf, sizeof buf, stdin) != NULL && bytes_to_read > 0)
        {
            if (strlen(buf) )
            printf("strlen(buf)=%d\n", (int) strlen(buf));

            for (int i = 0; i < strlen(buf)-1; i++)
            {
                bytes_to_read--;
                char temp = i;
                buf[i+1] = '\0';
                printf("buf=%s,temp=%s\n", buf, temp_buffer);
                strcat(temp_buffer, buf);
                buf[i+1] = temp;
            }
            strcat(temp_buffer, "\n");
        }
        printf("%s", temp_buffer);
    }
    exit_success();
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
    head_status.flag = no_flags;
    head_status.countlines = 10;
    head_status.countbytes = MAX_BUFFER_SIZE;

    printf("entered main function\n");
    /* if countlines=0, countbytes is the argument */
    bool flags = false;

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
                    exit_bc_failure(err_msg);
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
                    exit_bc_failure(err_msg);
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
            exit_bc_failure(err_msg);
        }
    }

    /* At this point, there either is flags + a file, or just a file */

    char filename[100];

    /* If there are valid flags, test file is third arg */
    if (flags == true)
    {
        strcpy(filename, argv[3]);
    }
    else
    {
        /* Test file is first arg */
        strcpy(filename, argv[1]);
    }

    // open file as read only
    int fd;
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        exit_bc_failure("file could not be opened!");
        /* if counting lines */
        // read file from file descriptor
        char buffer[MAX_BUFFER_SIZE];
        if (read(fd, buffer, head_status.countbytes-1) == -1)
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