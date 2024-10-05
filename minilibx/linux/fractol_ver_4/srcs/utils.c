#include "../includes/fractals.h"

int resize_hook(t_data *data)
{
	XWindowAttributes attr;
	int new_width;
	int new_height;

	XGetWindowAttributes(data->mlx, data->win, &attr);
	new_width = attr.width;
	new_height = attr.height;
	if (new_width != data->width || new_height != data->height)
	{
		data->width = new_width;
		data->height = new_height;
		mlx_destroy_image(data->mlx, data->img);
		data->img = mlx_new_image(data->mlx, data->width, data->height);
		data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
									   &data->line_length, &data->endian);
		draw_fractal(data);
	}
	return (0);
}
