/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:09:32 by asplavni          #+#    #+#             */
/*   Updated: 2024/10/14 19:29:53 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_complex	get_mapped_complex(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_bounds	bounds_x;
	t_bounds	bounds_y;

	bounds_x = (t_bounds){-2, +2, 0, WIDTH};
	bounds_y = (t_bounds){+2, -2, 0, HEIGHT};
	z.x = (map(x, bounds_x) * fractal->zoom) + fractal->shift_x;
	z.y = (map(y, bounds_y) * fractal->zoom) + fractal->shift_y;
	return (z);
}

static int	get_pixel_color(int i, t_fractal *fractal)
{
	t_bounds	color_bounds;

	color_bounds = (t_bounds){BLACK, WHITE,
		0, fractal->iterations_defintion};
	return (map(i, color_bounds));
}

static void	handle_fractal_iteration(t_complex *z,
	t_complex c, int *i, t_fractal *fractal)
{
	while (*i < fractal->iterations_defintion)
	{
		*z = sum_complex(square_complex(*z), c);
		if ((z->x * z->x) + (z->y * z->y) > fractal->escape_value)
			break ;
		++(*i);
	}
}

void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z = get_mapped_complex(x, y, fractal);
	mandelbrot_vs_julia(&z, &c, fractal);
	handle_fractal_iteration(&z, c, &i, fractal);
	if (i < fractal->iterations_defintion)
	{
		color = get_pixel_color(i, fractal);
		pixel_put(x, y, &fractal->img, color);
	}
	else
	{
		pixel_put(x, y, &fractal->img, WHITE);
	}
}
