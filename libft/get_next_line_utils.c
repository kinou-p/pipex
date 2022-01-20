/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 06:05:54 by apommier          #+#    #+#             */
/*   Updated: 2022/01/17 21:42:00 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Utils/push_swap.h"

char	*ft_strjoin(char *save, char *s2)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!save && !s2)
		return (0);
	dest = malloc(ft_strlen(save) + ft_strlen(s2) + 1);
	while (save && save[i])
	{
		dest[j] = save[i];
		j++;
		i++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		dest[j] = s2[i];
		j++;
		i++;
	}
	dest[j] = 0;
	return (dest);
}
