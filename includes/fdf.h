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
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}   t_img;

typedef struct s_win
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
}	t_win;

#endif

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	// int		bpp;
	// int		line_len;
	// int		endian;
}	t_img;

