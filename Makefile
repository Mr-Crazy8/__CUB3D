CC = cc
CFLAGS = #-Wall -Wextra -Werror
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit
SRCS = parsing/ft_split.c  parsing/get_next_line.c  parsing/get_next_line_utils.c  parsing/parsing.c  parsing/parsing_floor_and_ceiling_color.c \
		parsing/parsing_map.c  parsing/parsing_texture.c   parsing/parsing_utiles.c 
OBJS = $(SRCS:.c=.o)

NAME = cub3D

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c parsing.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean