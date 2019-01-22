/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmelara- <cmelara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 21:24:04 by cmelara-          #+#    #+#             */
/*   Updated: 2019/01/22 22:38:37 by cmelara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	handle_events(t_engine *engine, SDL_Event e)
{
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			engine->quit = 1;
		if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
			engine->quit = 1;
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
