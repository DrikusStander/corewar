/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  lld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 13:48:01 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/24 10:22:44 by hstander         ###   ########.fr       */
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
		i = (i >> 8 & 0xFF) | (i << 8 & 0xFF00);
		write(fd, (void *)&i, 2);
	}
	return (i);
}

/*
**	Sub function of create_param to handle the argument1 if it
**	is a register or a direct value
*/

static int			create_param_sub(char *arg1, t_args *ag)
{
	int				arg_param;
	char			*sub;

	sub = NULL;
	arg_param = 0;
	if (arg1[0] == '%')
	{
		if (arg1[1] == ':')
		{
			sub = ft_strsub(arg1, 2, (ft_strlen(arg1) - 2));
			arg_param = get_label_offset(sub, ag);
		}
		else
		{
			sub = ft_strsub(arg1, 1, (ft_strlen(arg1) - 1));
			arg_param = ft_atoi(sub);
		}
	}
	else
	{
		sub = ft_strsub(arg1, 1, (ft_strlen(arg1) - 1));
		arg_param = ft_atoi(sub);
	}
	free(sub);
	return (arg_param);
}

/*
**	Receives the file descriptor and lld's parameters as arguments.
**	Processes the parameters to get the int value of them, and the second's
**	parameter's (a register) last byte to the file
*/

static void			create_param(int fd, char *arg1, char *reg, t_args *ag)
{
	int				arg_param;
	char			*sub;

	sub = NULL;
	if (arg1[0] == '%' || arg1[0] == 'r')
		arg_param = create_param_sub(arg1, ag);
	else
		arg_param = ft_atoi(arg1);
	arg_param = swop_int_bits(fd, arg_param, arg1[0]);
	sub = ft_strsub(reg, 1, (ft_strlen(reg) - 1));
	arg_param = ft_atoi(sub);
	write(fd, (void *)&arg_param, 1);
	free(sub);
}

/*
**	Function receives file descriptor and lld's parameters as arguments.
**	Processes the parameters into an argument code byte, and writes the
**	acb to the file indicated by fd.
*/

static void			create_acb(int fd, char *arg1, char *reg)
{
	unsigned char	hex;
	int				write_ret;

	if (reg[0] != 'r')
	{
		ft_printf("Invalid parameter 2 for lld, should be a reg - exiting\n");
		exit(0);
	}
	hex = 0b00010000;
	if (arg1[0] == '%')
		hex = hex | 0b10000000;
	else if (arg1[0] == 'r')
	{
		ft_printf("Invalid parameter 1 for lld, should be a T_DIR | T_IND - exiting\n");
		exit(0);
	}
	else
		hex = hex | 0b11000000;
	write_ret = write(fd, (void *)&hex, 1);
	if (write_ret < 0)
	{
		ft_printf("Unable to write lld's acb to file - exiting\n");
		exit(1);
	}
}

/*
**	Main function handling load opcode lld. Writes lld's opcode to
**	the file indicated by fd, and call relevant functions to
**	write the argument coding byte and parameter values to file.
*/

void				ft_lld(t_args *ag, t_prog *lst)
{
	unsigned char	hex;
	int				write_ret;

	hex = 0x0d;
	write_ret = write(ag->fd, (void *)&hex, 1);
	if (write_ret < 0)
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
	create_param(ag->fd, lst->data[1], lst->data[2], ag);
}
