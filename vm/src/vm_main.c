/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 08:34:55 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/25 16:45:39 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vm.h"
#include <stdio.h>

void				print_hex(int n)
{
	unsigned char	c;
	unsigned char	temp;

	temp = n;
	temp /= 16;
	if (temp % 16 >= 10)
	{
		temp = (temp % 16) % 10 + 'a';
		write(1, &temp, 1);
	}
	else
	{
		temp = (temp % 16) + '0';
		write(1, &temp, 1);
	}
	if (n % 16 >= 10)
	{
		c = (n % 16) % 10 + 'a';
		write(1, &c, 1);
	}
	else
	{
		c = (n % 16) + '0';
		write(1, &c, 1);
	}
}

void				check_cor_files(int ac, char **av)
{
	int				ctr;
	int				fd;
	int				read_ret;
	unsigned char	buf[sizeof(header_t)];

	ctr = 1;
	while (ctr < ac)
	{
		fd = open(av[ctr], O_RDONLY);
		if (fd < 0)
		{
			ft_printf("Unable to open file %s - exiting\n", av[ctr]);
			exit (0);
		}
		read_ret = read(fd, buf, sizeof(header_t));
//		print_hex(buf[4 + PROG_NAME_LENGTH + 1]);

		size_t i = 120;
		while (i < 140)
		{
			ft_printf("%i  :",i); 
			print_hex(buf[i]);
			ft_printf("  ");
			i++;
		}
		ft_printf("\n");
		if (1) //	Insert func :check_cor_header(fd)\n	
			ft_printf("Insert func :check_cor_header(fd)\n");

		ctr++;
	}
}

int			main(int argc, char **argv)
{
	if (argc < 2 || argc > 5)
	{
		ft_printf("Usage: ./corewar <champ1.cor> <...>\n");
		return (0);
	}
	check_cor_files(argc, argv);
	return (0);
}
