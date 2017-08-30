# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/29 11:02:17 by gvan-roo          #+#    #+#              #
#    Updated: 2017/08/30 09:46:34 by hstander         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	corewar

PATH_HEAD	=	./headers/
PATH_LIB	=	./libft/
PATH_SRC	=	./src/
PATH_OSC	=	./orc/

HEADERS		=	vm.h

SRC			=	$(PATH_SRC)vm_main.c\
				$(PATH_SRC)check_key_swop_bytes.c\
				$(PATH_SRC)open_files.c\
				$(PATH_SRC)print_mem.c\
				$(PATH_SRC)init_vm.c\
				$(PATH_SRC)print_champ_mem.c\
				$(PATH_SRC)opcodes.c\
				../ops/st.c

OSC			=	vm_main.o\
				check_key_swop_bytes.o\
				open_files.o\
				print_mem.o\
				init_vm.o\
				print_champ_mem.o\
				opcodes.o\
				st.o\


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
