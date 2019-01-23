/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmelara- <cmelara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 13:38:22 by cmelara-          #+#    #+#             */
/*   Updated: 2019/01/23 19:06:10 by cmelara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

int worldMap[MAP_WIDTH][MAP_HEIGHT]=
{
  {1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1}
};

double	raycast(t_player *player, int x, Uint32 *color)
{
	double cam;
	double ray_x;
	double ray_y;
	//which cell of the map we're in
	int grid_x;
	int grid_y;
	//length of ray from current position to next x or y-side
	double side_dist_x;
	double side_dist_y;
	//length of ray from one x or y-side to next x or y-side
	double delta_x;
	double delta_y;
	double wall_dist;
	//what direction to step in x or y-direction (either +1 or -1)
	int step_x;
	int step_y;
	int hit;
	int side;

	cam = 2.0f * (double)x / (double)WINDOW_WIDTH - 1.0f;
	ray_x = player->dir_x + player->plane_x * cam;
	ray_y = player->dir_y + player->plane_y * cam;
	grid_x = (int)player->x;
	grid_y = (int)player->y;
	delta_x = abs(1 / ray_x);
	delta_y = abs(1 / ray_y);
	hit = 0;

	// initial step and side
	if (ray_x < 0)
	{
		step_x = -1;
		side_dist_x = (player->x - grid_x) * delta_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (grid_x + 1.0f - player->x) * delta_x;
	}
	if (ray_y < 0)
	{
		step_y = -1;
		side_dist_y = (player->y - grid_y) * delta_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (grid_y + 1.0f - player->y) * delta_y;
	}

	// DDA
	while (hit == 0)
	{
		// Jump the the next cell in a map
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_x;
			grid_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_y;
			grid_y += step_y;
			side = 1;
		}
		// Check if intersected
		if (worldMap[grid_x][grid_y] > 0)
			hit = 1;
	}

	// Calculating distance to camera plane
	if (side == 0)
		wall_dist = (grid_x - player->x + (double)(1.0f - step_x) / 2.0f) / ray_x;
	else
		wall_dist = (grid_y - player->y + (double)(1.0f - step_y) / 2.0f) / ray_y;

	switch(worldMap[grid_x][grid_y])
	{
		case 1:  *color = 0x99992D;  break; //red
		case 2:  *color = 0x00FF00;  break; //green
		case 3:  *color = 0x0000FF;  break; //blue
		case 4:  *color = 0xFFFFFF;  break; //white
		default: *color = 0x888800;  break; //yellow
	}
	return (wall_dist);
}
