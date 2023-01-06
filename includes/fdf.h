/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomes-t <ngomes-t@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:11:54 by ngomes-t          #+#    #+#             */
/*   Updated: 2023/01/07 00:00:13 by ngomes-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define HEIGHT 1080
# define WIDTH 1920
# define WHITE 0xFFFFFF

# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "../42_libft/libft.h"
# include "../minilibx-linux/mlx.h"

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}   t_img;

typedef struct s_win
{
	void	*mlx;
	void	*mlx_win;
}	t_win;

typedef struct s_dot
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_dot;

typedef struct s_fdf
{
	int	height;
	int	width;
	int	zoom;
	t_dot **dot_matrix;
	t_win	win;
	t_map	img;
}	t_fdf;

void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int		key_hook(int keycode, t_win *win);
void	double_free(char **str);
void	get_coords(t_fdf *fdf, char *filename);
void	error_message(char *message);
void	get_dimensions(char *filename, t_fdf *fdf);

#endif