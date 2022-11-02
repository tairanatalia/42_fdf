/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngomes-t <ngomes-t@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 00:18:35 by ngomes-t          #+#    #+#             */
/*   Updated: 2022/11/02 02:22:09 by ngomes-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>


// typedef struct s_img
// {
// 	void	*mlx_img;
// 	char	*addr;
// 	int		bpp; /* bits per pixel */
// 	int		line_len;
// 	int		endian;
// }	t_img;

// typedef struct s_mlx
// {
// 	void	*mlx_ptr;
// 	void	*win_ptr;
// 	t_img	img;
// 	int		cur_img;
// }	t_mlx;

int	main(int argc, char **argv)
{
	int	fd;
	char	*str;
	t_dot	dot;
	char	**splitted;

	argc = 0;
	fd = open(argv[1], O_RDONLY);
	str = ft_get_next_line(fd);
	while (str)
	{
		splitted = ft_split(str, ' ');
		while (*splitted)
		{
			dot.z = ft_atoi(*splitted);
			printf("%d", dot.z);
			splitted++;
		}
		printf("\n");
		str = ft_get_next_line(fd);
	}
}
--------
1. contar linhas e colunas
2. alocação dos pontos
3. salvar todas informações dentro do ponto criado
4. criar janela
4. colocar os pontos na tela
5. transformações lineares
6. bresenham

	//tratamento de erros iniciais
// 	if (argc != 2)
// 		fazer algo pra sair e colocar uma mensagem de erro

// 	//inicialização de ponteiros e verificação de erro de inicialização
// 	mlx.mlx_ptr = mlx_init();
// 	if (mlx.mlx_ptr == NULL)
// 		return (ERRO_MLX)

// 	/*
// 		código para capturar as dimensões do mapa
// 	*/

// 	//inicialização da janela e verificação de inicialização
// 	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, ALTURA, LARGURA, *argv[2]);
// 	if (mlx.win_ptr == NULL)
// 	{
// 		free(mlx.win_ptr);
// 		return (ERRO_MLX);
// 	}

// 	//criar imagem 
// 	mlx.img.mlx_img = mlx_new_image(mlx.mlx_ptr, ALTURA, LARGURA);
// 	mlx.img.addr = mlx_get_data_addr(mlx.img.mlx_img, &mlx.img.bpp,
// 			&mlx.img.line_len, &mlx.img.endian);

// 	//loop de renderização
// 	mlx_loop_hook(data.mlx_ptr, &render, &mlx);

// 	//eventos de teclado
// 	int	handle_keypress(int keysym, t_data *data)
// {
// 	if (keysym == XK_Escape)
// 	{
// 		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
// 		data->win_ptr = NULL;
// 	}
// 	return (0);
// }
// 	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

// 	//manter a janela aberta
// 	mlx_loop(data.mlx_ptr);

// 	//procedimento para fechar tudo
// 	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
// 	mlx_destroy_display(data.mlx_ptr);
// 	free(data.mlx_ptr);
