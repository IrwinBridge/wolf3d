/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmelara- <cmelara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 21:46:59 by cmelara-          #+#    #+#             */
/*   Updated: 2019/01/28 21:02:15 by cmelara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_column(t_engine *engine, int x, t_col y_column, t_ray *ray)
{
	SDL_Rect	*tex_rect;
	SDL_Rect	win_rect;

	tex_rect = ft_memalloc(sizeof(SDL_Rect));
	tex_rect->w = 1;
	tex_rect->h = TEX_H;
	//printf("tex_x: %d\n", ray->tex_x);
	tex_rect->x =  TEX_W * (ray->wall_id - 1) + ray->tex_x;
	tex_rect->y = 0;//(int)((1.0f - (double)abs(y_column.end - y_column.start) / (double)ray->wall_height) * 64);

	win_rect.w = 1;
	win_rect.h = abs(y_column.end - y_column.start);
	win_rect.x = x;
	win_rect.y = y_column.start;
	SDL_BlitScaled(engine->map->texture, tex_rect, engine->surface, &win_rect);
}
