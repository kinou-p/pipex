/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:45:03 by apommier          #+#    #+#             */
/*   Updated: 2022/01/20 20:26:59 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **get_path(char **envp)
{
	int		i;
	int		j;
	char	**line;
	char	*swap;

	i = 0;
	j = 0;
	line = 0;
	swap = 0;
	while (envp[i++] && envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH", 4))
		{
			swap = ft_substr(envp[i], -1, 4);
			line = ft_split(swap, ':');
			free(swap);
			return (line);
		}
		free(line);
	}
	return (0);
}

char	*get_command(char *exec, char **envp)
{
	char	**path;
	char	*cmd;
	char 	*del;
	int		i;

	i = 0;
	cmd = exec;
	path = get_path(envp);
	while (access(cmd, F_OK) && path[i++])
	{
		del = cmd;
		cmd = ft_strjoin("/", cmd);
		free(del);
		del = cmd;
		cmd = ft_strjoin(path[i], cmd);
		free(del);
	}
	return (cmd);
}

void pipex(char *cmd1, char *cmd2, int fd1, int fd2, char **envp)
{
	int		*pipe;
	pid_t	parent;

	pipe = ft_calloc(sizeof(int), 2);
	if (pipe(pipe) == -1)
		return ;
	parent = fork();
	if (parent < 0)
	{
		free(pipe);
		return ;
	}
	if (!parent)
		child(cmd1, fd1, path);
	else
		parent(cmd2, fd2, path);
	else 
	free(pipe);
}

void	child(int fd1, char **envp, char **argv)
{
	int		i;
	char	*cmd1; 

	cmd1 = 0;
	i = 0;
	if (!dup2(fd1, STDIN_FILENO))
		return ;
	if (!dup2(pipe[1], STDIN_FILENO))
		return ;
	close(end[0]);
	close(fd1);
	cmd1 = get_command(argc[0], envp);
	if (cmd1)
		execve(cmd1, argv, envp)
	free(cmd1);
}

void	parent(int fd2, char **envp, char **argv)
{
	char	*cmd2;

	return ;
}

int main(int argc, char **argv, char **envp)
{
	int		fd1;
	int 	fd2;
	char	*path;

	if (check_error)
		return (0);
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!fd1 || !fd2)
		return (0);
	pipex(argv[1], argv[4], fd1, fd2);
	return (1);
}
