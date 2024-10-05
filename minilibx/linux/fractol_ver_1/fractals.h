#ifndef FRACTALS_H
#define FRACTALS_H

typedef struct s_complex
{
    double real;
    double imag;
}               t_complex;

typedef struct s_fractal
{
    int         max_iterations;
    t_complex   min;
    t_complex   max;
    t_complex   factor;
    int         (*fractal_func)(t_complex c, int max_iterations);
}               t_fractal;

typedef struct s_mlx
{
    void    *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    char    *img_data;
    int     bpp;
    int     size_line;
    int     endian;
    t_fractal fractal;
    int     width;
    int     height;
}               t_mlx;

int mandelbrot(t_complex c, int max_iterations);

#endif
