#include "../includes/fractals.h"

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 65361) // Left arrow key
		data->offset_x -= 0.1 / data->zoom;
	else if (keycode == 65363) // Right arrow key
		data->offset_x += 0.1 / data->zoom;
	else if (keycode == 65362) // Up arrow key
		data->offset_y -= 0.1 / data->zoom;
	else if (keycode == 65364) // Down arrow key
		data->offset_y += 0.1 / data->zoom;
	else if (keycode == 'z')
		data->zoom *= 1.1;
	else if (keycode == 'x')
		data->zoom /= 1.1;
	else if (keycode == 65307) // Escape key
		exit(0);
	draw_fractal(data);
	return (0);
}
