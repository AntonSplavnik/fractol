#include "fractals.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
int		get_color(int iteration, int max_iteration)
{
	double	t;
	int		red;
	int		green;
	int		blue;

	if (iteration == max_iteration)
		return (0x000000); // Black for points in the set
	t = (double)iteration / max_iteration;
	red = (int)(9 * (1 - t) * t * t * t * 255);
	green = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	blue = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return ((red << 16) | (green << 8) | blue);
}
void	draw_fractal(t_data *data)
{
	int		x;
	int		y;
	double	pr;
	double	pi;
	double	new_re;
	double	new_im;
	double	old_re;
	double	old_im;
	int		i;
    int		max_iterations = 100;


	y = 0;
	while (y < 600)
	{
		x = 0;
		while (x < 800)
		{
			pr = 1.5 * (x - 800 / 2) / (0.5 * data->zoom * 800) + data->offset_x;
			pi = (y - 600 / 2) / (0.5 * data->zoom * 600) + data->offset_y;
			new_re = 0;
			new_im = 0;
			i = 0;
			while (i < max_iterations)
			{
				old_re = new_re;
				old_im = new_im;
				new_re = old_re * old_re - old_im * old_im + pr;
				new_im = 2 * old_re * old_im + pi;
				if ((new_re * new_re + new_im * new_im) > 4)
					break ;
				i++;
			}
            my_mlx_pixel_put(data, x, y, get_color(i, max_iterations));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
