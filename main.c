/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:45:03 by apommier          #+#    #+#             */
/*   Updated: 2022/01/20 19:07:24 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	int		fd1;
	int 	fd2;
	char	*path;

	if (check_error)
		return (0);
	fd1 = open(argv[1], O_RDONLY);
	fd2 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC);
	if (!fd1 || !fd2)
		return (0);
	path = get_path(envp);
	pipex(argv[1], argv[4], fd1, fd2);
	return (1);
}

char *get_path(char **envp)
{
	int	i;
	int	j;
	char **line;
	char **swap;

	i = 0;
	j = 0;
	line = 0;
	swap = 0;
	while (envp[i++] && envp[i])
	{
		line = ft_split(envp[i], ':');
		if (!ft_strncmp(line[0], "PATH", 4))
			return (line);
		free(line);
	}
	return (0);
}

void pipex(char *cmd1, char *cmd2, int fd1, int fd2, char **)
{
	int		*pipe;
	pid_t	parent;

	pipe = ft_calloc(sizeof(int), 2);
	pipe(pipe);
	parent = fork();
	if (parent < 0)
	{
		free(pipe);
		return (0);
	}
	if (!parent)
		child(cmd1, fd1, path);
	else
		parent(cmd2, fd2, path);
	else 
	free(pipe);
}

child(char *cmd1, int fd1, char **path)
{

}

parent(char *cmd2, int fd2, char **path)
{

}