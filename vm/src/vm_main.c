/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 08:34:55 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/26 09:39:42 by gvan-roo         ###   ########.fr       */
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

void				read_prog_info(int fd, int prog_num, t_champ champ_head);
{
	t_champ			*champ_ptr;

	champ_ptr = champ_head;
	if (!check_magic(fd, champ_ptr))
		ft_printf("Incorrect magic number for champion :\n");


void				check_cor_files(int ac, char **av, t_champ champ_head)
{
	int				ctr;
	int				fd;

	ctr = 1;
	while (ctr < ac)
	{
		fd = open(av[ctr], O_RDONLY);
		if (fd < 0)
		{
			ft_printf("Unable to open file %s - exiting\n", av[ctr]);
			exit (0);
		}
		read_prog_info(fd, (ctr - 1), champ_head);
/*		lseek(fd, 134, SEEK_SET);
		read(fd, int_buf, sizeof(int));
		file_size = (int)int_buf;
		ft_printf("File size :%i\n", file_size);
		print_hex(buf[4 + PROG_NAME_LENGTH + 1]);

		size_t i = 135;
		while (i < 140)
		{
			ft_printf("%i  :",i); 
			print_hex(buf[i]);
			ft_printf("  ");
			i++;
		}
		ft_printf("\n");
*/		ctr++;
	}
}

int				main(int argc, char **argv)
{
	t_champion	*champ_head;
	if (argc < 2 || argc > 5)
	{
		ft_printf("Usage: ./corewar <champ1.cor> <...>\n");
		return (0);
	}
	champ_head = ft_memalloc(sizeof(t_champion));
	check_cor_files(argc, argv, champ_head);
	return (0);
}
