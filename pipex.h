/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 12:45:13 by apommier          #+#    #+#             */
/*   Updated: 2022/01/21 03:00:34 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "./libft/libft.h"

char	**get_path(char **envp);
char	*get_command(char *exec, char **envp);
void	pipex(char **envp, char **argv);
void	child_process(char **envp, char **argv, int *pipe_tab);
void	parent_process(char **envp, char **argv, int *pipe_tab);
