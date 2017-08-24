# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/29 11:02:17 by gvan-roo          #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2017/08/24 09:50:55 by gvan-roo         ###   ########.fr        #
=======
#    Updated: 2017/08/24 10:28:12 by hstander         ###   ########.fr        #
>>>>>>> d6d6244f042e7401702daf3dc20a3d6f3dc472f5
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
<<<<<<< HEAD
				$(PATH_SRC)ft_fork.c\
=======
				$(PATH_SRC)lld.c\
				$(PATH_SRC)lldi.c\
				$(PATH_SRC)lfork.c\
				$(PATH_SRC)add.c\
				$(PATH_SRC)sub.c\
>>>>>>> d6d6244f042e7401702daf3dc20a3d6f3dc472f5

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
<<<<<<< HEAD
				ft_fork.o\
=======
				lld.o\
				lldi.o\
				lfork.o\
				add.o\
				sub.o\
>>>>>>> d6d6244f042e7401702daf3dc20a3d6f3dc472f5

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
