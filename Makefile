NAME = wolf3d
SRC = src/*.c
HEADERS = -Iincludes
LIBLINK = -L./libft -lft
SDLLINK = -L./sdl/build -lSDL2
MLINK = -lm
PTHREADS = -lpthread
GFLAGS = -Wall -Wextra -Werror -Ofast

$(NAME):
	make -C libft
	make -C sdl
	gcc $(GFLAGS) $(SRC) $(HEADERS) $(LIBLINK) $(SDLLINK) $(MLINK) -o $(NAME)

all: $(NAME)

clean:
	/bin/rm -f libft/*.o

fclean: clean
	/bin/rm -f libft/libft.a
	/bin/rm -f sdl/SDL2.a
	/bin/rm -f $(NAME)

re: fclean all
