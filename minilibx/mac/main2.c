#include <stdlib.h>
#include <time.h>
#include "./minilibx/mlx.h"
#define HEIGHT 500
#define WIDTH 500

void draw_mandelbrot(void *mlx, void *win, double zoom, double offsetX, double offsetY)
{
    int x, y;
    for (x = 0; x < WIDTH; x++)
    {
        for (y = 0; y < HEIGHT; y++)
        {
            double a = 0.0, b = 0.0, c, d, n = 0;
            while (n < 20)
            {
                c = a * a - b * b + (x - WIDTH / 2.0 + offsetX) * 4.0 / (WIDTH * zoom);
                d = 2 * a * b + (y - HEIGHT / 2.0 + offsetY) * 4.0 / (HEIGHT * zoom);
                a = c;
                b = d;
                if (a * a + b * b > 4) break;
                n++;
            }
            int color;
            if (n < 256)
                color = ((int)n) << 16;  // Red
            else if (n < 512)
                color = ((int)(n - 256)) << 8;  // Green
            else
                color = (int)(n - 512);  // Blue

            mlx_pixel_put(mlx, win, x, y, color);
        }
    }
}

int handle_mouse(int button, int x, int y, void *param) {
    if (!param)
        return -1;
	double zoom_factor_in = 1.1;
    double zoom_factor_out = 0.9;
    struct {
        void *mlx;
        void *win;
        double zoom;
        double offsetX;
        double offsetY;
    } *p = param;

    if (button == 4) {  // Scroll up to zoom in
        p->zoom *= zoom_factor_in;
        p->offsetX -= (x - WIDTH / 2.0) / (WIDTH * p->zoom);
        p->offsetY -= (y - HEIGHT / 2.0) / (HEIGHT * p->zoom);
    } else if (button == 5) {  // Scroll down to zoom out
        p->zoom *= zoom_factor_out;
        p->offsetX += (x - WIDTH / 2.0) / (WIDTH * p->zoom);
        p->offsetY += (y - HEIGHT / 2.0) / (HEIGHT * p->zoom);
    }

    draw_mandelbrot(p->mlx, p->win, p->zoom, p->offsetX, p->offsetY);
    return 0;
}

int main()
{

    void *mlx = mlx_init();
    if (!mlx)
        return -1;

	void *win = mlx_new_window(mlx, HEIGHT, WIDTH, "Drawing Board");

    struct
    {
        void *mlx;
        void *win;
        double zoom;
        double offsetX;
        double offsetY;
    } params = {mlx, win, 0.005, -0.6, 0.0};

	draw_mandelbrot(params.mlx, params.win, params.zoom, params.offsetX, params.offsetY);
	mlx_hook(win, 17, 1L<<17, handle_mouse, &params);
    mlx_loop(mlx);

    return (0);
}
