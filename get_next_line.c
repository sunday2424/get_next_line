/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junpark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:51:28 by junpark           #+#    #+#             */
/*   Updated: 2019/03/26 00:11:09 by junpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		check_new_line(int fd, int readsize, char **line, char **str)
{
	int		i;
	char	*temp;

	i = 0;
	while (str[fd][i] != '\n' && str[fd][i] != '\0')
		i++;
	if (str[fd][i] == '\n')
	{
		*line = ft_strsub(str[fd], 0, i);
		temp = ft_strdup(str[fd] + i + 1);
		free(str[fd]);
		str[fd] = temp;
		if (str[fd][0] == '\0')
			ft_strdel(&str[fd]);
	}
	else if (str[fd][i] == '\0')
	{
		if (readsize == BUFF_SIZE)
			return (get_next_line(fd, line));
		*line = ft_strdup(str[fd]);
		ft_strdel(&str[fd]);
	}
	return (1);
}

void	buffer_to_str(int fd, char **str, char *buff)
{
	char	*temp;

	temp = ft_strjoin(str[fd], buff);
	ft_strdel(&str[fd]);
	str[fd] = ft_strdup(temp);
	ft_strdel(&temp);
}

int		get_next_line(const int fd, char **line)
{
	int			readsize;
	char		buff[BUFF_SIZE + 1];
	static char	*str[4096];

	if (line == NULL || fd < 0)
		return (-1);
	while ((readsize = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[readsize] = '\0';
		if (str[fd] == NULL)
			str[fd] = ft_strnew(0);
		buffer_to_str(fd, str, buff);
		if (ft_strchr(buff, '\n'))
			break ;
	}
	if (readsize < 0)
		return (-1);
	else if (readsize == 0 && str[fd] == NULL)
		return (0);
	return (check_new_line(fd, readsize, line, str));
}
