//This main is for test purpose only and does not meet norm requirements.

#include <fcntl.h>
#include "get_next_line.h"

int main (int argc, char **argv)
{
	int		fd;
	int		fd2;
	char	*line;

	line = NULL;
	fd = 0;
	fd2 = 0;
	if (argc == 1)
		fd = 0;
	else if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		while(get_next_line(fd, &line) == 1)
		{
			ft_putendl(line);
			ft_putendl("----");
			free(line);
		}
		close(fd);
	}
	else
	{
		fd = open(argv[1], O_RDONLY);
		fd2 = open(argv[2], O_RDONLY);
		while(1 == get_next_line(fd, &line)) 
		{
			ft_putendl(line);
			ft_putendl("-----");
			free(line);
			if (get_next_line(fd2, &line) == 1)
			{
				ft_putendl(line);
				ft_putendl("*****");
				free(line);
			}
		}
		close(fd);
		close(fd2);
	}
	return (0);
}
