#include "pipex.h"

void	free_table(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i++]);
		i++;
	}
	free(ptr);
}

int	child_process(t_data *data)
{
	if (close(data->pipefd[READ]) == -1
		|| execve(data->path, data->arg, NULL) == -1)
		return (-1);
	return (1);
}

int	execute_cmd(t_data *data)
{
	static int	i;

	if (i == 1)
		data->fd_out = open(data->av[FILE2], O_WRONLY | O_CREAT, PERM);
	if (data->fd_out == -1 
		|| dup2(data->fd_out, STDOUT) == -1)
		return (-1);
	data->pid = fork();
	if (data->pid == -1)
		return (-1);
	if (data->pid != 0
		&& (wait(&data->status) == -1
			|| !WIFEXITED(data->status)))
		return (-1);
	else if (data->pid == 0
		&& (child_process(data) == -1))
		return (-1);
	if (data->pid != 0 && i++ == 1)
	{
		data->success = TRUE;
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
		exit(EXIT_FAILURE);
	data->path = ft_strjoin(data->path, data->arg[NAME]);
	if (data->path == NULL)
		return (-1);
	if (cmd == CMD1)
		data->fd_in = open(data->av[FILE1], O_RDONLY);
	if (cmd == CMD1 && data->fd_in == -1)
	{
		if (close(data->fd_in) == -1)
			return (-1);
	}
	return (1);
}

int	main(int ac, char **av)

{
	t_data	data;

	if (ac != 5)
		return (-1);
	if (!av[1] || !av[2] || !av[3] || !av[4]
		|| *av[1] == 0 || *av[2] == 0 || *av[3] == 0 || *av[4] == 0)
		return (-1);
	data.success = 0;
	data.av = av;
	data.path = "/usr/bin/";
	data.status = 0;
	data.fd_out = 0;
	if (set_execve(&data, CMD1) == -1
		|| pipe(data.pipefd) == -1
		|| close(STDIN) == -1
		|| dup2(data.fd_in, STDIN) == -1
		|| close(STDOUT) == -1
		|| dup2(data.pipefd[WRITE], STDOUT) == -1
		|| close(data.pipefd[WRITE]) == -1
		|| execute_cmd(&data) == -1
		|| dup2(data.pipefd[READ], STDIN) == -1
		|| set_execve(&data, CMD2) == -1
		|| execute_cmd(&data) == -1)
	{
		free_table(data.arg);
		free(data.path);
		if (!data.success)
			return (-1);
	}
	return (1);
}
