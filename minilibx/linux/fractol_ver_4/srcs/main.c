#include "../includes/fractals.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int get_color(int iteration, int max_iteration)
{
	double t;
	int red;
	int green;
	int blue;

	if (iteration == max_iteration)
		return (0x000000); // Black for points in the set
	t = (double)iteration / max_iteration;
	red = (int)(9 * (1 - t) * t * t * t * 255);
	green = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	blue = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return ((red << 16) | (green << 8) | blue);
}

void *draw_fractal_part(void *arg)
{
	t_thread *thread;
	t_data *data;
	int x, y;
	double pr, pi;
	double new_re, new_im, old_re, old_im;
	int i;

	thread = (t_thread *)arg;
	data = thread->data;
	y = thread->start_y;
	while (y < thread->end_y)
	{
		x = 0;
		while (x < data->width)
		{
			pr = 1.5 * (x - data->width / 2) / (0.5 * data->zoom * data->width) + data->offset_x;
			pi = (y - data->height / 2) / (0.5 * data->zoom * data->height) + data->offset_y;
			new_re = 0;
			new_im = 0;
			i = 0;
			while (i < MAX_ITER)
			{
				old_re = new_re;
				old_im = new_im;
				new_re = old_re * old_re - old_im * old_im + pr;
				new_im = 2 * old_re * old_im + pi;
				if ((new_re * new_re + new_im * new_im) > 4)
					break;
				i++;
			}
			my_mlx_pixel_put(data, x, y, get_color(i, MAX_ITER));
			x++;
		}
		y++;
	}
	return (NULL);
}

void draw_fractal(t_data *data)
{
	pthread_t threads[THREADS];
	t_thread thread_data[THREADS];
	int i;

	i = 0;
	while (i < THREADS)
	{
		thread_data[i].data = data;
		thread_data[i].start_y = i * (data->height / THREADS);
		thread_data[i].end_y = (i + 1) * (data->height / THREADS);
		pthread_create(&threads[i], NULL, draw_fractal_part, &thread_data[i]);
		i++;
	}
	i = 0;
	while (i < THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
