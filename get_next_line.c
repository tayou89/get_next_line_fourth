/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayou <tayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 05:42:51 by tayou             #+#    #+#             */
/*   Updated: 2023/01/28 13:55:13 by tayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_buf_readsize(char *buf, int *read_size, int fd)
{
	buf = (char *) malloc(BUFFER_SIZE + 1);
	if (buf == 0)
		return (0);
	*read_size = read(fd, buf, BUFFER_SIZE);
	if (*read_size == -1)
		return (0);
	buf[*read_size] = '\0';
	return (buf);
}

int	ft_strlen(char *string)
{
	int	i;
	int	size;

	if (string == 0)
		return (0);
	i = 0;
	while (string[i] != '\0')
		i++;
	size = i;
	return (size);
}

char	*ft_strdup(char *string)
{
	char	*copy_string;
	int		string_size;
	int		i;

	if (string == NULL)
		return (NULL);
	string_size = ft_strlen(string);
	copy_string = (char *) malloc(sizeof(char) * string_size + 1);
	if (copy_string == 0)
		return (0);
	i = 0;
	while (string[i] != '\0')
	{
		copy_string[i] = string[i];
		i++;
	}
	copy_string[i] = '\0';
	return (copy_string);
}

char	*ft_strjoin(char *backup, char *buf)
{
	char	*new_backup;
	int		backup_size;
	int		buf_size;

	backup_size = ft_strlen(backup);
	buf_size = ft_strlen(buf);
	new_backup = (char *) malloc(sizeof(char) * (backup_size + buf_size) + 1);
	if (new_backup == 0)
		return (0);
	while (*backup != '\0')
	{
		*new_backup = *backup;
		new_backup++;
		backup++;
	}
	while (*buf != '\0')
	{
		*new_backup = *buf;
		new_backup++;
		buf++;
	}
	*new_backup = '\0';
	free(backup - backup_size);
	return (new_backup - backup_size - buf_size);
}

char	*ft_strchr(const char *s, int c)
{
	if (s == 0)
		return (0);
	while (*s != (char) c)
	{
		if (*s == '\0')
			return (0);
		s++;
	}
	return ((char *) s);
}

char	*get_backup(char *buf, char *backup, int read_size, int fd)
{
	while (read_size > 0)
	{
		buf[read_size] = '\0';
		if (backup == NULL)
			backup = ft_strdup(buf);
		else
			backup = ft_strjoin(backup, buf);
		if (ft_strchr(backup, '\n') != NULL)
			break ;
		else
			read_size = read(fd, buf, BUFFER_SIZE);
	}
	if (read_size == 0 && backup[ft_strlen(backup) - 1] == '\n')
		backup[ft_strlen(backup) - 1] = '\0';
	return (backup);
}

char	*ft_substr(char *string, int start, int size)
{
	char	*substring;
	int		i;
	int		j;
	
	substring = (char *) malloc(sizeof(char) * size + 1);
	if (substring == 0)
		return (0);
	i = start;
	j = 0;
	while (i < size)
	{
		substring[j] = string[i];
		j++;
		i++;
	}
	substring[j] = '\0';
	return (substring);
}

char	*get_line(char *line, char *backup)
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
		size = newline_point  + 1;
		line = ft_substr(backup, 0, size);
	}
	else
		line = ft_strdup(backup);
	return (line);
}

char	*renewal_backup(char *backup)
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
		free(temp);
	}
	else
	{
		temp = backup;
		backup = ft_strdup("");
		free(temp);
	}
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
	if (buf[0] == '\n' && read_size == 1)
	{
		free(buf);
		buf = NULL;
		return (NULL);
	}
	backup = get_backup(buf, backup, read_size, fd);
	free(buf);
	buf = NULL;
	line = get_line(line, backup);
	backup = renewal_backup(backup);
	return (line);
}
/*
1. fd를 받는다.
2. buf에 메모리를 할당하다.
3. buf값과 read_size값을 구하다.
4. read_size가 0보다 작거나 같거나 buf[0]이 \n이면서 read_size가 1이면 
	4.1. buf메모리를 해제하다.
	4.2. NULL을 리턴하다.
5. read_size가 0보다 클 동안 반복하다.
	5.1. backup이 없으면
		5.1.1. backup에 메모리를 할당하다.
		5.1.2. backup을 구하다.
	5.2. backup이 있으면
		5.2.1. temp를 구하다.
		5.2.2. new_backup에 메모리를 할당하다.
		5.2.3. new_backup을 구하다.
		5.2.4. temp 메모리를 해제하다.
		5.2.5. new_backup을 반환하다.
		5.2.6. backup을 구하다.
	5.3. backup에 개행이 있는지를 확인하다.
		5.3.1. 있으면 반복문을 탈출하다.
	5.4. read_size와 buf를 구하다.
6. buf메모리를 해제하다.
7. backup에 개행문자가 있는지를 확인하다.
	7.1. 개행문자가 있으면
		7.1.1. line을 구하다.
		7.1.2. backup을 구하다.
	7.2. 개행문자가 없으면
		7.1.1. line을 구하다.
		7.1.2. backup을 구하다.
8. line을 반환하다.	
*/
