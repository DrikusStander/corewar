# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/29 11:02:17 by gvan-roo          #+#    #+#              #
#    Updated: 2017/08/23 17:08:45 by gvan-roo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	asm

PATH_HEAD	=	./headers/
PATH_LIB	=	./libft/
PATH_SRC	=	./src/
PATH_OSC	=	./orc/

HEADERS		=	asm.h

SRC			=	$(PATH_SRC)asm_main.c\
				$(PATH_SRC)check.c\
				$(PATH_SRC)list.c\
				$(PATH_SRC)extras.c\
				$(PATH_SRC)parse_line.c\
				$(PATH_SRC)free.c\
				$(PATH_SRC)label_offset.c\
				$(PATH_SRC)name_comment.c\
				$(PATH_SRC)init.c\
				$(PATH_SRC)test.c\
				$(PATH_SRC)op.c\
				$(PATH_SRC)st.c\
				$(PATH_SRC)and.c\
				$(PATH_SRC)or.c\
				$(PATH_SRC)find_offset.c\
				$(PATH_SRC)ld.c\

OSC			=	asm_main.o\
				check.o\
				list.o\
				extras.o\
				parse_line.o\
				free.o\
				label_offset.o\
				name_comment.o\
				init.o\
				test.o\
				op.o\
				st.o\
				and.o\
				or.o\
				find_offset.o\
				ld.o

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
