#include "minilibx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#define WIDTH	500
#define HEIGHT 500

typedef struct s_data {
    void *mlx;
    void *win;
} t_data;

void	draw_square(void *mlx, void *win, int x, int y, int size, int color);
int		close_window(int keycode, t_data *data);

int	main(void)
{
	t_data	data;
	int		size;
	int		x;
	int		y;

	size = WIDTH * 0.8;
	x = WIDTH / 2;
	y = HEIGHT / 2;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "My window");

	draw_square(data.mlx, data.win, x - size / 2, y - size / 2, size, 0x37C780);
	mlx_string_put(data.mlx, data.win, WIDTH * 0.45, HEIGHT * 0.95, 0xC420E3,"LazyPixel");
    mlx_key_hook(data.win, close_window, &data);

	mlx_loop(data.mlx);
	return (0);
}

void draw_square(void *mlx, void *win, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_pixel_put(mlx, win, x + j , y + i, color);
			j++;
		}
		i++;
	}
}

int close_window(int keycode, t_data *data)
{
	printf("Keycode: %d\n", keycode);

    if (keycode == 53)  // ESC key
    {
        mlx_destroy_window(data->mlx, data->win);
        exit(0);
    }
	else if (keycode == 120)
		printf("X key was pressed\n");
	else if (keycode == 121)
		printf("Y key was pressed\n");

    return (0);
}
