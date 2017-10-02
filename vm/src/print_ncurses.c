/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ncurses.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 16:07:23 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/09/27 07:59:52 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vm.h"

void					index_inc(int *i)
{
	*i += 1;
	if (*i == MEM_SIZE)
		i = 0;
}

/*
**	Function for printing out bytes in hexadecimal
*/

static void				ft_print_hex_nc(unsigned char c, unsigned char memp)
{
	char				*map;

	attron(COLOR_PAIR(memp));
	map = ft_strdup("0123456789abcdef");
	addch(*(map + (c / 16)));
	addch(*(map + (c % 16)));
	attroff(COLOR_PAIR(memp));
	free(map);
}

/*
**	Subfunction of print memory
**	bit is the amount of bytes printed on a single nine
*/

static void				print_line_nc(t_vm *vm, size_t size, int bit, int *i)
{
	t_vm				*mem_c;
	int					k;

	k = 0;
	mem_c = vm;
	while ((size_t)k < size && k < bit)
	{
		ft_print_hex_nc(mem_c->mem[*i], vm->mem_p[*i]);
		printw(" ");
		index_inc(i);
		k++;
	}
	while (k < bit)
	{
		printw("   ");
		k++;
	}
}

/*
**	Function for printing out the memory of at address addr
**	of size size.
*/

void					print_mem_nc(t_vm *vm, size_t size, int bit)
{
	t_vm				*vmc;
	int					i;
	int					lc;

	vmc = vm;
	i = 0;
	lc = 0;
	while ((long int)size > 0)
	{
		if (lc < 62)
		{
			print_line_nc(vmc, size, bit, &i);
		}
		lc++;
		printw("\n");
		size -= bit;
	}
}
