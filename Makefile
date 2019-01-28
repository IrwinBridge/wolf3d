NAME = wolf3d
SRC = src/*.c
HEADERS = -Iincludes -Ilibft -I/usr/include/SDL2/
LINUX_LINKS = -L./libft -lft -lSDL2 -lSDL2_image -lm -lpthread
GFLAGS = -Wall -Wextra -Werror -Ofast

$(NAME):
	make -C libft
	gcc $(GFLAGS) $(SRC) $(HEADERS) $(LINUX_LINKS) -o $(NAME)
	make clean -C libft

all: $(NAME)

clean:
	/bin/rm -f libft/*.o

fclean: clean
	/bin/rm -f libft/libft.a
	/bin/rm -f $(NAME)

re: fclean all
