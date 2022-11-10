/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomes-t <ngomes-t@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 23:07:00 by ngomes-t          #+#    #+#             */
/*   Updated: 2022/11/02 02:10:09 by ngomes-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "../42_libft/libft.h"

#include <X11/X.h>
#include <X11/keysym.h>

typedef struct s_dot
{
	int	x;
	int	y;
	int	z;
}	t_dot;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	// int		bpp;
	// int		line_len;
	// int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	int		cur_img;
}	t_data;

typedef struct s_map
{
	char	**line_row;

}	t_lines;

#endif