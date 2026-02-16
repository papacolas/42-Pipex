/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:43:23 by ncrivell          #+#    #+#             */
/*   Updated: 2025/03/17 16:03:03 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "pipex.h"
#include "pipexbonus.h"
#include <stdlib.h>

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t		sizedest;
	char		*dest;
	int			i;
	int			j;

	sizedest = ft_strlen(s1) + ft_strlen(s2);
	dest = malloc ((sizedest + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		dest[i] = s2[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}
