/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:45:13 by apommier          #+#    #+#             */
/*   Updated: 2022/01/21 08:07:31 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <errno.h>
# include "./libft/libft.h"

char	**get_path(char **envp);
char	*get_command(char **exec, char **envp);
void	pipex(char **envp, char **argv);
void	child_process(int fd1, char **envp, char **argv, int *pipe_tab);
void	parent_process(int fd2, char **envp, char **argv, int *pipe_tab);

void	error(char *error);
void	exit_command(char **path, char **exec, char *swap, int i);
void	free_double(char **tab);

#endif