#ifndef HEAD_H
#define HEAD_H

#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NEWLINES_FLAG "-n"
#define COUNTBYTES_FLAG "-c"
#define MAX_BUFFER_SIZE 4096

/* exits program with success status (0) */
void
exit_success()
{
    _exit(0);
}

/* Exits the program with failure */
void
exit_bc_failure(char *str)
{
    printf("ERROR: %s\n", str);
    _exit(EXIT_FAILURE);
}

/* This shows what flags have been given */
typedef enum
{
    no_flags,
    count_lines_flag,
    count_bytes_flag
} FLAG;

/* Use the Flag Type, Number of Lines to spew, and bytes to read in
   to handle any functions */
typedef struct
{
    FLAG flag;
    int countlines;
    int countbytes;

} Transaction;


#endif
