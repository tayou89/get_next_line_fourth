/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tayou <tayou@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 13:59:24 by tayou             #+#    #+#             */
/*   Updated: 2023/01/29 14:07:08 by tayou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	return (new_backup - backup_size - buf_size);
}

char	*ft_substr(char *string, int start, int size)
{
	char	*substring;
	int		i;
	int		j;

	if (size == 0 || string == NULL)
		return (0);
	substring = (char *) malloc(sizeof(char) * size + 1);
	if (substring == 0)
		return (0);
	i = 0;
	j = 0;
	while (i < size)
	{
		substring[j] = string[start];
		j++;
		start++;
		i++;
	}
	substring[j] = '\0';
	return (substring);
}
