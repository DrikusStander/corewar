# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/29 11:02:17 by gvan-roo          #+#    #+#              #
#    Updated: 2017/08/13 11:13:05 by gvan-roo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	asm

PATH_HEAD	=	./headers/
PATH_LIB	=	./libft/
PATH_SRC	=	./src/
PATH_OSC	=	./orc/

HEADERS		=	asm.h

SRC			=	$(PATH_SRC)asm_main.c

OSC			=	asm_main.o		\

FLAGS		=	-Wall -Werror -Wextra

all	:	$(NAME)

$(NAME)	:	$(OSRC)
	make -C $(PATH_LIB) fclean && make -C $(PATH_LIB)
	gcc $(FLAGS) -I $(PATH_HEAD)$(HEADERS) -c $(SRC)
	gcc -o $(NAME) $(OSC) -L$(PATH_LIB) -lft -ltermcap

$(OSRC) :
	
clean	:
	rm -f $(OSC)
	make -C $(PATH_LIB) clean

fclean	:	clean
	rm -f $(NAME)
	make -C $(PATH_LIB) fclean

re	:	fclean
	make
