/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomes-t <ngomes-t@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:13:57 by ngomes-t          #+#    #+#             */
/*   Updated: 2023/01/05 04:56:12 by ngomes-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../42_libft/libft.h"
#include <stdio.h>

/* colocar imagem na janela 
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}
*/

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
void	get_coords(t_fdf *fdf, char *filename)
{
	char	*line_content;
	char	**splitted_line;
	char	**splitted_value;
	int		rows;
	int		cols;
	int		fd;

	rows = 0;
	printf(" 62 inicio debug\n");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_message("erro");
	printf(" 66 arquivo aberto\n");
	while (rows < fdf->map.rows)
	{
			// printf("while de leitura\n");
		cols = 0;
		line_content = ft_get_next_line(fd);
		// printf("%s", line_content);
		if (!line_content)
			break;
		splitted_line = ft_split(line_content, ' ');
		fdf->map.dot_matrix[rows] = ft_calloc(sizeof(t_dot), fdf->map.cols + 1);
		while (cols < fdf->map.cols)
		{
			// printf("while de alocação\n");
			fdf->map.dot_matrix[rows][cols].x = cols;
			fdf->map.dot_matrix[rows][cols].y = rows;
			if (ft_strchr(splitted_line[cols], ','))
			{
				splitted_value = ft_split(splitted_line[cols], ',');
				// printf("splitted_value[0] = %s e [1] = %s", splitted_value[0], splitted_value[1]);
				fdf->map.dot_matrix[rows][cols].z = ft_atoi(splitted_value[0]);
				// printf("%d", fdf->map.dot_matrix[rows][cols].z);
				fdf->map.dot_matrix[rows][cols].color = ft_htoi(splitted_value[1]);
				// printf("%d", fdf->map.dot_matrix[rows][cols].color);
				double_free(splitted_value);
			}
			else
			{
				fdf->map.dot_matrix[rows][cols].z = ft_atoi(splitted_line[cols]);
				// printf("%d\n", fdf->map.dot_matrix[rows][cols].z);
				fdf->map.dot_matrix[rows][cols].color = WHITE;
			}
			cols++;
		}
		// dot_matrix[rows] = NULL;
		free(line_content);
		double_free(splitted_line);
		rows++;
	}
	close(fd);
	printf("deu certo essa merda\n");
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
void	get_dimensions(char *filename, t_fdf *fdf)
{
	int	fd;
	char	*line;
	char	**splitted;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_message("erro");
	line = ft_get_next_line(fd);
	splitted = ft_split(line, ' ');
	fdf->map.cols = 0;
	while (splitted[fdf->map.cols] != NULL)
		fdf->map.cols++;
	fdf->map.rows = 0;
	while (line)
	{
		free(line);
		line = ft_get_next_line(fd);
		fdf->map.rows++;
	}
	double_free(splitted);
	close(fd);
	printf(" mapa %d x %d \n", fdf->map.rows, fdf->map.cols);
	printf(" 143 get dim ok \n");
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

// void	zoom(float *x, float *y, float *x1, float *y1, t_map *map)
// {
// 	x *= map->zoom;
// 	y *= map->zoom;
// 	x1 *= map->zoom;
// 	y1 *= map->zoom;
// }

// void	isometric()

void	bresenham(float x, float y, float x1, float y1, t_fdf *fdf)
{
	float	delta_x;
	float	delta_y;
	int		max;
	int		z;
	int		z1;

	z = fdf->map.dot_matrix[(int)x][(int)y].z;
	printf("%i", z);
	z1 = fdf->map.dot_matrix[(int)x1][(int)y1].z;
	printf("%i", z1);


	/* escala do mapa */
	x *= fdf->map.zoom;
	y *= fdf->map.zoom;
	x1 *= fdf->map.zoom;
	y1 *= fdf->map.zoom;
	// zoom(&x, &y, &x1, &y1, &fdf->map);

	/* cor */

	delta_x = x1 - x;
	delta_y = y1 - y;
	max = biggest(delta_x, delta_y);
	delta_x /= max;
	delta_y /= max;
	while ((int)(x - x1) || (int)(y - y1))
	{
		mlx_pixel_put(fdf->win.mlx, fdf->win.mlx_win, x, y, /*fdf->map.dot_matrix \
		[(int)x][(int)y].color*/WHITE);
		x += delta_x;
		y += delta_y;
	}
}

void	draw(t_fdf *fdf)
{
	int	row;
	int	col;

	row = 0;
	while (row <= fdf->map.rows)
	{
		col = 0;
		while (col <= fdf->map.cols)
		{
			if (col < fdf->map.cols)
				bresenham(col, row, col + 1, row, fdf);
			if (row < fdf->map.rows)
				bresenham(col, row, col, row + 1, fdf);
			col++;
		}
		row++;
	}
}

void	test(t_fdf *fdf)
{
	int	row = 0 , col;
	while (row < fdf->map.rows)
	{
		col = 0;
		while (col < fdf->map.cols)
		{
			printf(" %d ", fdf->map.dot_matrix[row][col].z);
			col++;
		}
		printf("\n");
		row++;
	}
}


int main(int argc, char **argv)
{
	t_fdf	*fdf;
	// t_dot		**dot_matrix;
	// t_map	map;
	// t_win		win;
	int	len;

	/*  tratamentos de possiveis erros de entrada */
	if (argc != 2)
		error_message("erro");
	else
	{
		len = ft_strlen(argv[1]) - 1;
		if (argv[1][len] != 'f' || argv[1][len - 1] != 'd' || argv[1][len - 2] != 'f' 
		|| argv[1][len - 3] != '.')
		{
			error_message("error");
			exit (1);
		}
	}
	fdf = (t_fdf *)malloc(sizeof(fdf));
	get_dimensions(argv[1], fdf);
	printf(" 279 antes da aloc\n");
	printf(" vamo ve se ta td certo\n fdf->map.rows = %d\n", fdf->map.rows);
	fdf->map.dot_matrix = ft_calloc(sizeof(t_dot *), fdf->map.rows); //Invalid write of size 8
	printf("checagem antes da func get_coords\n");
	get_coords(fdf, argv[1]); //Invalid read of size 8
	printf("check depois da func get_coords\n");
	fdf->win.mlx = mlx_init();
	fdf->win.mlx_win = mlx_new_window(fdf->win.mlx, WIDTH, HEIGHT, "FDF");
	// img.img = mlx_new_image(fdf.win.mlx, WIDTH, HEIGHT);
	// img.addr = mlx_get_data_addr(fdf.img.img, &fdf.img.bpp, &fdf.img.line_length,
	// 							&fdf.img.endian);

	// mlx_put_image_to_window(fdf.win.mlx, fdf.win.mlx_win, fdf.img.img, 0, 0);
	// mlx_pixel_put(&fdf.win.)
	//bresenham(10, 10, 600, 300, fdf.win);
	fdf->map.zoom = 30;
	test(fdf);
	draw(fdf);
	mlx_key_hook(fdf->win.mlx_win, key_hook, &fdf->win);
	mlx_loop(fdf->win.mlx);
	// mlx_destroy_image(fdf.win.mlx, fdf.img.img);
}
