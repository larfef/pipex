# ifndef PIPEX_H
#define PIPEX_H
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include "libft.h"
#define CMD1 2
#define CMD2 3
#define FILE1 1
#define FILE2 4
#define NAME 0
#define STDIN 0
#define STDOUT 1
#define READ 0
#define WRITE 1
#define PERM 0777

typedef struct t_struct
{
	char	*path;
	char	**arg;
	char	**av;
	int		success;
	int		fd_in;
	int		fd_out;
	int		status;
	int		pipe[2];
	pid_t	pid;
}	t_data;

# endif