/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:17:50 by asplavni          #+#    #+#             */
/*   Updated: 2024/10/14 19:32:15 by asplavni         ###   ########.fr       */
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

static void	render_pixel_row(int y, t_fractal *fractal)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		handle_pixel(x, y, fractal);
	}
}

static void	draw_image_to_window(t_fractal *fractal)
{
	mlx_put_image_to_window(fractal->mlx_connection, fractal->mlx_window,
		fractal->img.img_ptr, 0, 0);
}

void	fractal_render(t_fractal *fractal)
{
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		render_pixel_row(y, fractal);
	}
	draw_image_to_window(fractal);
}
