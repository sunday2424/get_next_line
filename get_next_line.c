/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junpark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 14:51:28 by junpark           #+#    #+#             */
/*   Updated: 2019/03/14 02:26:04 by junpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int check_new_line(int fd, char **line, char **str)
{
	int		i;
	char	*temp;

	return (1);
}

int	get_next_line(const int fd, char **line)
{
	int			readsize;
	char		buff[BUFF_SIZE + 1];
	char		*temp;
	static char	**str;

	if (line == NULL || fd < 0)
		return (-1);
	while ((readsize = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[readsize] = '\0';
		if(str[fd] == NULL)
			str[fd] = ft_strnew(1);
		temp = ft_strjoin(str[fd], buff);
		free(str[fd]);
		str[fd] = temp;
		if (ft_strchr(buff, '\n'))
			break;
	}
	if (readsize < 0)
		return (-1);
	else if (readsize == 0 && (str[fd] == NULL || str[fd][0] == NULL))
		return (0);
	return (check_new_line(fd, line, str));
}

int main(int argc, char **argv)
{
    int fd;
    int fd2;
    char *line;

    line = NULL;
    fd = 0;
    fd2 = 0;
    if (argc == 1)
        fd = 0;
    else if (argc == 2)
    {
        fd = open (argv[1], O_RDONLY);
        while(get_next_line(fd, &line) == 1)
        {
            ft_putendl(line);
            ft_putendl("----");
            free(line);
        }
        close(fd);
    }
    else {
        fd = open(argv[1], O_RDONLY);
        fd2 = open(argv[2], O_RDONLY);
        while (1 == get_next_line(fd, &line)) {
            ft_putendl(line);
            ft_putendl("-----");
            free(line);
            if (get_next_line(fd2, &line) == 1) {
                ft_putendl(line);
                ft_putendl("*****");
                free(line);
            }
        }
        close(fd);
        close(fd2);
    }
    return 0;
}
