/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anel-men <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 09:27:09 by anel-men          #+#    #+#             */
/*   Updated: 2025/01/05 09:27:12 by anel-men         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	here_your_line(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	return (i);
}

char	*check(char *buffer)
{
	if (!buffer)
	{
		buffer = ft_strdup("");
		if (!buffer)
			return (NULL);
	}
	return (buffer);
}

static char	*reading(int fd, char *buffer)
{
	char	*tmp;
	char	*old;
	ssize_t	count;

	buffer = check(buffer);
	tmp = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!tmp)
		return (free(buffer), buffer = NULL, NULL);
	while (1)
	{
		count = read(fd, tmp, BUFFER_SIZE);
		if (count <= 0)
			break ;
		tmp[count] = '\0';
		old = buffer;
		buffer = ft_strjoin(buffer, tmp);
		free(old);
		if (!buffer || ft_strchr(buffer, '\n') != NULL)
			break ;
	}
	free(tmp);
	if (count < 0 || !buffer || !*buffer)
		return (free(buffer), buffer = NULL, NULL);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*old;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = reading(fd, buffer);
	if (!buffer)
		return (NULL);
	old = buffer;
	line = ft_substr(buffer, 0, here_your_line(buffer) + 1);
	if (!line)
		return (free(buffer), buffer = NULL, NULL);
	buffer = ft_substr(buffer, here_your_line(buffer) + 1, (ft_strlen(buffer)
				- here_your_line(buffer)));
	if (!buffer)
		return (free(old), free(line), NULL);
	return (free(old), line);
}
