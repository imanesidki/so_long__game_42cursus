NAME := so_long

BONUS_NAME := so_long_bonus

SRCS := $(shell find ./src ./lib/getnextline -iname "*.c")

BONUS_SRCS := $(shell find ./src_bonus ./lib/getnextline -iname "*.c") $(shell find ./src -iname "*_commun.c")

OBJS := ${SRCS:.c=.o}

BONUS_OBJS := ${BONUS_SRCS:.c=.o}

CFLAGS =	-Wall -Werror -Wextra -Wunreachable-code -Ofast -DDEBUG=1
MLX_FLAG =	-lmlx -framework OpenGL -framework AppKit

all : $(NAME)

bonus : $(BONUS_NAME)

%.o : %.c
	@cc $(CFLAGS) -o $@ -c $<

$(NAME) : $(OBJS)
	@cc $(OBJS) $(CFLAGS) $(MLX_FLAG) -o $(NAME)

$(BONUS_NAME) : $(BONUS_OBJS)
	@cc $(BONUS_OBJS) $(CFLAGS) $(MLX_FLAG) -o $(BONUS_NAME)

clean :
	@rm -rf $(OBJS) $(BONUS_OBJS)

fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(BONUS_NAME)

re : clean all

.PHONY: all, clean, fclean, re, bonus
