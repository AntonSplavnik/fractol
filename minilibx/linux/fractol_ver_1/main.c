#include <mlx.h>
#include <stdlib.h>
#include <math.h>
#include "fractals.h"

#define WIDTH 900
#define HEIGHT 800

void draw_fractal(t_mlx *mlx)
{
    int x, y;
    t_complex c;
    int color;
    int iteration;

    mlx->fractal.factor.real = (mlx->fractal.max.real - mlx->fractal.min.real) / (WIDTH - 1);
    mlx->fractal.factor.imag = (mlx->fractal.max.imag - mlx->fractal.min.imag) / (HEIGHT - 1);

    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            c.real = mlx->fractal.min.real + x * mlx->fractal.factor.real;
            c.imag = mlx->fractal.min.imag + y * mlx->fractal.factor.imag;
            iteration = mlx->fractal.fractal_func(c, mlx->fractal.max_iterations);
            color = iteration * 0xFFFFFF / mlx->fractal.max_iterations;
            *(int *)(mlx->img_data + ((x + y * WIDTH) * mlx->bpp / 8)) = color;
        }
    }
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}

int key_hook(int keycode, t_mlx *mlx)
{
    double zoom_factor = 0.9;
    double move_factor = 0.1;
    t_complex center;

    center.real = (mlx->fractal.min.real + mlx->fractal.max.real) / 2;
    center.imag = (mlx->fractal.min.imag + mlx->fractal.max.imag) / 2;

    if (keycode == 65307) // Escape key
        exit(0);
    else if (keycode == 65361) // Left arrow
    {
        mlx->fractal.min.real -= move_factor * (mlx->fractal.max.real - mlx->fractal.min.real);
        mlx->fractal.max.real -= move_factor * (mlx->fractal.max.real - mlx->fractal.min.real);
    }
    else if (keycode == 65363) // Right arrow
    {
        mlx->fractal.min.real += move_factor * (mlx->fractal.max.real - mlx->fractal.min.real);
        mlx->fractal.max.real += move_factor * (mlx->fractal.max.real - mlx->fractal.min.real);
    }
    else if (keycode == 65364) // Down arrow
    {
        mlx->fractal.min.imag += move_factor * (mlx->fractal.max.imag - mlx->fractal.min.imag);
        mlx->fractal.max.imag += move_factor * (mlx->fractal.max.imag - mlx->fractal.min.imag);
    }
    else if (keycode == 65362) // Up arrow
    {
        mlx->fractal.min.imag -= move_factor * (mlx->fractal.max.imag - mlx->fractal.min.imag);
        mlx->fractal.max.imag -= move_factor * (mlx->fractal.max.imag - mlx->fractal.min.imag);
    }
    else if (keycode == 122) // 'z' key for zoom in
    {
        mlx->fractal.min.real = center.real + (mlx->fractal.min.real - center.real) * zoom_factor;
        mlx->fractal.min.imag = center.imag + (mlx->fractal.min.imag - center.imag) * zoom_factor;
        mlx->fractal.max.real = center.real + (mlx->fractal.max.real - center.real) * zoom_factor;
        mlx->fractal.max.imag = center.imag + (mlx->fractal.max.imag - center.imag) * zoom_factor;
    }
    else if (keycode == 120) // 'x' key for zoom out
    {
        mlx->fractal.min.real = center.real + (mlx->fractal.min.real - center.real) / zoom_factor;
        mlx->fractal.min.imag = center.imag + (mlx->fractal.min.imag - center.imag) / zoom_factor;
        mlx->fractal.max.real = center.real + (mlx->fractal.max.real - center.real) / zoom_factor;
        mlx->fractal.max.imag = center.imag + (mlx->fractal.max.imag - center.imag) / zoom_factor;
    }

    draw_fractal(mlx);
    return (0);
}

int main(void)
{
    t_mlx mlx;

    // Initialize MLX
    mlx.mlx_ptr = mlx_init();
    mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGHT, "Mandelbrot");
    mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, WIDTH, HEIGHT);
    mlx.img_data = mlx_get_data_addr(mlx.img_ptr, &mlx.bpp, &mlx.size_line, &mlx.endian);


    // Initialize fractal parameters
    mlx.fractal.min = (t_complex){-2.0, -1.5};
    mlx.fractal.max = (t_complex){1.0, 1.5};
    mlx.fractal.max_iterations = 100;
    mlx.fractal.fractal_func = mandelbrot;
    mlx.width = WIDTH;
    mlx.height = HEIGHT;

    // Draw the initial fractal
    draw_fractal(&mlx);
    
    // Setup event hooks
    mlx_key_hook(mlx.win_ptr, key_hook, &mlx);
    
    // Enter the MLX event loop
    mlx_loop(mlx.mlx_ptr);

    return (0);
}
