# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/29 11:02:17 by gvan-roo          #+#    #+#              #
#    Updated: 2017/09/11 11:19:29 by gvan-roo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	corewar

PATH_HEAD	=	./headers/
PATH_LIB	=	./libft/
PATH_SRC	=	./src/
PATH_OPS	=	./src/ops/
PATH_OSC	=	./orc/

HEADERS		=	vm.h

SRC			=	$(PATH_SRC)vm_main.c\
				$(PATH_SRC)open_files.c\
				$(PATH_SRC)read_champs.c\
				$(PATH_SRC)print_mem.c\
				$(PATH_SRC)print_ncurses.c\
				$(PATH_SRC)init_vm.c\
				$(PATH_SRC)print_champ_mem.c\
				$(PATH_SRC)run_machine_run.c\
				$(PATH_SRC)op.c\
				$(PATH_SRC)utils_vm.c\
				$(PATH_OPS)st.c\
				$(PATH_OPS)add.c\
				$(PATH_OPS)sub.c\
				$(PATH_OPS)and.c\
				$(PATH_OPS)or.c\
				$(PATH_OPS)xor.c\
				$(PATH_OPS)zjmp.c\
				$(PATH_OPS)extras.c\
				$(PATH_OPS)ldi.c\
				$(PATH_OPS)sti.c\
				$(PATH_OPS)fork.c\
				$(PATH_OPS)lldi.c\
				$(PATH_OPS)lfork.c\
				$(PATH_OPS)aff.c\
				$(PATH_OPS)ld.c\
				$(PATH_OPS)lld.c\

OSC			=	vm_main.o\
				open_files.o\
				read_champs.o\
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
