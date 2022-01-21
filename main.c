/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:45:03 by apommier          #+#    #+#             */
/*   Updated: 2022/01/21 08:02:42 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **env)
{
	int		i;
	int		j;
	char	**line;
	char	*swap;

	i = 0;
	j = 0;
	line = 0;
	swap = 0;
	while (env[i++] && env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			swap = ft_substr(env[i], 5, ft_strlen(env[i]));
			if (!swap)
				exit(1);
			line = ft_split(swap, ':');
			if (!line)
				exit(1);
			free(swap);
			return (line);
		}
		free(line);
	}
	return (0);
}

char	*get_command(char **exec, char **env)
{
	char	**path;
	char	*cmd;
	char	*swap;
	int		i;

	i = 0;
	cmd = 0;
	swap = 0;
	path = get_path(env);
	if (exec[0][0] != '/')
		swap = ft_strjoin(path[i], "/");
	else
		swap = ft_strdup(path[i]);
	while (access(swap, F_OK) && path[i++])
	{
		free(swap);
		swap = ft_strjoin(path[i], "/");
		cmd = swap;
		swap = ft_strjoin(swap, exec[0]);
		free(cmd);
	}
	exit_command(path, exec, swap, i);
	return (swap);
}

void	child_process(int fd1, char **env, char **argv, int *end)
{
	char	**exec;
	char	*cmd;
	int		i;

	i = 0;
	if (dup2(end[1], 1) == -1)
		error("dup2 fail");
	if (dup2(fd1, 0) == -1)
		error("dup2 fail");
	close(end[0]);
	close(fd1);
	exec = ft_split(argv[2], ' ');
	cmd = get_command(exec, env);
	if (execve(cmd, exec, env) == -1)
	{
		free_double(exec);
		free(cmd);
		error("Execve went wrong");
	}
	free_double(exec);
	free(cmd);
}

void	parent_process(int fd2, char **env, char **argv, int *end)
{
	char	**exec;
	char	*cmd2;
	int		status;

	waitpid(-1, &status, 0);
	if (dup2(end[0], 0) == -1)
		error("dup2 fail");
	if (dup2(fd2, 1) == -1)
		error("dup2 fail");
	close(end[1]);
	close(fd2);
	exec = ft_split(argv[3], ' ');
	cmd2 = get_command(exec, env);
	if (execve(cmd2, exec, env) == -1)
	{	
		free_double(exec);
		free(cmd2);
		error("Execve went wrong");
	}
	free_double(exec);
	free(cmd2);
}

int	main(int argc, char **argv, char **env)
{
	int		end[2];
	pid_t	parent;
	int		fd1;
	int		fd2;

	if (argc != 5)
		error("Bad number of argument");
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd2 == -1 || fd1 == -1)
	{
		error("Bad file descriptor");
	}
	pipe(end);
	parent = fork();
	if (parent < 0)
		error("Fork Error");
	if (!parent)
		child_process(fd1, env, argv, end);
	else
		parent_process(fd2, env, argv, end);
	exit(1);
}
