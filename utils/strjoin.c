/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncrivell <ncrivell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:36:10 by ncrivell          #+#    #+#             */
/*   Updated: 2025/03/17 16:01:43 by ncrivell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2, char const *s3)
{
	int		sizedest;
	char	*dest;
	int		i;
	int		j;

	if (!s1 || !s2 || !s3)
		return (NULL);
	sizedest = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3);
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
		dest[i++] = s2[j++];
	j = 0;
	while (s3[j])
		dest[i++] = s3[j++];
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	len;

	len = ft_strlen(s);
	i = 0;
	if ((char)c == '\0')
		return ((char *)&s[len]);
	while (i < len)
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;
	int		slen;

	i = 0;
	slen = ft_strlen(s);
	dest = malloc((slen + 1) * sizeof(char));
	if (dest == NULL)
		return (0);
	while (i < slen)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
