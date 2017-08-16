/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/16 13:48:01 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/16 17:03:00 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/asm.h"

static void			create_param(int fd, char *arg1, char *reg)
{
	int				arg_bytes;
	int				arg_param;
	unsigned char	hex;
	char			*sub;

	if (arg1[0] == '%')
	{
		arg_bytes = T_DIR;
		sub = ft_strsub(arg1, 1, (ft_strlen(arg1) - 1));
		arg_param = ft_atoi(sub);
	}
	else if (arg1[0] == 'r')
	{
		arg_bytes = T_REG;
		sub = ft_strsub(arg1, 1, (ft_strlen(arg1) - 1));
		arg_param = ft_atoi(sub);
	}
	else
	{
		arg_bytes = T_IND;
		arg_para = ft_atoi(sub);
	}
	while (arg_bytes)
	{
		hex = arg_param >>  
		write(fd, (void *)

static void			create_acb(int fd, char *arg1, char *reg)
{
	unsigned char	hex;
	int				write_ret;

	hex = 0x00;
	if (arg1[0] == '%')
		hex = hex | 0x80;
	else if (arg1[0] == 'r')
		hex = hex | 0x40;
	else
		hex = hex | 0xC0;
	if (reg[0] == 'r')
		hex = hex | 0x01;
	write_ret = write(fd, (void *)&hex, 1);
	if (write_ret < 0)
	{
		ft_printf("Unable to write to file\n");
		exit(1)
	}
}

void				handle_ld(int fd, char *arg1, char *reg)
{
	unsigned char	hex;
	int				write_ret;

	hex = 0x02;
	write_ret = write(fd, (void *)&hex, 1);
	if (write_ret < 0)
	{
		ft_printf("Unable to write opcode to file\n");
		exit(1);
	}
	create_acb(fd, arg1, reg);
	create_param(fd, arg1, reg);
}

int			main(void)
{
	int		ret;

	ret = open("test.s", O_APPEND | O_CREAT | O_TRUNC | O_RDWR);
	handle_ld(ret, "34", "r3");
	return (0);
}
