/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 16:07:23 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/30 17:54:01 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vm.h"

/*
**	Function for printing out bytes in hexadecimal
*/

void	ft_print_hex(int c)
{
	char *map = "0123456789abcdef";

	write(1, map + (c / 16), 1);
	write(1, map + (c % 16), 1);
	write(1, " ", 1);
}

/*
**	Subfunction of print memory
*/

unsigned char 	*print_line(unsigned char *mem, size_t size)
{
	unsigned char *mem_c;

	mem_c = mem;
	while ((size_t)(mem_c - mem) < size && (mem_c - mem) < 16)
	{
		ft_print_hex(*mem_c);
//		if ((size_t)(mem_c + 1) % 2 == 0)
//			write(1, " ", 1);
		++mem_c;
	}
	while((mem_c - mem) < 16)
	{
		write(1, "  ", 2);
//		if ((size_t)(mem_c + 1) % 2 == 0)
//			write(1, " ", 1);
		++mem_c;
	}
	mem_c = mem;
	while ((size_t)(mem_c - mem) < size && (mem_c - mem) < 16)
	{
		if (*mem_c >= 32 && *mem_c <= 126)
			write(1, &(*mem_c), 1);
		else
			write(1, ".", 1);
		++mem_c;
	}
	write(1, "\n", 1);
	return (mem_c);
}

/*
**	Function for printing out the memory of at address addr
**	of size size.
*/

void	print_memory(const void *addr, size_t size)
{
	unsigned char *mem;

	mem = (unsigned char *)addr;
	while ((long int)size > 0)
	{
		mem = print_line(mem, size);
		size -= 16;
	}
}
