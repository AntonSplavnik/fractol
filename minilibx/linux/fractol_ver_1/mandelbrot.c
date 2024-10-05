#include "fractals.h"

int mandelbrot(t_complex c, int max_iterations)
{
    t_complex z;
    int       i;
    double    temp;

    z.real = 0;
    z.imag = 0;
    i = 0;
    while ((z.real * z.real + z.imag * z.imag <= 4.0) && (i < max_iterations))
    {
        temp = z.real * z.real - z.imag * z.imag + c.real;
        z.imag = 2 * z.real * z.imag + c.imag;
        z.real = temp;
        i++;
    }
    return (i);
}
