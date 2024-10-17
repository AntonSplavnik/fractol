/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asplavni <asplavni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:30:22 by asplavni          #+#    #+#             */
/*   Updated: 2024/10/15 14:00:18 by asplavni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	*thread_render(void *arg)
{
	t_thread_data	*data;
	int				y;

	data = (t_thread_data *)arg;
	y = data->start_row;
	while (y < data->end_row)
	{
		render_pixel_row(y, data->fractal);
		y++;
	}
	return (NULL);
}
