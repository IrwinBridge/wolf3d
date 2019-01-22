/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmelara- <cmelara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 20:20:39 by cmelara-          #+#    #+#             */
/*   Updated: 2019/01/22 22:22:33 by cmelara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		map[5][5] =
	{
		{1, 1, 1, 1, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 0, 0, 0, 1},
		{1, 1, 1, 1, 1}
	};

void	render(t_engine *engine)
{
	int x;
	int top_offset;
	int bottom_offset;
	t_vec2 p1;
	t_vec2 p2;

	clear_screen(engine, 0xFFFFFF);
	x = 0;
	top_offset = 20;
	bottom_offset = WINDOW_HEIGHT - 20;
	//color = SDL_MapRGBA(engine->surface->format, 255, 0, 0, 255);
	while (x < WINDOW_WIDTH)
	{
		p1.x = x;
		p2.x = x;
		p1.y = top_offset + (int)(x / 10.0f);
		p2.y = bottom_offset - (int)(x / 10.0f);
		draw_line(engine, p1, p2, 0xFF0000);
		x++;
	}
	update_screen(engine);
}
