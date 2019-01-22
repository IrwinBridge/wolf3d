/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmelara- <cmelara-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 17:46:30 by cmelara-          #+#    #+#             */
/*   Updated: 2019/01/22 22:38:24 by cmelara-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define WINDOW_WIDTH	640
# define WINDOW_HEIGHT	480

# include <math.h>
# include "../sdl/include/SDL.h"
# include "../libft/libft.h"

typedef struct	s_vec2
{
	double		x;
	double		y;
}				t_vec2;

typedef struct	s_line
{
	t_vec2		start;
	t_vec2		end;
	int			dx;
	int			dy;
	int			dirx;
	int			diry;
	int			err;
	int			err2;
	Uint32		color;
}				t_line;

typedef struct			s_engine
{
	SDL_Window			*window;
	SDL_Surface			*surface;
	int					quit;
}						t_engine;

void		render(t_engine *engine);

t_engine	*initialize(char *title);
void		init_engine(t_engine *engine);
int			free_engine(t_engine *engine);

void		put_pixel(t_engine *engine, int x, int y, Uint32 color);
void		clear_screen(t_engine *engine, Uint32 color);
void		update_screen(t_engine *engine);

void		game_loop(t_engine *engine);

void		draw_line(t_engine *engine, t_vec2 p1, t_vec2 p2, Uint32 color);

void		benchmark(t_engine *engine);

#endif
