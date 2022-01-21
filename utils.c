/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 08:03:23 by apommier          #+#    #+#             */
/*   Updated: 2022/01/21 08:04:01 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(char *error)
{
	perror(error);
	exit(1);
}

void	exit_command(char **path, char **exec, char *swap, int i)
{
	if (!path[i])
	{
		i = 0;
		while (path[i])
			free(path[i++]);
		free(path);
		i = 0;
		while (exec[i])
			free(exec[i++]);
		free(exec);
		free(swap);
		error("command not found");
	}
	i = 0;
	while (path[i++])
		free(path[i]);
	free(path);
}

void	free_double(char **tab)
{
	int	i;

	i = 0;
	while (tab[i++])
		free(tab[i]);
	free(tab);
}
