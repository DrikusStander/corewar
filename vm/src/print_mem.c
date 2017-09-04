/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 16:07:23 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/09/04 11:42:39 by hstander         ###   ########.fr       */
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
}

/*
**	Subfunction of print memory
*/

unsigned char 	*print_line(unsigned char *mem, size_t size)
{
	unsigned char *mem_c;

	mem_c = mem;
	while ((size_t)(mem_c - mem) < size && (mem_c - mem) < 32)
	{
		ft_print_hex(*mem_c);
		write(1, " ", 1);
		++mem_c;
	}
	while((mem_c - mem) < 32)
	{
		write(1, "   ", 3);
		++mem_c;
	}
	mem_c = mem;
	while ((size_t)(mem_c - mem) < size && (mem_c - mem) < 32)
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
		size -= 32;
	}
}

/*
**	Utitlity function that convert the value of unsigned char in memory
**	to the integer value.
*/

int			get_int_from_mem(unsigned char *mem, int size)
{
	int		ret;
	int		mul;

	mul = 1;
	ret = 0;
	size--;
	while (size)
	{
		ret = ret + (mem[size] * mul);
		mul *= 256;
		size--;
	}
	return (ret);
}
