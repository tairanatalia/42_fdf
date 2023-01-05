/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomes-t <ngomes-t@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:13:57 by ngomes-t          #+#    #+#             */
/*   Updated: 2023/01/05 04:07:50 by ngomes-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../42_libft/libft.h"
#include <stdio.h>

/* colocar imagem na janela */
void	mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}
//*/

/* fechar janela */
int key_hook(int keycode, t_win *win)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(win->mlx, win->mlx_win);
		mlx_destroy_display(win->mlx);
		if (win->mlx)
			free(win->mlx);
		exit(1);
	}
	printf("%d \n", keycode);
	return (0);
}
//*/

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
			cols++;
		}
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
	close(fd);
}

/* escala x10 */
void	scale(t_dot **dot_matrix, t_mapdim dimensions)
{
	int	rows;
	int	cols;

	rows = 0;
	while (rows < dimensions.rows)
	{
		cols = 0;
		while (cols < dimensions.cols)
		{
			dot_matrix[rows][cols].x *= 10;
			dot_matrix[rows][cols].y *= 10;
			cols++;
		}
		rows++;
	}
}

void	pointer_checker(char **pointer)
{
	if (!pointer)
	{
		ft_putstr_fd("erro", 2);
		exit(1);
	}
}

/* desenhar linha entre os pontos */
int	biggest(float x, float y)
{
	if (x > y)
		return (x);
	return (y);
}

int	abs(int n)
{
	if (n >= 0)
		return (n);
	return (-n);
}

void	bresenham(float x, float y, float x1, float y1, t_img img)
{
	float	delta_x;
	float	delta_y;
	int		max;

	delta_x = x1 - x;
	delta_y = y1 - y;
	max = biggest(delta_x, delta_y);
	delta_x /= max;
	delta_y /= max;
	while ((int)(x - x1) ||| (int)(y - y1))
	{
		mlx_pixel_put(&win.mlx, x, y, WHITE);
		x += delta_x;
		y += delta_y;
	}
}

int main(int argc, char **argv)
{
	t_dot		**dot_matrix;
	t_mapdim	dimensions;
	t_win		win;
	t_img		img;
	//int	rows = 0, cols;
	int	len;

	/*  tratamentos de possiveis erros de entrada */
	if (argc != 2)
		error_message("erro");
	else
	{
		len = ft_strlen(argv[1]) - 1;
		if (argv[1][len] != 'f' || argv[1][len - 1] != 'd' || argv[1][len - 2] != 'f' 
		|| argv[1][len - 3] != '.')
		error_message("error");
		exit (1);
	}

	get_dimensions(argv[1], &dimensions);	
	dot_matrix = ft_calloc(sizeof(t_dot *), dimensions.rows + 1);
	get_coords(dot_matrix, dimensions, argv[1]);
	scale(dot_matrix, dimensions);

	win.mlx = mlx_init();
	win.mlx_win = mlx_new_window(win.mlx, WIDTH, HEIGHT, "FDF");
	// img.img = mlx_new_image(win.mlx, WIDTH, HEIGHT);
	// img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_length,
	// 							&img.endian);

	/* teste
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
	*/
	mlx_put_image_to_window(win.mlx, win.mlx_win, img.img, 0, 0);
	mlx_key_hook(win.mlx_win, key_hook, &win);
	mlx_loop(win.mlx);
	mlx_destroy_image(win.mlx, img.img);
}
