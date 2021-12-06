#ifndef MY_H_
#define MY_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



#define MAXNUMWORDS 2048
#define MAXWORDLENGTH 64


typedef struct s_file {
    char *file;
    int fd;
    char **file_content;
} t_file;

int size_eol(char *);
void show_state(int);
int main(int, char **);
int read_file();

#endif /* !MY_H_ */