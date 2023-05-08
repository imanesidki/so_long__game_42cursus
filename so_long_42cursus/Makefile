NAME := so_long

SRCS := $(shell find ./src ./lib/getnextline -iname "*.c")

OBJS := ${SRCS:.c=.o}

CFLAGS =	-Wall -Werror -Wextra -Wunreachable-code -Ofast -DDEBUG=1
MLX_FLAG =	-lmlx -framework OpenGL -framework AppKit

all : $(NAME)

%.o : %.c
	@cc $(CFLAGS) -o $@ -c $<

$(NAME) : $(OBJS)
	@cc $(OBJS) $(CFLAGS) $(MLX_FLAG) -o $(NAME)

clean :
	@rm -rf $(OBJS)

fclean : clean
	@rm -rf $(NAME)

re : clean all

.PHONY: all, clean, fclean, re
