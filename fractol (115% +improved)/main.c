/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 13:16:31 by asplavni          #+#    #+#             */
/*   Updated: 2024/10/15 15:34:20 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	parse_julia_params(t_fractal *fractal, int ac, char **av)
{
	if (ac != 4)
	{
		write_string_to_file_descriptor
		("Error: Julia requires exactly two parameters.\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (!is_valid_double(av[2]) || !is_valid_double(av[3]))
	{
		write_string_to_file_descriptor
		("Error: Julia parameters must be valid numbers.\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	fractal->julia_x = string_to_double(av[2]);
	fractal->julia_y = string_to_double(av[3]);
}

void	start_fractal(t_fractal *fractal, char *name, int ac, char **av)
{
	fractal->name = name;
	if (!ft_strncmp(fractal->name, "julia", 5))
		parse_julia_params(fractal, ac, av);
	fractal_init(fractal);
	fractal_render(fractal);
	mlx_loop(fractal->mlx_connection);
}

void	print_usage_and_exit(void)
{
	write_string_to_file_descriptor("\n\t  Please enter:"
		"\n\t./fractol mandelbrot"
		"\n\t./fractol julia <value1> <value2>\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_fractal	fractal;

	if ((ac == 2 && !ft_strncmp(av[1], "mandelbrot", 10))
		|| (ac == 4 && !ft_strncmp(av[1], "julia", 5)))
		start_fractal(&fractal, av[1], ac, av);
	else
		print_usage_and_exit();
	return (0);
}
