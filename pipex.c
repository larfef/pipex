#include "pipex.h"

// static int	set_quote(t_data *data)
// {
// 	char	*temp;
// 	int		current;

// 	current = 0;
// 	while (data->arg[current]) 
// 	{
// 		if (ft_strlen(data->arg[current]) == 2
// 			&& ft_strncmp(data->arg[current], "''", 2) == 0)
// 		{
// 			temp = ft_calloc(5, sizeof(char));
// 			if (!temp)
// 				return(-1);
// 			free(data->arg[current]);
// 			data->arg[current] = temp;
// 			ft_strlcpy(data->arg[current], "\\'\\'", 5);
// 		}
// 		current++;
// 	}
// 	return (1);
// }

void	free_table(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr[i]);
	free(ptr);
}

void	child_process(t_data *data)
{
	//static int	i;

	// if (i == 1)
	// 	data->fd_out = open(data->av[FILE2], O_WRONLY | O_CREAT, PERM);
	// if (i++ == 1)
	// 	if (data->fd_out == -1 
	// 		|| dup2(data->fd_out, STDOUT) == -1)
	// 			return;
	if (close(data->pipe[READ]) == -1
		|| execve(data->path, data->arg, NULL) == -1)
	{
		perror("command not found:");
		exit(EXIT_FAILURE);
	}
}

int	execute_cmd(t_data *data)
{
	static int	i;

	if (i == 1)
		data->fd_out = open(data->av[FILE2], O_WRONLY | O_CREAT | O_TRUNC, PERM);
	if (i == 1)
		if (data->fd_out == -1 
			|| dup2(data->fd_out, STDOUT) == -1)
				return (-1);
	data->pid = fork();
	if (data->pid == -1)
		return (-1);

	if (data->pid != 0
		&& wait(&data->status) == -1)
		return (-1);
	else if (data->pid == 0)
		child_process(data);	
	if (data->pid != 0 && i++ == 1)
	{
		data->success = 1;
		return (-1);
	}
	return (1);
}

int	set_execve(t_data *data, int cmd)
{
	if (cmd == CMD2)
	{
		free_table(data->arg);
		free(data->path);
		data->path = "/usr/bin/";
	}
	data->arg = ft_split(data->av[cmd], ' ');
	if (data->arg == NULL)
		return (-1);
	// if (set_quote(data) == -1)
	// 	return (-1);
	data->path = ft_strjoin(data->path, data->arg[NAME]);
	if (data->path == NULL)
		return (-1);
	if (cmd == CMD1)
		data->fd_in = open(data->av[FILE1], O_RDONLY);
	if (cmd == CMD1 && data->fd_in == -1)
			return (-1);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 5)
		exit(EXIT_FAILURE);
	if (!av[1] || !av[2] || !av[3] || !av[4]
		|| *av[1] == 0 || *av[2] == 0 || *av[3] == 0 || *av[4] == 0)
		return (-1);
	data.success = 0;
	data.av = av;
	data.path = "/usr/bin/";
	data.status = 0;
	data.pipe[0] = -1;
	data.pipe[1] = -1;
	data.fd_out = 0;
	if (set_execve(&data, CMD1) == -1
		|| close(STDIN) == -1
		|| dup2(data.fd_in, STDIN) == -1
		|| pipe(data.pipe) == -1
		|| close(STDOUT) == -1
		|| dup2(data.pipe[WRITE], STDOUT) == -1
		|| close(data.pipe[WRITE]) == -1
		|| execute_cmd(&data) == -1
		|| dup2(data.pipe[READ], STDIN) == -1
		|| set_execve(&data, CMD2) == -1
		|| execute_cmd(&data) == -1)
	{
		free_table(data.arg);
		free(data.path);
		if (data.fd_in > 0)
			close(data.fd_in);
		close(data.pipe[READ]);
		close(data.fd_out);
		if (!data.success)
		{
			if (WIFSIGNALED(data.status))
				exit(WTERMSIG(data.status));
			exit(0);
		}
	}
	if (WIFEXITED(data.status))
		exit(EXIT_SUCCESS);
}
