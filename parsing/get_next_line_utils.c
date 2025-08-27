/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 09:27:25 by anel-men          #+#    #+#             */
/*   Updated: 2025/01/05 09:27:28 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char const *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		j;
	int		s_len;
	char	*dup;

	i = 0;
	j = 0;
	s_len = ft_strlen(s);
	dup = (char *)malloc(s_len + 1);
	if (dup == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		dup[j] = s[i];
		j++;
		i++;
	}
	return (dup[j] = '\0', dup);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;
	char	*s3;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3 = (char *)malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!s3)
		return (NULL);
	i = -1;
	while (++i < s1_len)
		s3[i] = s1[i];
	j = -1;
	while (++j < s2_len)
		s3[i + j] = s2[j];
	return (s3[i + j] = '\0', s3);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*substr;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (s[start + i] != '\0' && i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	return (substr[i] = '\0', substr);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	m;

	i = 0;
	m = c;
	if (m == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[i++] != '\0')
		if (s[i] == m)
			return ((char *)&s[i]);
	return (NULL);
}
