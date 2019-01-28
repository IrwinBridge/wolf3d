/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmelara- <cmelara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 13:38:22 by cmelara-          #+#    #+#             */
/*   Updated: 2019/01/28 19:26:44 by cmelara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	set_ray(t_player *player, t_ray *ray, t_cast *cast, double cam)
{
	ray->x = player->dir_x + player->plane_x * cam;
	ray->y = player->dir_y + player->plane_y * cam;
	cast->mapx = (int)player->x;
	cast->mapy = (int)player->y;
	ray->dx = sqrt((ray->y * ray->y) / (ray->x * ray->x) + 1);
	ray->dy = sqrt((ray->x * ray->x) / (ray->y * ray->y) + 1);
	cast->nextx = (ray->x < 0) ? -1 : 1;
	cast->nexty = (ray->y < 0) ? -1 : 1;
	ray->sx = (ray->x < 0 ? player->x - cast->mapx
				: cast->mapx + 1.0f - player->x) * ray->dx;
	ray->sy = (ray->y < 0 ? player->y - cast->mapy
				: cast->mapy + 1.0f - player->y) * ray->dy;
}

int		hit(t_ray *ray, t_cast *cast)
{
	int passed_dist;

	passed_dist = 0;
	while (passed_dist < VIEW_MAX)
	{
		if (ray->sx < ray->sy)
		{
			ray->sx += ray->dx;
			cast->mapx += cast->nextx;
			cast->side = 0;
		}
		else
		{
			ray->sy += ray->dy;
			cast->mapy += cast->nexty;
			cast->side = 1;
		}
		if (cast->mapx < 0 || cast->mapx > ray->map->mapWidth
			|| cast->mapy < 0 || cast->mapx > ray->map->mapHeight)
			break ;
		if (ray->map->map[cast->mapx][cast->mapy] > 0)
			return (1);
		passed_dist++;
	}
	return (0);
}

t_ray	*raycast(t_engine *engine, t_player *player, int x)
{
	double	cam;
	t_ray	*ray;
	t_cast	cast;

	ray = ft_memalloc(sizeof(t_ray));
	ray->map = engine->map;
	cam = 2.0f * (double)x / (double)WINDOW_WIDTH - 1.0f;
	set_ray(player, ray, &cast, cam);
	if (hit(ray, &cast))
	{
		if (cast.side == 0)
			ray->wall_dist = (cast.mapx - player->x
							+ (double)(1.0f - cast.nextx) / 2.0f) / ray->x;
		else
			ray->wall_dist = (cast.mapy - player->y
							+ (double)(1.0f - cast.nexty) / 2.0f) / ray->y;
		ray->wall_id = engine->map->map[cast.mapx][cast.mapy];
		ray->wall_x = (!cast.side) ? player->y + ray->wall_dist * ray->y
							: player->x + ray->wall_dist * ray->x;
		ray->wall_x -= floor(ray->wall_x);
		ray->tex_x = (int)(ray->wall_x * (double)TEX_W);
		if ((!cast.side && ray->x > 0) || (cast.side == 1 && ray->y < 0))
			ray->tex_x = TEX_W - ray->tex_x - 1;
		ray->cast = cast;
		return (ray);
	}
	ray->wall_dist = 2.0f;
	ray->cast = cast;
	return (ray);
}
