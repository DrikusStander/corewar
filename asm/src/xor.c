/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 13:48:01 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/22 15:14:02 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/asm.h"

/*
**	Swops the bits of an int from little endian to big endian
**	and prints to file the correct number of bytes
*/
static int			swop_int_bits(int fd, int i, char c)
{
	unsigned char	byte_swop;

	if (c == '%')
	{
		i = (i >> 24 & 0xFF) | (i >> 8 & 0xFF00) |
			(i << 8 & 0xFF0000) | (i << 24 & 0xFF000000);
		write(fd, (void *)&i, 4);
	}
	else if (c == 'r')
	{
		byte_swop = i & 0xFF;
		write(fd, (void *)&byte_swop, 1);
	}
	else
	{
		i = (i >> 8 & 0x00FF) | (i << 8 & 0xFF00);
		write(fd, (void *)&i, 2);
	}
	return (i);
}

/*
**	Receives the file descriptor and ld's parameters as arguments.
**	Processes the parameters to get the int value of them, and
**	prints the first parameter's 4 bytes to file, and the second's
**	parameter's (a register) last byte to the file
*/
static void			create_param(int fd, char *arg1, char *arg2, char *arg3)
{
	int				arg_param;
	char			*sub;

	sub = NULL;
	if (arg1[0] == 'r' || arg1[0] == '%')
	{
		sub = ft_strsub(arg1, 1, (ft_strlen(arg1) - 1));
		arg_param = ft_atoi(sub);
		free(sub);
	}
	else
		arg_param = ft_atoi(arg1);
	arg_param = swop_int_bits(fd, arg_param, arg1[0]);
	if (arg2[0] == 'r' || arg2[0] == '%')
	{
		sub = ft_strsub(arg2, 1, (ft_strlen(arg2) - 1));
		arg_param = ft_atoi(sub);
		free(sub);
	}
	else
		arg_param = ft_atoi(arg2);
	arg_param = swop_int_bits(fd, arg_param, arg2[0]);
	sub = ft_strsub(arg3, 1, (ft_strlen(arg3) - 1));
	arg_param = ft_atoi(sub);
	arg_param = swop_int_bits(fd, arg_param, arg3[0]);
	free(sub);
}

/*	
**	Function receives file descriptor and ld's parameters as arguments.
**	Processes the parameters into an argument code byte, and writes the
**	acb to the file indicated by fd.
*/
static void			create_acb(int fd, char *arg1, char *arg2, char *arg3)
{
	unsigned char	hex;

	if (arg3[0] != 'r')
	{
		ft_printf("Invalid parameter 3 for xor, should be a register\n");
		exit (0);
	}	
	if (arg1[0] == '%')
		hex = 0b10000000;
	else if (arg1[0] == 'r')
		hex = 0b01000000;
	else
		hex = 0b11000000;
	if (arg2[0] == 'r')
		hex = hex | 0b00010000;
	else if (arg2[0] == '%')
		hex = hex | 0b00100000;
	else
		hex = hex | 0b00110000;
	hex = hex | 0b00000100;
	if (write(fd, (void *)&hex, 1) < 0)
	{
		ft_printf("Unable to write xor's argument coding byte to file - exiting\n");
		exit(1);
	}
}

/*
**	Main function handling st opcode. Writes st's opcode to 
**	the file indicated by fd, and call relevant functions to 
**	write the argument coding byte and parameter values to file.
*/
void				ft_xor(t_args *ag, t_prog *lst)
{
	unsigned char	hex;
	hex = 0x08;
	if (write(ag->fd, (void *)&hex, 1) < 0)
	{
		ft_printf("Unable to write opcode to file\n");
		exit(1);
	}
	if (ft_arrlen(lst->data) != 4)
	{
		ft_printf("not the right amount of args\n");
		exit(1);
	}
	create_acb(ag->fd, lst->data[1], lst->data[2], lst->data[3]);
	create_param(ag->fd, lst->data[1], lst->data[2], lst->data[3]);
}
