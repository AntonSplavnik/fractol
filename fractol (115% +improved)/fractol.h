/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:10:14 by asplavni          #+#    #+#             */
/*   Updated: 2024/10/15 15:35:06 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <pthread.h>
# include <ctype.h>
# include "minilibx-linux/mlx.h"

# define WIDTH	800
# define HEIGHT	800

# define BLACK       0x000000  // RGB(0, 0, 0)
# define WHITE       0xFFFFFF  // RGB(255, 255, 255)
# define RED         0xFF0000  // RGB(255, 0, 0)
# define GREEN       0x00FF00  // RGB(0, 255, 0)
# define BLUE        0x0000FF  // RGB(0, 0, 255)

# define MAGENTA_BURST   0xFF00FF
# define LIME_SHOCK      0xCCFF00
# define NEON_ORANGE     0xFF6600
# define PSYCHEDELIC_PURPLE 0x660066
# define AQUA_DREAM      0x33CCCC
# define HOT_PINK        0xFF66B2
# define ELECTRIC_BLUE   0x0066FF
# define LAVA_RED        0xFF3300

typedef struct s_bounds
{
	double	new_min;
	double	new_max;
	double	old_min;
	double	old_max;
}	t_bounds;

typedef struct s_complex
{
	double	x;
	double	y;
}				t_complex;

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}				t_img;

typedef struct s_fractal
{
	char	*name;
	void	*mlx_connection;
	void	*mlx_window;
	t_img	img;

	double	escape_value;
	int		iterations_defintion;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
}				t_fractal;

typedef struct s_thread_data
{
	int			start_row;
	int			end_row;
	t_fractal	*fractal;
}	t_thread_data;

//events
int			close_handler(t_fractal *fractal);
int			key_handler(int keysym, t_fractal *fractal);
int			mouse_handler(int button, int x, int y, t_fractal *fractal);
int			julia_track(int x, int y, t_fractal *fractal);

//handle_pixel
void		handle_pixel(int x, int y, t_fractal *fractal);

//init
void		fractal_init(t_fractal *fractal);

//math utils
double		map(double unscaled_num, t_bounds bounds);
int			is_valid_double(const char *str);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);

//render_fractal_progressive
void		fractal_render_progressive(t_fractal *fractal);

//render
void		pixel_put(int x, int y, t_img *img, int color);
void		fractal_render(t_fractal *fractal);
void		render_pixel_row(int y, t_fractal *fractal);
void		draw_image_to_window(t_fractal *fractal);
void		mandelbrot_vs_julia(t_complex *complex_z,
				t_complex *complex_c, t_fractal *fractal);

//string utils
int			ft_strncmp(char *s1, char *s2, int n);
double		string_to_double(char *str);
void		write_string_to_file_descriptor(char *str, int file_descriptor);

//thread_render
void		*thread_render(void *arg);

#endif
