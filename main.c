/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:45:03 by apommier          #+#    #+#             */
/*   Updated: 2022/01/21 01:16:22 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

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
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			swap = ft_substr(envp[i], 5, ft_strlen(envp[i]));
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
	char 	*swap;
	int		i;

	i = 0;
	swap = 0;
	cmd = ft_strjoin("/", exec);
	path = get_path(envp);
	swap = ft_strjoin(path[i], cmd);
	while (access(swap, F_OK) == -1 && path[i++])
	{
		if (swap)
			free(swap);
		swap = ft_strjoin(path[i], cmd);
	}
	printf("cmd = %s path = %s\n", cmd, swap);
	free(cmd);
	return (swap);
}

void pipex(int fd1, int fd2, char **envp, char **argv)
{
	int		pipe_tab[2];
	pid_t	parent;

	parent = fork();
	if (parent < 0)
	{
		printf("here\n");
		perror("Error");
		return ;
	}
	if (!parent)
		child_process(fd1, envp, argv, pipe_tab);
	else
		parent_process(fd2, envp, argv, pipe_tab);
	printf("pipex end\n");
}

void	child_process(int fd1, char **envp, char **argv, int *pipe_tab)
{
	int		i;
	char	*cmd1; 

	cmd1 = 0;
	i = 0;
	if (dup2(fd1, 0) == -1)
	{
		perror("Error");
		return ;
	}
	if (dup2(pipe_tab[1], 1) == -1)
	{
		perror("Error");
		return ;
	}
	close(pipe_tab[0]);
	close(fd1);
	cmd1 = get_command(argv[2], envp);
	if (cmd1)
	{
		execve(cmd1, argv, envp);
		free(cmd1);
	}
}

void	parent_process(int fd2, char **envp, char **argv, int *pipe_tab)
{
	int		i;
	int		status;
	char	*cmd2; 

	waitpid(-1, &status, 0);
	cmd2 = 0;
	i = 0;
	if (!dup2(fd2, 1))
		return ;
	if (!dup2(pipe_tab[0], 0))
		return ;
	close(pipe_tab[1]);
	close(fd2);
	cmd2 = get_command(argv[3], envp);
	if (cmd2)
	{
		execve(cmd2, argv, envp);
		free(cmd2);
	}
}
int main(int argc, char **argv, char **envp)
{
	int		fd1;
	int 	fd2;
	char	*path;

	//if (check_error)
	//	return (0);
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (!fd1 || !fd2)
		return (0);
	pipex(fd1, fd2 , envp, argv);
	printf("--end--\n");
	return (1);
}
