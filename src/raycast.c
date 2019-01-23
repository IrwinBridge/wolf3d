/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmelara- <cmelara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 13:38:22 by cmelara-          #+#    #+#             */
/*   Updated: 2019/01/23 21:47:33 by cmelara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

int map[MAP_WIDTH][MAP_HEIGHT] =
{
  {1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,2,2,0,0,0,1},
  {1,0,0,0,2,2,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1}
};

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
		if (cast->mapx < 0 || cast->mapx > MAP_WIDTH || cast->mapy < 0
			|| cast->mapx > MAP_HEIGHT)
			break ;
		if (map[cast->mapx][cast->mapy] > 0)
			return (1);
		passed_dist++;
	}
	return (0);
}

double	raycast(t_engine *engine, t_player *player, int x, Uint32 *color)
{
	double	cam;
	t_ray	ray;
	t_cast	cast;

	cam = 2.0f * (double)x / (double)WINDOW_WIDTH - 1.0f;
	set_ray(player, &ray, &cast, cam);
	if (hit(&ray, &cast))
	{
		if (cast.side == 0)
			ray.wall_dist = (cast.mapx - player->x
							+ (double)(1.0f - cast.nextx) / 2.0f) / ray.x;
		else
			ray.wall_dist = (cast.mapy - player->y
							+ (double)(1.0f - cast.nexty) / 2.0f) / ray.y;
		set_map_color(engine, color, map[cast.mapx][cast.mapy]);
		*color = (cast.side == 1) ? *color / 2 : *color;
		return (ray.wall_dist);
	}
	return (2.0f);
}
