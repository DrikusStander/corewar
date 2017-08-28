/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 16:17:54 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/28 16:19:10 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vm.h"

/*
**	Reads the info from file into the champion struct. Calls check magic
**	number func for a valid magic number, and checks the file size of the
**	champion that is does not exceed maximum size. Initialises program
**	carry, pc, registers and next executable cycle.
*/

void				read_champ(int fd, int prog_num, t_champ *champ_ptr)
{
	int				ctr;

	ctr = 2;
	read(fd, (void *)&champ_ptr->head.magic, 4);
	if (!check_key((void *)&champ_ptr->head.magic, 4))
		ft_printf("\nInvalid file magic number\n");
	champ_ptr->head.magic = swop_bytes(champ_ptr->head.magic, 4);
	champ_ptr->player_num = prog_num;
	read(fd, champ_ptr->head.prog_name, PROG_NAME_LENGTH);
	lseek(fd, 136, SEEK_SET);
	read(fd, (void *)&champ_ptr->head.prog_size, 4);
	champ_ptr->head.prog_size = swop_bytes(champ_ptr->head.prog_size, 4);
	if (champ_ptr->head.prog_size > CHAMP_MAX_SIZE)
	{
		ft_printf("\n**** Program size too big for champion %s ****\n\n",
				champ_ptr->head.prog_name);
	}
	read(fd, champ_ptr->head.comment, COMMENT_LENGTH);
	lseek(fd, 2192, SEEK_SET);
	read(fd, champ_ptr->prog, champ_ptr->head.prog_size);
	champ_ptr->nbr_live = 0;
	champ_ptr->calls_without_live = 0;
	champ_ptr->alive = 1;
	champ_ptr->carry = 0;
	champ_ptr->pc = 0;
	champ_ptr->reg[1] = champ_ptr->player_num;
	while (ctr < 17)
	{
		champ_ptr->reg[ctr] = 0;
		ctr++;
	}
	champ_ptr->exec_cycle = 1;
}

/*
**	Tries to open files passed as arguments to main. If successfull
**	mallocs space for a new champion, and call read function which
**	reads the file info into the champion struct.
*/

void				open_files(int ac, char **av, t_champ *champ_ptr)
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
		read_champ(fd, ctr, champ_ptr);
		close(fd);
		ctr++;
		if (ctr < ac)
		{
			champ_ptr->next = ft_memalloc(sizeof(t_champ));
			champ_ptr = champ_ptr->next;
		}
		champ_ptr->next = NULL;
	}
}
