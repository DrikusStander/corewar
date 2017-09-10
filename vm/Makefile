# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/29 11:02:17 by gvan-roo          #+#    #+#              #
#    Updated: 2017/09/10 12:52:15 by gvan-roo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	corewar

PATH_HEAD	=	./headers/
PATH_LIB	=	./libft/
PATH_SRC	=	./src/
PATH_OSC	=	./orc/

HEADERS		=	vm.h

SRC			=	$(PATH_SRC)vm_main.c\
				$(PATH_SRC)open_files.c\
				$(PATH_SRC)print_mem.c\
				$(PATH_SRC)print_ncurses.c\
				$(PATH_SRC)init_vm.c\
				$(PATH_SRC)print_champ_mem.c\
				../ops/st.c\
				$(PATH_SRC)run_machine_run.c\
				$(PATH_SRC)op.c\
				$(PATH_SRC)utils_vm.c\
				../ops/add.c\
				../ops/sub.c\
				../ops/and.c\
				../ops/or.c\
				../ops/xor.c\
				../ops/zjmp.c\
				../ops/extras.c\
				../ops/ldi.c\
				../ops/sti.c\
				../ops/fork.c\
				../ops/lldi.c\
				../ops/lfork.c\
				../ops/aff.c\
				../ops/ld.c\
				../ops/lld.c\

OSC			=	vm_main.o\
				open_files.o\
				print_mem.o\
				print_ncurses.o\
				init_vm.o\
				print_champ_mem.o\
				st.o\
				run_machine_run.o\
				op.o\
				utils_vm.o\
				add.o\
				sub.o\
				and.o\
				or.o\
				xor.o\
				zjmp.o\
				extras.o\
				ldi.o\
				sti.o\
				fork.o\
				lldi.o\
				lfork.o\
				aff.o\
				ld.o\
				lld.o\

FLAGS		=	-Wall -Werror -Wextra 

all	:	$(NAME)

$(NAME)	:	$(OSRC)
	make -C $(PATH_LIB) fclean && make -C $(PATH_LIB)
	gcc $(FLAGS) -I $(PATH_HEAD)$(HEADERS) -c $(SRC)
	gcc -o $(NAME) $(OSC) -L$(PATH_LIB) -lft -lncurses

$(OSRC) :
	
clean	:
	rm -f $(OSC)
	make -C $(PATH_LIB) clean

fclean	:	clean
	rm -f $(NAME)
	make -C $(PATH_LIB) fclean

re	:	fclean
	make


#				$(PATH_SRC)check_key_swop_bytes.c
#				check_key_swop_bytes.o
