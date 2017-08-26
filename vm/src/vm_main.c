/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 08:34:55 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/26 11:24:24 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vm.h"
#include <stdio.h>
/*
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
*/

void				read_prog(int fd, t_champ *champ_ptr)
{
	int ctr;

	ctr = 0;
	ft_bzero(champ_ptr->prog, CHAMP_MAX_SIZE);
	lseek(fd, 2192, SEEK_SET);
	read(fd, champ_ptr->prog, champ_ptr->head.prog_size);
	champ_ptr->carry = 0;
	champ_ptr->pc = 0;
	while (ctr < 17)
	{
		champ_ptr->reg[ctr] = 0;
		ctr++;
	}
	champ_ptr->exec_cycle = 1;
}

void				read_prog_name_comment(int fd, t_champ *champ_ptr)
{
	void			*int_buf;

	int_buf = ft_memalloc(sizeof(int));
//	ft_bzero(int_buf, sizeof(int));
	ft_bzero(champ_ptr->head.prog_name, (PROG_NAME_LENGTH + 1));
	lseek(fd, 5, SEEK_SET);
	read(fd, champ_ptr->head.prog_name, PROG_NAME_LENGTH);
	read(fd, int_buf, sizeof(int));
	ft_printf("sizeof int :%i\n", sizeof(int));
	champ_ptr->head.prog_size = *(unsigned int *)int_buf;
	ft_printf("prog size :%i\n", champ_ptr->head.prog_size);
	read(fd, champ_ptr->head.comment, COMMENT_LENGTH);
}


void				read_prog_info(int fd, int prog_num, t_champ *champ_ptr)
{
	champ_ptr->player_num = prog_num;
	read_prog(fd, champ_ptr);
	read_prog_name_comment(fd, champ_ptr);
//	if (!check_magic(fd, champ_ptr))
//		ft_printf("Incorrect magic number for champion :\n");
}

void				read_files(int ac, char **av, t_champ *champ_head)
{
	int				ctr;
	int				fd;
	t_champ			*champ_ptr;

	champ_ptr = champ_head;
	ctr = 1;
	while (ctr < ac)
	{
		fd = open(av[ctr], O_RDONLY);
		if (fd < 0)
		{
			ft_printf("Unable to open file %s - exiting\n", av[ctr]);
			exit (0);
		}
		if (champ_ptr == NULL)
			champ_ptr = ft_memalloc(sizeof(t_champ));
		else
		{
			champ_ptr->next = ft_memalloc(sizeof(t_champ));
			champ_ptr = champ_ptr->next;
		}
		champ_ptr->next = NULL;
		read_prog_info(fd, (ctr - 1), champ_ptr);
		close(fd);
		ctr++;
	}
}

int				main(int argc, char **argv)
{
	t_champ		*champ_head;
	
	if (argc < 2 || argc > 5)
	{
		ft_printf("Usage: ./corewar <champ1.cor> <...>\n");
		return (0);
	}
	champ_head = NULL;	
	read_files(argc, argv, champ_head);
//	free_champs;
	return (0);
}
