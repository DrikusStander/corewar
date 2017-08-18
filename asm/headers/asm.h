/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 10:59:32 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/18 10:43:47 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ASM_H
# define __ASM_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include "op.h"

typedef struct s_prog	t_prog;
typedef struct s_args	t_args;

struct					s_prog
{
	char				*label;
	char				**data;
	t_prog				*next;
};

struct					s_args
{
	t_prog				*head;
	t_prog				*lst;
	char				*line;
	char				*trim_str;
	char				**ref;
	char				**ref2;
};

int						check_arguments(int argc, char **argv);
int						check_valid_file(char *file_name);
void					parse_line(t_args *ag);
void					ft_setlist(t_args *ag);
void					ft_lbl_com(t_args *ag);
void					ft_com(t_args *ag);
void					ft_lbl(t_args *ag, int i);
void					ft_nm_com(t_args *ag);
int						ft_chr_i(char *str, char c);
void					swap_bytes(unsigned int i, int fd);
size_t					ft_arrlen(char **arr);
void					ft_freelst(t_prog *lst);

#endif
