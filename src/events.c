/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmelara- <cmelara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 21:24:04 by cmelara-          #+#    #+#             */
/*   Updated: 2019/01/28 21:42:54 by cmelara-         ###   ########.fr       */
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
	while (SDL_PollEvent(e))
	{
		if (e->type == SDL_QUIT)
			engine->quit = 1;
		if (e->type == SDL_KEYUP && e->key.keysym.sym == SDLK_ESCAPE)
			engine->quit = 1;
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_w)
			move_towards(engine, 1);
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_s)
			move_towards(engine, -1);
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_d)
			move_side(engine, 1);
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_a)
			move_side(engine, -1);
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
