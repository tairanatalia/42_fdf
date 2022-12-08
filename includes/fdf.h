/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomes-t <ngomes-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:11:54 by ngomes-t          #+#    #+#             */
/*   Updated: 2022/12/08 16:17:39 by ngomes-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define HEIGHT 1080
# define WIDTH 1920

#include "../42_libft/libft.h"
#include "../minilibx-linux/mlx.h"

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
	void	*img;
}	t_win;

typedef struct s_mapdim
{
	int	rows;
	int	cols;
}	t_mapdim;

typedef struct s_dot
{
	int	x;
	int	y;
	int	color;
}	t_dot;

#endif