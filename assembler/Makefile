# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/13 13:39:56 by gvan-roo          #+#    #+#              #
#    Updated: 2017/09/13 16:42:11 by gvan-roo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_A		=	asm

SDIR_A		=	./src
ODIR_A		=	./obj
IDIR_A		=	./headers
CFLAGS_A	=	-I$(IDIR_A)
LDIR		=	./libft
LIBS_A		=	-lft

_DEPS_A		=	asm.h op.h
DEPS_A		=	$(patsubst %,$(IDIR_A)/%,$(_DEPS_A))

_OBJ_A		=	asm_main.o\
				check.o\
				list.o\
				extras.o\
				parse_line.o\
				free.o\
				label_offset.o\
				name_comment.o\
				init.o\
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
				error.o\
				extras2.o
OBJ_A		=	$(patsubst %,$(ODIR_A)/%,$(_OBJ_A))

all:	$(NAME_A)

$(ODIR_A)/%.o:	$(SDIR_A)/%.c
	gcc -c -o $@ $< $(CFLAGS_A)

$(NAME_A):	$(OBJ_A)
	make -C $(LDIR) re
	gcc -o $@ $^ $(CFLAGS_A) -L$(LDIR) $(LIBS_A)

.PHONY:	clean fclean re
clean:
	rm -f $(ODIR_A)/*.o
	make -C $(LDIR) clean
fclean:	clean
	rm -f $(NAME_A)
	make -C $(LDIR) fclean
re:	fclean
	make
