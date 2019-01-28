/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmelara- <cmelara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 20:20:39 by cmelara-          #+#    #+#             */
/*   Updated: 2019/01/28 20:22:06 by cmelara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	render_background(t_engine *engine)
{
	int x;
	int y;

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if (y < WINDOW_HEIGHT / 2)
				put_pixel(engine, x, y, 0xB1D9DF);
			else
				put_pixel(engine, x, y, 0x707070);
			x++;
		}
		y++;
	}
}

void	render_walls(t_engine *engine)
{
	int		x;
	t_col	column;
	t_ray	*ray;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ray = raycast(engine, engine->player, x);
		ray->wall_height = (int)(WINDOW_HEIGHT / ray->wall_dist);
		column.start = (int)(WINDOW_HEIGHT / 2 - ray->wall_height / 2);
		column.start = (column.start < 0) ? 0 : column.start;
		column.end = (int)(WINDOW_HEIGHT / 2 + ray->wall_height / 2);
		column.end = (column.end >= WINDOW_HEIGHT)
									? WINDOW_HEIGHT - 1 : column.end;
		draw_column(engine, x, column, ray);
		x++;
	}
}

void	render_hud(t_engine *engine)
{
	SDL_Rect rect;

	rect.w = 512;
	rect.h = 512;
	rect.x = (int)(WINDOW_WIDTH / 2) - rect.w / 2;
	rect.y = WINDOW_HEIGHT - rect.h;
	SDL_BlitScaled(engine->gun, NULL, engine->surface, &rect);
}

void	render(t_engine *engine)
{
	render_background(engine);
	render_walls(engine);
	render_hud(engine);
	update_screen(engine);
}
