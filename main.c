/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:45:03 by apommier          #+#    #+#             */
/*   Updated: 2022/01/21 03:56:28 by apommier         ###   ########.fr       */
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
	cmd = 0;
	path = get_path(envp);
	swap = ft_strjoin(path[i], "/");
	while (access(swap, F_OK) && path[i++])
	{
		if (swap)
			free(swap);
		swap = ft_strjoin(path[i], "/");
		cmd = swap;
		swap = ft_strjoin(swap, exec);
		free(cmd);
	}
	if (!path[i])
		return (0);
	return (swap);
}

void	child_process(char **envp, char **argv, int *end)
{
	int		fd1;
	char	**exec;
	char 	*cmd1; 
	
	fd1 = open(argv[1], O_RDONLY);
	exec = ft_split(argv[2], ' ');
	cmd1 = get_command(exec[0], envp);
	if (dup2(end[1], 1) == -1)
	{
		perror("Error");
		exit(1);
	}
	if (dup2(fd1, 0) == -1)
	{
		perror("Error");
		exit(1);
	}
	close(end[0]);
	close(fd1);
	if (execve(cmd1, exec, envp) == -1)
		perror("Error");
	free(cmd1);
}


void	parent_process(char **env, char **argv, int *end)
{
	char	**exec;
	char 	*cmd2;
	int		status;
	int 	fd2;


	waitpid(-1, &status, 0);	
	exec = ft_split(argv[3], ' ');
	fd2 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0666);
	cmd2 = get_command(exec[0], env);	
	if (dup2(end[0], 0) == -1)
		exit(1);
	if (dup2(fd2, 1) == -1)
		exit(1);
	close(end[1]);
	close(fd2);
	if (execve(cmd2, exec, env) == -1)
		perror("Error");
}

int main(int argc, char **argv, char **envp)
{
	int		end[2];
	char *cmd1;
	char *cmd2;
	pid_t	parent;

	pipe(end);
	parent = fork();
	if (parent < 0)
	{
		printf("here\n");
		perror("Error");
		return (0);
	}
	if (!parent)
		child_process(envp, argv, end);
	else
		parent_process(envp, argv, end);
	return (0);
}
