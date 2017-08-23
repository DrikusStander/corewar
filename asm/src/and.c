/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 13:48:01 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/23 10:31:05 by hstander         ###   ########.fr       */
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
static void			create_param(t_args *ag, t_prog *lst)
{
	int				arg_param;
	char			*sub;
	char			*temp;
	int 			offset;
	int 			flag;
	t_prog			*head;

	sub = NULL;
	head = ag->head;
	flag = 0;
	arg_param = 0;
	offset = 0;
	if (lst->data[1][0] == 'r' || lst->data[1][0] == '%')
	{
		if (lst->data[1][1] == ':')
		{
			temp = ft_strsub(lst->data[1], 2, (ft_strlen(lst->data[1]) - 1));
			sub = ft_strjoin(temp, ":");
			free(temp);
			while (head)
			{
				if (head->label)
				{
					if (ft_strncmp(head->label, ag->cur_label, ft_strlen(ag->cur_label)) == 0)
						flag = 1;
					if (ft_strncmp(head->label, sub, ft_strlen(sub)) == 0)
						break ;
				}
				head = head->next;
			}
			if (flag == 1)
			{
				while (lst)
				{
					if (lst->label)
					{
						if (ft_strncmp(lst->label, sub, ft_strlen(sub)) == 0)
							break;
					}
					offset += lst->bytes;
					lst = lst->next;
				}
			}
			else
			{
				while (head)
				{
					if (head->label)
					{
						if (ft_strncmp(head->label, ag->cur_label, ft_strlen(ag->cur_label)) == 0)
							break;
					}
					offset += head->bytes;
					head = head->next;
				}
			}

		}
		else
		{
			sub = ft_strsub(lst->data[1], 1, (ft_strlen(lst->data[1]) - 1));
			arg_param = ft_atoi(sub);
		}
		ft_printf("---------->>%d\n", offset);
		free(sub);
	}
	else
		arg_param = ft_atoi(lst->data[1]);
	arg_param = swop_int_bits(ag->fd, arg_param, lst->data[1][0]);
	if (lst->data[2][0] == 'r' || lst->data[2][0] == '%')
	{
		sub = ft_strsub(lst->data[2], 1, (ft_strlen(lst->data[2]) - 1));
		arg_param = ft_atoi(sub);
		free(sub);
	}
	else
		arg_param = ft_atoi(lst->data[2]);
	arg_param = swop_int_bits(ag->fd, arg_param, lst->data[2][0]);
	sub = ft_strsub(lst->data[3], 1, (ft_strlen(lst->data[3]) - 1));
	arg_param = ft_atoi(sub);
	arg_param = swop_int_bits(ag->fd, arg_param, lst->data[3][0]);
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
		ft_printf("Invalid parameter 3 for and, should be a register\n");
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
		ft_printf("Unable to write and's argument coding byte to file - exiting\n");
		exit(1);
	}
}

/*
**	Main function handling st opcode. Writes st's opcode to 
**	the file indicated by fd, and call relevant functions to 
**	write the argument coding byte and parameter values to file.
*/
void				ft_and(t_args *ag, t_prog *lst)
{
	unsigned char	hex;
	hex = 0x06;
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
	create_param(ag, lst);
}
