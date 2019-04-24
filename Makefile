# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ydonse <ydonse@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/23 10:03:18 by ydonse            #+#    #+#              #
#    Updated: 2019/04/24 13:06:18 by ydonse           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

SRC_PATH = src

SRC_NAME = main.c parsing.c errors.c walls_checking.c

CPPFLAGS = -I libft/includes/ -I /usr/local/include/ -MMD

LDFLAGS = -L libft/ -lft  -L /usr/local/include/ -lpthread

LDLIBS = -framework OpenGL -framework AppKit

CC = gcc

CFLAGS = -g -Wall -Wextra #-Werror

OBJ_NAME = $(SRC_NAME:.c=.o)

OBJ_PATH = obj

HEADER_PATH = includes/
HEADER_NAME = wolf3d.h

ID = $(shell id -un)
SDLFLAGS =  $(SDLINCL) -L/Users/$(ID)/.brew/Cellar/sdl2/2.0.9_1/lib -lSDL2
SDLINCL = -I /Users/$(ID)/.brew/Cellar/sdl2/2.0.9_1/include

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))

HEADER = $(addprefix $(HEADER_PATH)/,$(HEADER_NAME))

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft/
	$(CC) $(CFLAGS) $(LDFLAGS) $(SDLFLAGS) $(LDLIBS) $^ -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) -I $(HEADER_PATH) $(SDLINCL) -o $@ -c $<

$(OBJ_PATH):
	@mkdir $(OBJ_PATH) 2> /dev/null || true

clean:
	make clean -C libft/
	rm -f $(OBJ) $(OBJ:.o=.d)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean: clean
	make fclean -C libft/
	rm -f $(NAME)

re: fclean
	$(MAKE) all

.PHONY: make clean fclean re

-include $(OBJ:.o=.d)
