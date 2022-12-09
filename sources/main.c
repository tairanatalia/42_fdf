/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomes-t <ngomes-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:12:32 by ngomes-t          #+#    #+#             */
/*   Updated: 2022/12/08 21:32:06 by ngomes-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <stdio.h>

/* colocar imagem na janela */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

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

/* inserir os mapa na matriz */
void    get_coords(t_dot dot_matrix[][], t_mapdim dimensions)
{
    char    *line_content;
    char    **splitted;

    rows = 0;
    while (rows < dimensions.rows)
    {
        cols = 0
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



int main()
{
    t_win   win;
    t_img  img;
    t_dot   **dot_matrix;
    t_mapdim dimensions;

    int i;
    int j;

    i = 0;
    win.mlx = mlx_init();
    win.mlx_win = mlx_new_window(win.mlx, WIDTH, HEIGHT, "janela");
    img.img = mlx_new_image(win.mlx, WIDTH, HEIGHT);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
    while (i < 50)
    {
        j = 0;
        while (j < 50)
        {
            my_mlx_pixel_put(&img, i, j, 0XF5A442);
            j++;
        }
        i++;
    }
    while (i < 100)
    {
        j = 50;
        while (j < 100)
        {
            my_mlx_pixel_put(&img, i, j, 0XF5A442);
            j++;
        }
        i++;
    }
    dimensions.cols = count_columns(argv[1]);
    dimensions.rows = count_lines(argv[1]);
    dot_matrix = ft_calloc(t_dot *, dimensions.rows);
    
    mlx_put_image_to_window(win.mlx, win.mlx_win, img.img, 0, 0);
    mlx_destroy_image(win.mlx, img.img);
    mlx_key_hook(win.mlx_win, key_hook, &win);
    mlx_loop(win.mlx);
}