/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayou <tayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 05:42:51 by tayou             #+#    #+#             */
/*   Updated: 2023/01/28 16:31:33 by tayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_buf_readsize(char *buf, int *read_size, int fd)
{
	buf = (char *) malloc(BUFFER_SIZE + 1);
	if (buf == 0)
		return (0);
	*read_size = read(fd, buf, BUFFER_SIZE);
	if (*read_size <= 0)
	{
		free(buf);
		buf = NULL;
		return (0);
	}
	buf[*read_size] = '\0';
	return (buf);
}

static char	*get_backup(char *buf, char *backup, int read_size, int fd)
{
	while (read_size > 0)
	{
		if (backup == NULL)
			backup = ft_strdup(buf);
		else
			backup = ft_strjoin(backup, buf);
		if (backup == NULL)
			return (NULL);
		if (ft_strchr(backup, '\n') != NULL)
			break ;
		read_size = read(fd, buf, BUFFER_SIZE);
		if (read_size == -1)
			return (NULL);
		buf[read_size] = '\0';
	}
	return (backup);
}

static char	*get_line(char *line, char *backup)
{
	int		newline_point;
	int		size;
	int		i;

	if (ft_strchr(backup, '\n') != NULL)
	{
		i = 0;
		while (backup[i] != '\n')
			i++;
		newline_point = i;
		size = newline_point + 1;
		line = ft_substr(backup, 0, size);
	}
	else
		line = ft_strdup(backup);
	return (line);
}

static char	*renewal_backup(char *backup)
{
	char	*temp;
	int		newline_point;
	int		start;
	int		size;
	int		i;

	if (ft_strchr(backup, '\n') != NULL)
	{
		i = 0;
		while (backup[i] != '\n')
			i++;
		newline_point = i;
		start = newline_point + 1;
		size = ft_strlen(&backup[start]);
		temp = backup;
		backup = ft_substr(temp, start, size);
	}
	else
		backup = NULL;
	return (backup);
}

char	*get_next_line(int fd)
{
	static char	*backup;
	char		*buf;
	char		*line;
	int			read_size;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = NULL;
	buf = NULL;
	buf = get_buf_readsize(buf, &read_size, fd);
	if (buf == NULL)
		return (NULL);
	backup = get_backup(buf, backup, read_size, fd);
	free(buf);
	buf = NULL;
	if (backup == NULL)
		return (NULL);
	line = get_line(line, backup);
	backup = renewal_backup(backup);
	return (line);
}
