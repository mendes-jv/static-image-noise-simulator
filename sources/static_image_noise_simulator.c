/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_image_noise_simulator.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jovicto2 <jovicto2@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:28:35 by jovicto2          #+#    #+#             */
/*   Updated: 2023/09/12 14:28:35 by jovicto2         ###   ########.org.br   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/static_image_noise_simulator.h"

static void	randomizer(void);
static int32_t	pixel(int32_t r, int32_t g, int32_t b, int32_t a);
static void	ft_hook(void* param);

static mlx_image_t* image;

int	main(void)
{
	mlx_t		*mlx;

	mlx_set_setting(MLX_FULLSCREEN, true);
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "Static Image Noise Simulator", true))
		|| !(image = mlx_new_image(mlx, WIDTH, HEIGHT))
		|| mlx_image_to_window(mlx,image, 0, 0) == -1)
	{
		if (mlx)
			mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	mlx_set_cursor_mode(mlx, MLX_MOUSE_DISABLED);
	mlx_loop_hook(mlx, (void (*)(void *)) randomizer, mlx);
	mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

static void	randomizer(void)
{
	for (uint32_t x = 0; x < image->width; ++x)
		for (uint32_t y = 0; y < image->height; ++y)
			mlx_put_pixel(image, x, y, pixel(
					(int32_t)random() % 0xFF,
					(int32_t)random() % 0xFF,
					(int32_t)random() % 0xFF,
					(int32_t)random() % 0xFF
			));
}

static int32_t pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void ft_hook(void* param) {
	mlx_t *mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}