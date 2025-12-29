/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saalomar <saalomar@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 11:06:37 by saalomar          #+#    #+#             */
/*   Updated: 2025/12/29 12:44:50 by saalomar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*copy_line_and_update_stash(char **stash, int len)
{
	char	*line;
	char	*new_stash;
	int		i;

	i = 0;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	while (i < len)
	{
		line[i] = (*stash)[i];
		i++;
	}
	line[len] = '\0';
	new_stash = ft_strjoin(NULL, (*stash) + len);
	free(*stash);
	*stash = new_stash;
	return (line);
}

static char	*extract_line(char **stash)
{
	int		i;

	i = 0;
	if (!*stash || **stash == '\0')
		return (NULL);
	while ((*stash)[i] && (*stash)[i] != '\n')
		i++;
	if ((*stash)[i] == '\n')
		i++;
	return (copy_line_and_update_stash(stash, i));
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buffer;
	int			bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes = 1;
	while (!has_newline(stash) && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buffer), free(stash), stash = NULL, NULL);
		buffer[bytes] = '\0';
		if (bytes > 0)
			stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	return (extract_line(&stash));
}
