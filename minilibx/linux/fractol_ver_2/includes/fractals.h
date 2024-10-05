#ifndef FRACTALS_H
#define FRACTALS_H

#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	double	zoom;
	double	offset_x;
	double	offset_y;
}				t_data;

void	draw_fractal(t_data *data);
int		key_hook(int keycode, t_data *data);
int		render_next_frame(t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
