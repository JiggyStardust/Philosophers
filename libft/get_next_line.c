/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sniemela <sniemela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:08:00 by sniemela          #+#    #+#             */
/*   Updated: 2024/08/06 10:02:54 by sniemela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*free_str(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

static char	*read_to_holder(int fd, char *reader, char *holder)
{
	int		read_bytes;
	char	*temp_holder;

	while (1)
	{
		read_bytes = read(fd, reader, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free_str(&holder));
		if (read_bytes == 0)
			break ;
		reader[read_bytes] = '\0';
		if (!holder)
			holder = ft_strdup("");
		if (!holder)
			return (NULL);
		temp_holder = holder;
		holder = ft_strjoin(temp_holder, reader);
		if (!holder)
			return (free_str(&temp_holder));
		free(temp_holder);
		temp_holder = NULL;
		if (ft_strchr(holder, '\n'))
			break ;
	}
	return (holder);
}

static char	*mine_the_line(char **line, char *holder)
{
	char	*temp;
	char	*new_holder;
	int		len;

	temp = ft_strchr(holder, '\n');
	if (!temp)
	{
		*line = ft_strdup(holder);
		return (free_str(&holder));
	}
	len = (temp - holder) + 1;
	*line = ft_substr(holder, 0, len);
	if (!*line)
		return (free_str(&holder));
	new_holder = ft_substr(holder, len, ft_strlen(holder) - len);
	free(holder);
	holder = new_holder;
	if (holder && *holder == '\0')
		return (free_str(&holder));
	return (holder);
}

char	*get_next_line(int fd)
{
	static char	*holders[MAX_FILES] = {0};
	char		*reader;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FILES)
		return (NULL);
	reader = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!reader)
		return (free_str(&holders[fd]));
	reader[0] = '\0';
	holders[fd] = read_to_holder(fd, reader, holders[fd]);
	if (!holders[fd])
		return (free_str(&reader));
	free(reader);
	reader = NULL;
	line = NULL;
	holders[fd] = mine_the_line(&line, holders[fd]);
	return (line);
}
