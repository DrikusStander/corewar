/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 13:48:01 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/25 14:44:35 by hstander         ###   ########.fr       */
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
		byte_swop = (i >> 8) & 0xFF;
		write(fd, (void *)&byte_swop, 1);
		byte_swop = 0x00;
		byte_swop = i & 0xFF;
		write(fd, (void *)&byte_swop, 1);
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
static void			create_param(char *arg1, char *arg2, t_args *ag, t_prog *lst)
{
	int				arg_param;
	char			*sub;
	char			*temp;

	sub = NULL;
	sub = ft_strsub(arg1, 1, (ft_strlen(arg1) - 1));
	arg_param = ft_checknum(sub);
	free(sub);
	if (arg_param < 1 || arg_param > 16)
	{
		ft_printf("Invalid register\n");
		exit(0);
	}
	arg_param = swop_int_bits(ag->fd, arg_param, arg1[0]);
	if (arg2[0] == 'r')
	{
		sub = ft_strsub(arg2, 1, (ft_strlen(arg2) - 1));
		arg_param = ft_checknum(sub);
		free(sub);
		if (arg_param < 1 || arg_param > 16)
	    {
			ft_printf("Invalid register\n");
			exit(0);
		}	
	}
	else if (arg2[0] == ':')
	{
		temp = ft_strsub(arg2, 1, (ft_strlen(arg2) - 1));
		sub = ft_strjoin(temp, ":");
		free(temp);
		arg_param = get_label_offset(sub, ag, lst);
		free(sub);
	}
	else
		arg_param = ft_checknum(arg2);
	arg_param = swop_int_bits(ag->fd, arg_param, arg2[0]);
}

/*	
**	Function receives file descriptor and ld's parameters as arguments.
**	Processes the parameters into an argument code byte, and writes the
**	acb to the file indicated by fd.
*/
static void			create_acb(int fd, char *arg1, char *arg2)
{
	unsigned char	hex;

	if (arg1[0] != 'r')
	{
		ft_printf("Invalid parameter 1 for st, should be a register\n");
		exit (0);
	}	
	hex = 0b01000000;
	if (arg2[0] == '%')
	{
		ft_printf("Invalid parameter 2 for st, should be T_REG or T_IND\n");
		exit (0);
	}
	else if (arg2[0] == 'r')
		hex = hex | 0b00010000;
	else
		hex = hex | 0b00110000;
	if (write(fd, (void *)&hex, 1) < 0)
	{
		ft_printf("Unable to write st's argument coding byte to file - exiting\n");
		exit(1);
	}
}

/*
**	Main function handling st opcode. Writes st's opcode to 
**	the file indicated by fd, and call relevant functions to 
**	write the argument coding byte and parameter values to file.
*/
void				ft_st(t_args *ag, t_prog *lst)
{
	unsigned char	hex;
	hex = 0x03;
	if (write(ag->fd, (void *)&hex, 1) < 0)
	{
		ft_printf("Unable to write opcode to file\n");
		exit(1);
	}
	if (ft_arrlen(lst->data) != 3)
	{
		ft_printf("not the right amount of args\n");
		exit(1);
	}
	create_acb(ag->fd, lst->data[1], lst->data[2]);
	create_param(lst->data[1], lst->data[2], ag, lst);
}
