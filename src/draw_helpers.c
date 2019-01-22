/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmelara- <cmelara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 21:46:59 by cmelara-          #+#    #+#             */
/*   Updated: 2019/01/22 21:54:15 by cmelara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	rasterize(t_engine *engine, t_line *line, t_vec2 *p1, t_vec2 *p2)
{
	while (1)
	{
		put_pixel(engine, p1->x, p1->y, line->color);
		if (p1->x == p2->x && p1->y == p2->y)
			break ;
		line->err2 = 2 * line->err;
		if (line->err2 >= line->dy)
		{
			line->err += line->dy;
			p1->x += line->dirx;
		}
		if (line->err2 <= line->dx)
		{
			line->err += line->dx;
			p1->y += line->diry;
		}
	}
}

void	draw_line(t_engine *engine, t_vec2 p1, t_vec2 p2, Uint32 color)
{
	t_line line;

	line.start = p1;
	line.end = p2;
	line.dx = abs(p2.x - p1.x);
	line.dy = -abs(p2.y - p1.y);
	line.dirx = p1.x < p2.x ? 1 : -1;
	line.diry = p1.y < p2.y ? 1 : -1;
	line.err = line.dx + line.dy;
	line.color = color;
	rasterize(engine, &line, &p1, &p2);
}
