/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 13:48:01 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/23 14:31:08 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/asm.h"

/*
**	Swops the bits of an int from little endian to big endian
**	and prints to file the correct number of bytes

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
		i = (i >> 24 & 0xFF) | (i >> 8 & 0xFF00) |
			(i << 8 & 0xFF0000) | (i << 24 & 0xFF000000);
		write(fd, (void *)&i, 4);
	}
	return (i);
}
*/
/*
**	Receives the file descriptor and ld's parameters as arguments.
**	Processes the parameters to get the int value of them, and
**	prints the first parameter's 4 bytes to file, and the second's
**	parameter's (a register) last byte to the file

static void			create_param(int fd, char *arg1, char *reg)
{
	int				arg_param;
	char			*sub;

	sub = NULL;
	if (arg1[0] == '%')
	{
		sub = ft_strsub(arg1, 1, (ft_strlen(arg1) - 1));
		arg_param = ft_atoi(sub);
	}
	else if (arg1[0] == 'r')
	{
		sub = ft_strsub(arg1, 1, (ft_strlen(arg1) - 1));
		arg_param = ft_atoi(sub);
	}
	else
		arg_param = ft_atoi(arg1);
	arg_param = swop_int_bits(fd, arg_param, arg1[0]);
	sub = ft_strsub(reg, 1, (ft_strlen(reg) - 1));
	arg_param = ft_atoi(sub);
	write(fd, (void *)&arg_param, 1);
	free(sub);
}
*/
/*	
**	Function receives file descriptor and ld's parameters as arguments.
**	Processes the parameters into an argument code byte, and writes the
**	acb to the file indicated by fd.
*/
static void			create_acb(int fd, char *arg1, char *reg)
{
	unsigned char	hex;
	int				write_ret;

	if (reg[0] != 'r')
	{
		ft_printf("Invalid parameter 2 for ld, should be a register - exiting\n");
		exit (0);
	}	
	hex = 0b00010000;
	if (arg1[0] == '%')
		hex = hex | 0b10000000;
	else if (arg1[0] == 'r')
		hex = hex | 0b01000000;
	else
		hex = hex | 0b11000000;
	write_ret = write(fd, (void *)&hex, 1);
	if (write_ret < 0)
	{
		ft_printf("Unable to write ld's argument coding byte to file - exiting\n");
		exit(1);
	}
}

/*
**	Main function handling load opcode ld. Writes ld's opcode to 
**	the file indicated by fd, and call relevant functions to 
**	write the argument coding byte and parameter values to file.
*/
void				fd_ld(t_args *ag, t_prog *lst)
{
	unsigned char	hex;
	int				write_ret;
	char			*arg1;
	char			*reg;

	hex = 0x02;
	write_ret = write(fd, (void *)&hex, 1);
	if (write_ret < 0)
	{
		ft_printf("Unable to write opcode to file\n");
		exit(1);
	}
	create_acb(ag->fd, lst->data[1], lst->data[2]);
//	create_param(fd, arg1, reg);
}

int			main(void)
{
	int		ret;

	ret = open("test.s", O_APPEND | O_CREAT | O_TRUNC | O_RDWR, 0755);
	ft_ld(ret, "1234", "r1");
	close(ret);
	return (0);
}
