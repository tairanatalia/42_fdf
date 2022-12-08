#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "./42_libft/libft.h"

void	error_message(char *message)
{
	if (errno == 0)
		ft_putendl_fd(message, 2);
	else
		perror(message);
	exit (1);
}

int    count_lines(void)
{
    int    fd;
    int    lines;

    fd = open("teste1", O_RDONLY);
    if (fd < 0)
        error_message("erro");
    lines = 0;
    while (ft_get_next_line(fd) != NULL)
        lines++;
    close(fd);
    return (lines);
}


int count_columns(void)
{
    int     fd;
    int     columns;
    char    *line;
    char    **splitted;

    fd = open("teste1", O_RDONLY);
    if (fd < 0)
        error_message("erro");
    line = ft_get_next_line(fd);
    printf("line = %s", line);
    splitted = ft_split(line, ' ');
    columns = 0;
    while (*splitted != NULL)
    {
        printf("*splitted = %s\n", *splitted);
        splitted++;
        columns++;
    }
    close(fd);
    return (columns);
}

int main(void)
{
    int lines;
    int columns;
    char    **splitted;
    
    lines = count_lines();
    columns = count_columns();
    printf("lines = %d, columns = %d\n", lines, columns);
    return (0);
}