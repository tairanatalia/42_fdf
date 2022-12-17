/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomes-t <ngomes-t@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:13:57 by ngomes-t          #+#    #+#             */
/*   Updated: 2022/12/17 20:11:01 by ngomes-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../42_libft/libft.h"
#include <stdio.h>


/* free em char **str */
void	double_free(char **str)
{
	if (*str != NULL)
		free(*str++);

}

/* inserir os mapa na matriz */
void	get_coords(t_dot **dot_matrix, t_mapdim dimensions, char *filename)
{
	char	*line_content;
	char	**splitted_line;
	char	**splitted_value;
	int		rows;
	int		cols;
	int		fd;

	rows = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_message("erro");
	while (rows < dimensions.rows)
	{
		cols = 0;
		line_content = ft_get_next_line(fd);
		if (!line_content)
			break;
		splitted_line = ft_split(line_content, ' ');
		dot_matrix[rows] = ft_calloc(sizeof(t_dot), dimensions.cols + 1);
		while (cols < dimensions.cols)
		{
			dot_matrix[rows][cols].x = cols;
			dot_matrix[rows][cols].y = rows;
			if (ft_strchr(splitted_line[cols], ','))
			{
				splitted_value = ft_split(splitted_line[cols], ',');
				dot_matrix[rows][cols].z = ft_atoi(splitted_value[0]);
				dot_matrix[rows][cols].color = ft_htoi(splitted_value[1]);
				double_free(splitted_value);
			}
			else
			{
				dot_matrix[rows][cols].z = ft_atoi(splitted_line[cols]);
				dot_matrix[rows][cols].color = WHITE;
			}
			printf("%d ", dot_matrix[rows][cols].z);
			cols++;
		}
		printf("\n");
		// dot_matrix[rows] = NULL;
		free(line_content);
		double_free(splitted_line);
		rows++;
	}
	close(fd);
}

/* tratamento de erro */
void	error_message(char *message)
{
	if (errno == 0)
		ft_putendl_fd(message, 2);
	else
		perror(message);
	exit (1);
}


/* medir as dimensões do mapa */
void	get_dimensions(char *filename, t_mapdim *dimensions)
{
	int	fd;
	int	columns;
	char	*line;
	char	**splitted;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_message("erro");
	line = ft_get_next_line(fd);
	splitted = ft_split(line, ' ');
	dimensions->cols = 0;
	while (splitted[dimensions->cols] != NULL)
		dimensions->cols++;
	dimensions->rows = 0;
	while (line)
	{
		free(line);
		line = ft_get_next_line(fd);
		dimensions->rows++;
	}
	double_free(splitted);
	printf("%d linhas e %d colunas\n", dimensions->rows, dimensions->cols);
	close(fd);
}


int main(int argc, char **argv)
{
	t_dot		**dot_matrix;
	t_mapdim	dimensions;
	int	rows = 0, cols;

	if (argc != 2)
		error_message("erro");
	get_dimensions(argv[1], &dimensions);	
	dot_matrix = ft_calloc(sizeof(t_dot *), dimensions.rows + 1);
	get_coords(dot_matrix, dimensions, argv[1]);

	/* teste */
	while (rows < dimensions.rows)
	{
		cols = 0;
		while (cols < dimensions.cols)
		{
			printf("%d ", dot_matrix[rows][cols].z);
			cols++;
		}
		printf("\n");
		rows++;
	}
}
