# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/29 11:02:17 by gvan-roo          #+#    #+#              #
#    Updated: 2017/08/24 10:56:26 by hstander         ###   ########.fr        #
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
				$(PATH_SRC)xor.c\
				$(PATH_SRC)find_offset.c\
				$(PATH_SRC)ld.c\
				$(PATH_SRC)zjmp.c\
				$(PATH_SRC)ldi.c\
				$(PATH_SRC)sti.c\
				$(PATH_SRC)ft_fork.c\
				$(PATH_SRC)lld.c\
				$(PATH_SRC)lldi.c\
				$(PATH_SRC)lfork.c\
				$(PATH_SRC)add.c\
				$(PATH_SRC)sub.c\
				$(PATH_SRC)live.c\
				$(PATH_SRC)aff.c\

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
				xor.o\
				find_offset.o\
				ld.o\
				zjmp.o\
				ldi.o\
				sti.o\
				ft_fork.o\
				lld.o\
				lldi.o\
				lfork.o\
				add.o\
				sub.o\
				live.o\
				aff.o\

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
