#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "./42_libft/libft.h"
#include "./includes/fdf.h"
#include <stdio.h>

/* tratamento de erro */
void	error_message(char *message)
{
	if (errno == 0)
		ft_putendl_fd(message, 2);
	else
		perror(message);
	exit (1);
}

/* free em char **str */
void    double_free(char **str)
{
    if (*str != NULL)
        free(*str++);
}

/* inserir o mapa na matriz */
void    get_coords(t_dot **dot_matrix, t_mapdim dimensions)
{
    char    *line_content;
    char    **splitted;
    int     rows;
    int     cols;
    int     fd;

    rows = 0;
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_message("erro");
    while (rows < dimensions.rows)
    {
        cols = 0;
        line_content = ft_get_next_line(fd);
        dot_matrix[rows] = ft_calloc(t_dot, dimensions.cols);
        while (cols < dimensions.cols)
        {
            dot_matrix.x = cols;
            dot_matrix.y = row;
            if (ft_strchr(line_content), ',')
            {
                splitted = ft_split(line_content, ' ');
                dot_matrix.z = splitted[0];
                dot_matrix.color = ft_htoi(splitted[1]);
                cols++
            }
            else
            {
                dot_matrix.z = ft_atoi(ft_split[cols]);
                dot_matriz.color = WHITE;
                cols++            
            }
        }
        rows++;
    }
    free(line_content);
    double_free(splitted);
}



/* medir as dimensões do mapa */
int    count_lines(char *filename)
{
    int    fd;
    int    lines;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_message("erro");
    lines = 0;
    while (ft_get_next_line(fd) != NULL)
        lines++;
    return (lines);
}
int count_columns(filename)
{
    int     fd;
    int     columns;
    char    *line;
    char    **splitted;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_message("erro");
    line = ft_get_next_line(fd);
    splitted = ft_split(line, ' ');
    columns = 0;
    while (splitted[0][columns] != NULL)
        columns++;
    free(line);
    double_free(splitted);
    close(fd);
    return (columns);
}

int main(void)
{
    char    *number = "#e35b71";
    char    *toupper = str_upper(number);
    printf("%s", toupper);
    return (0);
}

