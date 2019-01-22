NAME = wolf3d
SRC = src/*.c
HEADERS = -Iincludes
LINUX_LINKS = -L./libft -lft -L./sdl/build -lSDL2 -lm -lpthread
GFLAGS = -Wall -Wextra -Werror -Ofast

$(NAME):
	make -C libft
	make -C sdl
	gcc $(GFLAGS) $(SRC) $(HEADERS) $(LINUX_LINKS) -o $(NAME)

all: $(NAME)

clean:
	/bin/rm -f libft/*.o

fclean: clean
	/bin/rm -f libft/libft.a
	/bin/rm -f $(NAME)

re: fclean all
