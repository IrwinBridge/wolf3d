/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmelara- <cmelara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 21:24:04 by cmelara-          #+#    #+#             */
/*   Updated: 2019/01/23 18:30:05 by cmelara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	turn_left(t_player *player)
{
	double a;
	double old_dir_x;
	double old_plane_x;

	a = 0.05235f;
	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = old_dir_x * cos(a) - player->dir_y * sin(a);
	player->dir_y = old_dir_x * sin(a) + player->dir_y * cos(a);
	player->plane_x = old_plane_x * cos(a) - player->plane_y * sin(a);
	player->plane_y = old_plane_x * sin(a) + player->plane_y * cos(a);
}

void	turn_right(t_player *player)
{
	double a;
	double old_dir_x;
	double old_plane_x;

	a = -0.05235f;
	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = old_dir_x * cos(a) - player->dir_y * sin(a);
	player->dir_y = old_dir_x * sin(a) + player->dir_y * cos(a);
	player->plane_x = old_plane_x * cos(a) - player->plane_y * sin(a);
	player->plane_y = old_plane_x * sin(a) + player->plane_y * cos(a);
}

void	handle_events(t_engine *engine, SDL_Event e)
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			engine->quit = 1;
		if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
			engine->quit = 1;

		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_LEFT)
			turn_left(engine->player);
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RIGHT)
			turn_right(engine->player);

		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP)
		{
			engine->player->x += engine->player->dir_x * 0.2f;
			engine->player->y += engine->player->dir_y * 0.2f;
		}
		if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN)
		{
			engine->player->x -= engine->player->dir_x * 0.2f;
			engine->player->y -= engine->player->dir_y * 0.2f;
		}
	}
}

void	game_loop(t_engine *engine)
{
	SDL_Event e;

	while (!engine->quit)
	{
		handle_events(engine, e);
		benchmark(engine);
	}
}
