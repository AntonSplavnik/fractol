#include <stdlib.h>
#include <stdio.h>
#include "./minilibx/mlx.h"
#include "fractol.h"

#define HEIGHT 500
#define WIDTH 500
#define ZOOM_SPEED 1.5

typedef struct s_params {
    void *mlx;
    void *win;
    void *img;
    char *img_data;
    int bpp;
    int size_line;
    int endian;
    double zoom;
    double move;
    double offsetX;
    double offsetY;
    double minX;
    double maxX;
    double minY;
    double maxY;
} t_params;

void put_pixel_to_image(t_params *p, int x, int y, int color)
{
    int index = (y * p->size_line) + (x * (p->bpp / 8));
    p->img_data[index] = color;
    p->img_data[index + 1] = color >> 8;
    p->img_data[index + 2] = color >> 16;
}

void draw_mandelbrot(t_params *p)
{
    int x, y;
    double a, b, c, d, n;
    int max_iter = 100;
    int color;

    for (x = 0; x < WIDTH; x++)
    {
        for (y = 0; y < HEIGHT; y++)
        {
            a = b = c = d = n = 0;
            double realPart = (p->minX + x) * ((p->maxX - p->minX) / WIDTH) / 2 - 1;
            double imagPart = (p->minY + y) * ((p->maxY - p->minY) / HEIGHT) / 2 - 1;

            while (n < max_iter)
            {
                c = a * a - b * b + realPart;
                d = 2 * a * b + imagPart;
                a = c;
                b = d;
                if (a * a + b * b > 4) break;
                n++;
            }

            if (n == max_iter)
                color = 0x000000; // Black for points inside the set
            else
            {
                int r = (int)(n * 255 / max_iter);
                int g = (int)(n * 255 / max_iter);
                int b = (int)(n * 255 / max_iter);
                color = (r << 16) | (g << 8) | b;
            }

            put_pixel_to_image(p, x, y, color);
        }
    }
    mlx_put_image_to_window(p->mlx, p->win, p->img, 0, 0);
}

int handle_key(int key, void *param)
{
    t_params *p = param;

    if (key == 53)  // 'ESC' key to exit
    {
        mlx_destroy_window(p->mlx, p->win);
        exit(0);
    }
    else if (key == 6) // 'z' key to zoom in
    {
        p->zoom *= ZOOM_SPEED;
        double centerX = (p->minX + p->maxX) / 2;
        double centerY = (p->minY + p->maxY) / 2;
        double rangeX = (p->maxX - p->minX) / ZOOM_SPEED;
        double rangeY = (p->maxY - p->minY) / ZOOM_SPEED;
        p->minX = centerX - rangeX / 2;
        p->maxX = centerX + rangeX / 2;
        p->minY = centerY - rangeY / 2;
        p->maxY = centerY + rangeY / 2;
    }
    else if (key == 7) // 'x' key to zoom out
    {
        p->zoom /= ZOOM_SPEED;
        double centerX = (p->minX + p->maxX) / 2;
        double centerY = (p->minY + p->maxY) / 2;
        double rangeX = (p->maxX - p->minX) * ZOOM_SPEED;
        double rangeY = (p->maxY - p->minY) * ZOOM_SPEED;
        p->minX = centerX - rangeX / 2;
        p->maxX = centerX + rangeX / 2;
        p->minY = centerY - rangeY / 2;
        p->maxY = centerY + rangeY / 2;
    }
    else if (key == 123) // Left arrow key to move left
    {
        double moveX = (p->maxX - p->minX) * 3;
        p->minX -= moveX;
        p->maxX -= moveX;
    }
    else if (key == 124) // Right arrow key to move right
    {
        double moveX = (p->maxX - p->minX) * 3;
        p->minX += moveX;
        p->maxX += moveX;
    }
    else if (key == 125) // Down arrow key to move down
    {
        double moveY = (p->maxY - p->minY) * 3;
        p->minY += moveY;
        p->maxY += moveY;
    }
    else if (key == 126) // Up arrow key to move up
    {
        double moveY = (p->maxY - p->minY) * 3;
        p->minY -= moveY;
        p->maxY -= moveY;
    }

    draw_mandelbrot(p);
    return 0;
}

int handle_mouse(int button, int x, int y, void *param)
{
    t_params *p = param;
    double zoom_factor = 5.1; // Zoom factor

    if (button == 4)  // Scroll up to zoom in
    {
        p->zoom *= zoom_factor;
        double centerX = (p->minX + p->maxX) / 2;
        double centerY = (p->minY + p->maxY) / 2;
        double rangeX = (p->maxX - p->minX) / zoom_factor;
        double rangeY = (p->maxY - p->minY) / zoom_factor;
        p->minX = centerX - rangeX / 2;
        p->maxX = centerX + rangeX / 2;
        p->minY = centerY - rangeY / 2;
        p->maxY = centerY + rangeY / 2;
    }
    else if (button == 5)  // Scroll down to zoom out
    {
        p->zoom /= zoom_factor;
        double centerX = (p->minX + p->maxX) / 2;
        double centerY = (p->minY + p->maxY) / 2;
        double rangeX = (p->maxX - p->minX) * zoom_factor;
        double rangeY = (p->maxY - p->minY) * zoom_factor;
        p->minX = centerX - rangeX / 2;
        p->maxX = centerX + rangeX / 2;
        p->minY = centerY - rangeY / 2;
        p->maxY = centerY + rangeY / 2;
    }

    draw_mandelbrot(p);
    return 0;
}

int main()
{
    void *mlx = mlx_init();
    void *win = mlx_new_window(mlx, WIDTH, HEIGHT, "Mandelbrot");
    t_params params;

    params.mlx = mlx;
    params.win = win;
    params.zoom = 1.0;
    params.move = 1.0;
    params.offsetX = 0.0;
    params.offsetY = 0.0;
    params.minX = -2.0;
    params.maxX = 2.0;
    params.minY = -2.0;
    params.maxY = 2.0;
    params.img = mlx_new_image(mlx, WIDTH, HEIGHT);
    params.img_data = mlx_get_data_addr(params.img, &params.bpp, &params.size_line, &params.endian);

    mlx_key_hook(win, handle_key, &params);
    mlx_mouse_hook(win, handle_mouse, &params);
    draw_mandelbrot(&params);

    mlx_loop(mlx);

    return 0;
}
