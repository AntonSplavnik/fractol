/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:17:50 by asplavni          #+#    #+#             */
/*   Updated: 2024/10/15 14:48:29 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

void	mandelbrot_vs_julia(t_complex *complex_z,
			t_complex *complex_c, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		complex_c->x = fractal->julia_x;
		complex_c->y = fractal->julia_y;
	}
	else
	{
		complex_c->x = complex_z->x;
		complex_c->y = complex_z->y;
	}
}

void	render_pixel_row(int y, t_fractal *fractal)
{
	t_bounds	bounds_x;
	t_bounds	bounds_y;
	double		mapped_y;
	int			x;
	t_complex	z;

	bounds_x = (t_bounds){-2, +2, 0, WIDTH};
	bounds_y = (t_bounds){+2, -2, 0, HEIGHT};
	mapped_y = (map(y, bounds_y) * fractal->zoom) + fractal->shift_y;
	x = 0;
	while (x < WIDTH)
	{
		z.x = (map(x, bounds_x) * fractal->zoom) + fractal->shift_x;
		z.y = mapped_y;
		handle_pixel(x, y, fractal);
		x++;
	}
}

void	draw_image_to_window(t_fractal *fractal)
{
	mlx_put_image_to_window(fractal->mlx_connection, fractal->mlx_window,
		fractal->img.img_ptr, 0, 0);
}

void	fractal_render(t_fractal *fractal)
{
	pthread_t		threads[4];
	t_thread_data	thread_data[4];
	int				rows_per_thread;
	int				i;

	rows_per_thread = HEIGHT / 4;
	i = 0;
	while (i < 4)
	{
		thread_data[i].start_row = i * rows_per_thread;
		thread_data[i].end_row = (i + 1) * rows_per_thread;
		thread_data[i].fractal = fractal;
		pthread_create(&threads[i], NULL, thread_render, &thread_data[i]);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	draw_image_to_window(fractal);
}
