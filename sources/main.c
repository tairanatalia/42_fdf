/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomes-t <ngomes-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:12:32 by ngomes-t          #+#    #+#             */
/*   Updated: 2022/12/08 16:12:35 by ngomes-t         ###   ########.fr       */
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

void    seta_valores(matriz matrix[][])
{
    enquanto ( i < linhas)
    {
        j = 0
        matriz[i] = calloc(tamanho(matriz), colunas);
        enquanto (j < colunas)
        {
            matriz[i] = colunas;
            matriz[j] = linhas;
            matriz[z] = atoi(split[colunas]);
        }
    }

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



int main()
{
    t_win   win;
    t_img  img;
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
    matriz = calloc(tamanho(matriz), linhas);
    mlx_put_image_to_window(win.mlx, win.mlx_win, img.img, 0, 0);
    mlx_destroy_image(win.mlx, img.img);
    mlx_key_hook(win.mlx_win, key_hook, &win);
    mlx_loop(win.mlx);
}