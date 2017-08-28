/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_key_swop_bytes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 16:11:22 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/28 16:23:37 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vm.h"

/*
** Utility function.
** Takes the address of the byte to be converted into hex. This address
** needs to be converted into two values, hence key is incremented twice.
** The second parameter takes the array into which the values are to be
** placed.
** Returns the pointer to the next element of the array.
*/

char *add_byte(unsigned char *mem_c, char *key)
{
	char *map = "0123456789abcdef";

	*key++ = map[*mem_c / 16];
	*key++ = map[*mem_c % 16];
	return (key);
}

/*
** Main function.
** Takes the address of the buffer that holds the first 4 byte of the FD.
** Takes the total size of the buffer.
** check_key converts the first 4 bytes of the FD into hex, which it then
** stores in an array.
** It the compares the array to the reference array which is defined in our
** header file.
** If the two arrays match, aka the two magic keys, the function returns 1.
** If the two arrays do not match, the funtion returns 0.
*/

int	check_key(const void *mem, size_t size)
{
	char key[9];
	char *key_c;
	char *ref = "00ea83f3";
	unsigned char *mem_c;

	mem_c = (unsigned char *)mem;
	key_c = key;
	while ((size_t)(mem_c - (unsigned char*)mem) < size)
		key_c = add_byte(mem_c++, key_c);
	*key_c = '\0';
	if (ft_strcmp(ref, key) == 0)
		return (1);
	return (0);
}

/*
**	Swops the bytes of a passed argument int
*/

int					swop_bytes(int i, int no_bytes)
{
	if (no_bytes == 4)
	{
		i = (i >> 24 & 0xFF) | (i >> 8 & 0xFF00) |
			(i << 8 & 0xFF0000) | (i << 24 & 0xFF0000);
	}
	return (i);
}
