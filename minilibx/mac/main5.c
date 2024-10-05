#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "./minilibx/mlx.h"
#include "fractol.h"
#define HEIGHT 500
#define WIDTH 500
#define ZOOM_SPEED 1.1

typedef struct {
    void *mlx;
    void *win;
    double zoom;
    double move;
    double offsetX;
    double offsetY;
} t_params;

void draw_mandelbrot(void *mlx, void *win, double zoom, double offsetX, double offsetY)
{
    int x;
    int y;
    double a = 0.0;
    double b = 0.0;
    double c = 0;
    double d = 0;
    double n = 0;

    int max_iter = 100;

    for (x = 0; x < WIDTH; x++)
    {
        for (y = 0; y < HEIGHT; y++)
        {
            a = 0.0;
            b = 0.0;
            c = 0;
            d = 0;
            n = 0;

            // Map pixel coordinates to complex plane with zoom and offset
            double realPart = (x - WIDTH / 2.0 + offsetX) * 6.0 / (WIDTH * zoom);
            double imagPart = (y - HEIGHT / 2.0 + offsetY) * 6.0 / (HEIGHT * zoom);

            while (n < max_iter)
            {
                c = a * a - b * b + realPart;
                d = 2 * a * b + imagPart;
                a = c;
                b = d;
                if (a * a + b * b > 4) break;
                n++;
            }
            int color;

            color = (0x242424 * n);

            // color = (n < 100) ? 0xFFFFFF : 0x000000;

            // if (n < 256)
            //     color = (int)(1023 - n);  // Blue
            // else if (n < 512)
            //     color = ((int)(511 - n)) << 16; // Red
            // else
            //     color = ((int)(255 - n)) << 8; // Green
            mlx_pixel_put(mlx, win, x, y, color);
        }
    }
}

int handle_key(int key, void *param)
{
    t_params *p = param;
    // double move_factor = 1.1; // Movement factor

    if (key == 53)  // 'ESC' key to exit
    {
        mlx_destroy_window(p->mlx, p->win);
        exit(0);
    }
    else if (key == 6) // 'z' key to zoom in
    {
        p->zoom *= ZOOM_SPEED; // add zoom
        p->move *= ZOOM_SPEED; // increase move speed (move speed is proportional to zoom level)
        printf("offsetX: %f\n", p->offsetX);
        printf("offsetY: %f\n", p->offsetY);
    }
    else if (key == 7) // 'x' key to zoom out
    {
        p->zoom /= ZOOM_SPEED;
        p->move /= ZOOM_SPEED;
        printf("offsetX: %f\n", p->offsetX);
        printf("offsetY: %f\n", p->offsetY);
    }
    else if (key == 123) // Left arrow key to move left
        p->offsetX -= p->move * 5;
    else if (key == 124) // Right arrow key to move right
        p->offsetX += p->move * 5;
    else if (key == 125) // Down arrow key to move down
        p->offsetY += p->move * 5;
    else if (key == 126) // Up arrow key to move up
        p->offsetY -= p->move * 5;

    mlx_clear_window(p->mlx, p->win);
    draw_mandelbrot(p->mlx, p->win, p->zoom, p->offsetX, p->offsetY);
    return 0;
}

int handle_mouse(int button, int x, int y, void *param)
{
    t_params *p = param;
    double zoom_factor = 1.1; // Zoom factor

    if (button == 4)  // Scroll up to zoom in
    {
        p->zoom *= zoom_factor;
        p->offsetX = p->offsetX * zoom_factor + (WIDTH / 2.0) * (1 - zoom_factor);
        p->offsetY = p->offsetY * zoom_factor + (HEIGHT / 2.0) * (1 - zoom_factor);
    }
    else if (button == 5)  // Scroll down to zoom out
    {
        zoom_factor = 1 / zoom_factor;
        p->zoom *= zoom_factor;
        p->offsetX = p->offsetX * zoom_factor + (WIDTH / 2.0) * (1 - zoom_factor);
        p->offsetY = p->offsetY * zoom_factor + (HEIGHT / 2.0) * (1 - zoom_factor);
    }

    mlx_clear_window(p->mlx, p->win);
    draw_mandelbrot(p->mlx, p->win, p->zoom, p->offsetX, p->offsetY);
    return 0;
}

int main()
{
	void *mlx = mlx_init();
	void *win = mlx_new_window(mlx, HEIGHT, WIDTH, "Drawing Board");
    t_params params;

    params.mlx = mlx;
    params.win = win;
    params.zoom = 1.0;
    params.move = 1.0;
    params.offsetX = 0.0;
    params.offsetY = 0.0;

	mlx_key_hook(win, handle_key, &params);
    mlx_mouse_hook(win, handle_mouse, &params);  // Set up mouse hook
	draw_mandelbrot(mlx, win, params.zoom, params.offsetX, params.offsetY);

	mlx_loop(mlx);

	return (0);
}


void draw_rectangle(void *mlx, void *win, int x, int y, int width, int height)
{
    int i = 0;
    int j;

    while (i < height) {
        j = 0;
        while (j < width) {
            mlx_pixel_put(mlx, win, x + j, y + i, rand() % 0x1000000);
            j++;
        }
        i++;
    }
}
void draw_triangle(void *mlx, void *win, int x, int y, int size)
{
    int i = 0;
    int j;

    while (i <= size) {
        j = 0;
        while (j <= i) {
            mlx_pixel_put(mlx, win, x - i / 2 + j, y + i, rand() % 0x1000000);
            j++;
        }
        i++;
    }
}
void draw_circle(void *mlx, void *win, int x, int y, int size)
{
	int i = 0;
	int j;

	while (i < size)
    {
		j = 0;
		while (j < size)
        {
			if ((i - size / 2) * (i - size / 2) + (j - size / 2) * (j - size / 2) <= size * size / 4)
				mlx_pixel_put(mlx, win, x - size / 2 + j, y - size / 2 + i, rand() % 0x1000000);
			j++;
		}
		i++;
	}
}
void draw_square(void *mlx, void *win, int x, int y, int size)
{
	int i = 0;
	int j;

	while (i < size) {
		j = 0;
		while (j < size) {
			mlx_pixel_put(mlx, win, x + j, y + i, rand() % 0x1000000);
			j++;
		}
		i++;
	}
}

// int main()
// {
// 	int		x = WIDTH / 2;
// 	int		y = HEIGHT / 2;
// 	int		size;

// 	// if (WIDTH < HEIGHT)
// 	// 	size = WIDTH * 0.1;
// 	// else
// 	// 	size = HEIGHT * 0.1;

//     size = WIDTH * 0.1;

// 	// i = WIDTH * 0.2;
// 	// j = HEIGHT * 0.2;
// 	srand(time(NULL));

// 	void *mlx = mlx_init();
// 	void *win = mlx_new_window(mlx, HEIGHT, WIDTH, "Drawing Board");

//     //draw_square(mlx, win, x - size / 2, y - size / 2, size);
// 	draw_triangle(mlx, win, WIDTH * 0.5, HEIGHT * 0.4 , size);
// 	//draw_circle(mlx, win, WIDTH *
