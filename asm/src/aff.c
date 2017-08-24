/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 13:48:01 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/24 14:38:43 by hstander         ###   ########.fr       */
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
** checks if the current argument is a label and returns correct value if true.
*/
static int			check_if_label(t_prog *lst, int arg, t_args *ag)
{
	char	*sub;
	int		arg_param;
	char	*temp;

	sub = NULL;
	if (lst->data[arg][1] == ':')
	{
		temp = ft_strsub(lst->data[arg], 2, (ft_strlen(lst->data[arg]) - 1));
		sub = ft_strjoin(temp, ":");
		free(temp);
		arg_param = get_label_offset(sub, ag, lst);
	}
	else
	{
		sub = ft_strsub(lst->data[arg], 1, (ft_strlen(lst->data[arg]) - 1));
		arg_param = ft_atoi(sub);
	}
	free(sub);
	return (arg_param);
}

/*
**	Receives the file descriptor and ld's parameters as arguments.
**	Processes the parameters to get the int value of them, and
**	prints the first parameter's 4 bytes to file, and the second's
**	parameter's (a register) last byte to the file
*/
static void			create_param(t_args *ag, t_prog *lst)
{
	int				arg_param;

	arg_param = 0;
	if (lst->data[1][0] == 'r' )
		arg_param = check_if_label(lst, 1, ag);
	arg_param = swop_int_bits(ag->fd, arg_param, lst->data[1][0]);
}

/*	
**	Function receives file descriptor and ld's parameters as arguments.
**	Processes the parameters into an argument code byte, and writes the
**	acb to the file indicated by fd.
*/
static void			create_acb(int fd, char *arg1)
{
	unsigned char	hex;

	if (arg1[0] != 'r')
	{
		ft_printf("Invalid parameter for aff, should be a register\n");
		exit (0);
	}
	else
		hex = 0b01000000;
	if (write(fd, (void *)&hex, 1) < 0)
	{
		ft_printf("Unable to write aff's argument coding byte to file - exiting\n");
		exit(1);
	}
}

/*
**	Main function handling st opcode. Writes st's opcode to 
**	the file indicated by fd, and call relevant functions to 
**	write the argument coding byte and parameter values to file.
*/
void				ft_aff(t_args *ag, t_prog *lst)
{
	unsigned char	hex;
	hex = 0x10;
	if (write(ag->fd, (void *)&hex, 1) < 0)
	{
		ft_printf("Unable to write opcode to file\n");
		exit(1);
	}
	if (ft_arrlen(lst->data) != 2)
	{
		ft_printf("not the right amount of args\n");
		exit(1);
	}
	create_acb(ag->fd, lst->data[1]);
	create_param(ag, lst);
}
