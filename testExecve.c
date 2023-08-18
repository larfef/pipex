#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	char	*arg[] = {"ab", NULL};

	int fd_in = open("infile", O_RDONLY);
	printf("%i\n", fd_in);

	//printf("%i\n", execve("/usr/bin/ab", arg, NULL));
}


// infile
// libft
// Makefile
// outfile
// pipex
// pipex.c
// pipex.h
// pipex.o
// testExecve.c

// Makefile
// infile
// libft
// outfile
// pipex
// pipex.c
// pipex.h
// pipex.o
// testExecve.c