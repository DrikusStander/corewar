/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 08:34:55 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/26 16:20:47 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vm.h"

void				read_prog(int fd, t_champ *champ_ptr)
{
	int 			ctr;

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
	unsigned char	*int_buf;

	int_buf = ft_memalloc(sizeof(int));
	ft_bzero(int_buf, sizeof(int));
	ft_bzero(champ_ptr->head.prog_name, (PROG_NAME_LENGTH + 1));
	lseek(fd, 4, SEEK_SET);
	read(fd, champ_ptr->head.prog_name, PROG_NAME_LENGTH);
	lseek(fd, 136, SEEK_SET);
	read(fd, (void *)&champ_ptr->head.prog_size, 4);
	champ_ptr->head.prog_size = ((champ_ptr->head.prog_size>> 24) & 0xFF)
		| ((champ_ptr->head.prog_size >> 8) & 0xFF00)
		| ((champ_ptr->head.prog_size < 8) & 0xFF0000)
		| ((champ_ptr->head.prog_size << 24) & 0xFF0000);
	if (champ_ptr->head.prog_size > CHAMP_MAX_SIZE)
	{
		ft_printf("\n**** Program size to big for champion %s ****\n\n",
				champ_ptr->head.prog_name);
	}
	read(fd, champ_ptr->head.comment, COMMENT_LENGTH);
}


void				read_prog_info(int fd, int prog_num, t_champ *champ_ptr)
{
	champ_ptr->player_num = prog_num;
	read_prog(fd, champ_ptr);
	read_prog_name_comment(fd, champ_ptr);
//	if (!check_magic(fd, champ_ptr))
//		ft_printf("Incorrect magic number for champion :\n");
	ft_printf("Player num :%i\n", champ_ptr->player_num);
	ft_printf("Program name :%s\n", champ_ptr->head.prog_name);
	ft_printf("Prog size :%i\n", champ_ptr->head.prog_size);
	ft_printf("Prog comment :%s\n", champ_ptr->head.comment);

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
		read_prog_info(fd, ctr, champ_ptr);
		ft_printf("\n");
		close(fd);
		ctr++;
	}
}

int				main(int argc, char **argv)
{
	t_champ		*champ_head;
	
	if (argc < 2 || argc > 5)
	{
		ft_printf("Usage with max %i champs: ./corewar <champ1.cor> <...>\n",
				MAX_PLAYERS);
		return (0);
	}
	champ_head = NULL;	
	read_files(argc, argv, champ_head);
//	free_champs;
	return (0);
}
