/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmelara- <cmelara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 21:24:04 by cmelara-          #+#    #+#             */
/*   Updated: 2019/01/28 20:56:51 by cmelara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	turn_player(t_player *player, double angle)
{
	double tmp_dir;
	double tmp_plane;
	double c;
	double s;

	c = cos(angle);
	s = sin(angle);
	tmp_dir = player->dir_x;
	tmp_plane = player->plane_x;
	player->dir_x = tmp_dir * c - player->dir_y * s;
	player->dir_y = tmp_dir * s + player->dir_y * c;
	player->plane_x = tmp_plane * c - player->plane_y * s;
	player->plane_y = tmp_plane * s + player->plane_y * c;
}

void	mouse_move(t_engine *engine, SDL_Event *e)
{
	double deltax;

	engine->mouse->prev_x = engine->mouse->x;
	engine->mouse->x = e->motion.x;
	deltax = (engine->mouse->prev_x - engine->mouse->x) * engine->frameTime;
	turn_player(engine->player, deltax);
}

void	handle_events(t_engine *engine, SDL_Event *e)
{
	int		mapx;
	int		mapy;
	double	mspd;

	mspd = engine->frameTime * 10.0f;
	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_QUIT)
			engine->quit = 1;
		if (e->type == SDL_KEYUP && e->key.keysym.sym == SDLK_ESCAPE)
			engine->quit = 1;
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_w)
		{
			mapx = (int)(engine->player->x + engine->player->dir_x * mspd);
			mapy = (int)(engine->player->y + engine->player->dir_y * mspd);
			if (!engine->map->map[mapx][(int)engine->player->y])
				engine->player->x += engine->player->dir_x * mspd;
			if (!engine->map->map[(int)engine->player->x][mapy])
				engine->player->y += engine->player->dir_y * mspd;
		}
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_s)
		{
			mapx = (int)(engine->player->x - engine->player->dir_x * mspd);
			mapy = (int)(engine->player->y - engine->player->dir_y * mspd);
			if (!engine->map->map[mapx][(int)engine->player->y])
				engine->player->x -= engine->player->dir_x * mspd;
			if (!engine->map->map[(int)engine->player->x][mapy])
				engine->player->y -= engine->player->dir_y * mspd;
		}
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_d)
		{
			mapx = (int)(engine->player->x + engine->player->plane_x * mspd);
			mapy = (int)(engine->player->y + engine->player->plane_y * mspd);
			if (!engine->map->map[mapx][(int)engine->player->y])
				engine->player->x += engine->player->plane_x * mspd;
			if (!engine->map->map[(int)engine->player->x][mapy])
				engine->player->y += engine->player->plane_y * mspd;
		}
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_a)
		{
			mapx = (int)(engine->player->x - engine->player->plane_x * mspd);
			mapy = (int)(engine->player->y - engine->player->plane_y * mspd);
			if (!engine->map->map[mapx][(int)engine->player->y])
				engine->player->x -= engine->player->plane_x * mspd;
			if (!engine->map->map[(int)engine->player->x][mapy])
				engine->player->y -= engine->player->plane_y * mspd;
		}
		if (e->type == SDL_MOUSEMOTION)
			mouse_move(engine, e);
	}
}

void	fps_count(t_engine *engine, double *time, double *oldTime, double *ft)
{
	*oldTime = *time;
	*time = SDL_GetTicks();
	*ft = (*time - *oldTime) / 1000.0f;
	engine->frameTime = *ft;
	//printf("FPS: %f\n", 1.0f / *ft);
}

void	game_loop(t_engine *engine)
{
	SDL_Event	e;
	double		time;
	double		oldTime;
	double		frameTime;

	time = 0;
	oldTime = 0;
	while (!engine->quit)
	{
		fps_count(engine, &time, &oldTime, &frameTime);
		render(engine);
		handle_events(engine, &e);
	}
}
