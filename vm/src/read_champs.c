/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 13:19:44 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/09/10 13:27:02 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vm.h"

/*
**  Reads the info from file into the champion struct. Calls check magic
**  number func for a valid magic number, and checks the file size of the
**  champion that is does not exceed maximum size. Initialises program
**  carry, pc, registers and next executable cycle.
*/

void                read_champ(int fd, int prog_num, t_champ *champ_ptr,
		t_vm *vm, t_champ *champ_head)
{
	int             ctr;

	ctr = 2;
	read(fd, (void *)&champ_ptr->head.magic, 4);
	champ_ptr->head.magic = swop_bytes(champ_ptr->head.magic, 4);
	if (champ_ptr->head.magic != COREWAR_EXEC_MAGIC)
	{
		ft_printf("\nInvalid file magic number for %s - exiting\n",
				champ_ptr->head.prog_name);
		free_structs(&champ_head, &vm);
		exit (0);
	}
	champ_ptr->player_num = prog_num;
	read(fd, champ_ptr->head.prog_name, PROG_NAME_LENGTH);
	lseek(fd, 136, SEEK_SET);
	read(fd, (void *)&champ_ptr->head.prog_size, 4);
	champ_ptr->head.prog_size = swop_bytes(champ_ptr->head.prog_size, 4);
	if (champ_ptr->head.prog_size > CHAMP_MAX_SIZE ||
			champ_ptr->head.prog_size == 0)
	{
		if (champ_ptr->head.prog_size > CHAMP_MAX_SIZE)
			ft_printf("\n** Program size too big for champion %s - exiting **\n\n",
					champ_ptr->head.prog_name);
		else
			ft_printf("\n** No program code for champion %s - exiting **\n\n",
					champ_ptr->head.prog_name);
		free_structs(&champ_head, &vm);
		exit (0);
	}
	read(fd, champ_ptr->head.comment, COMMENT_LENGTH);
	lseek(fd, 2192, SEEK_SET);
	read(fd, champ_ptr->prog, champ_ptr->head.prog_size);
	champ_ptr->alive = 1;
	champ_ptr->called_alive = 0;
	champ_ptr->carry = 0;
	champ_ptr->pc = 0;
	champ_ptr->reg[1] = champ_ptr->player_num;
	while (ctr < 17)
	{
		champ_ptr->reg[ctr] = 0;
		ctr++;
	}
	champ_ptr->exec_cycle = 0;
}
