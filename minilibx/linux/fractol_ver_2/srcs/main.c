#include "fractals.h"

int	main(void)
{
	t_data	data;

	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.win = mlx_new_window(data.mlx, 800, 600, "Fractals");
	if (!data.win)
		return (1);
	data.img = mlx_new_image(data.mlx, 800, 600);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
								  &data.line_length, &data.endian);
	data.zoom = 1.0;
	data.offset_x = 0.0;
	data.offset_y = 0.0;
	draw_fractal(&data);
	mlx_key_hook(data.win, key_hook, &data);
	mlx_loop(data.mlx);
	return (0);
}
