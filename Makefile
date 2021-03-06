# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dbolilyi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/16 16:42:45 by dbolilyi          #+#    #+#              #
#    Updated: 2018/08/03 15:15:55 by dbolilyi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem

SRC = main.c

OBJ = $(SRC:.c=.o)

INC =	-I SDL2/SDL2.framework/Headers\
		-I SDL2/SDL2_image.framework/Headers\
		-I SDL2/SDL2_ttf.framework/Headers

ERRFL = -Wall -Wextra

FL = -F SDL2/ -framework SDL2 -framework SDL2_image -framework SDL2_ttf

PRINT = yes

all: $(NAME)

$(OBJ): %.o: %.c
	@echo "\033[93mCompiling \033[0m$@"
	cc $(ERRFL) -c -o $@ $< $(INC)

$(NAME): $(OBJ)
	@echo "\033[93mCompiling libft\033[0m"
	@make -C ./libft
	@echo "\033[93mCompiling $(NAME)\033[0m"
	gcc $(ERRFL) $(FL) -o $@ $(OBJ) -L libft/ ./libft/libft.a 
	@echo "\033[92mDONE\033[0m"
	

clean:
	@echo "\033[91mDeleting libft objects\033[0m"
	@make -C libft/ clean
	@echo "\033[91mDeleting $(NAME) objects\033[0m"
	@rm -f $(OBJ)

fclean: clean
	@echo "\033[91mDeleting libft.a\033[0m"
	@make -C libft/ fclean
	@echo "\033[91mDeleting $(NAME)\033[0m"
	@rm -f $(NAME)

re: fclean \
	all

.PHONY: all clean fclean re libft1

.NOTPARALLEL: all clean fclean re libft1
