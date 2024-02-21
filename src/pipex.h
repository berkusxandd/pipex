#ifndef PIPEX_H
#define PIPEX_H
#include "../Libft/libft.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>     
#include <sys/wait.h>

typedef struct s_pipex
{
	char**  commands[2];
	char *command_paths[2];
    char*   path;
    char *outfile;
    char *infile;
    int end[2];
}					t_pipex;

#endif