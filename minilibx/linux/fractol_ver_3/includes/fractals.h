#ifndef FRACTALS_H
#define FRACTALS_H

#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>

#define WIDTH 1024
#define HEIGHT 768
#define MAX_ITER 100
#define THREADS 8

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

typedef struct s_thread
{
	t_data	*data;
	int		start_y;
	int		end_y;
}				t_thread;

void	draw_fractal(t_data *data);
int		key_hook(int keycode, t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		get_color(int iteration, int max_iteration);
void	*draw_fractal_part(void *arg);

#endif
