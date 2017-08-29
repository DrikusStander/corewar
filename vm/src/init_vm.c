/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 16:21:41 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/29 10:13:02 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vm.h"

/*
**	Function reads the champion program into the virtual machine memory
**	starting from offset bytes.
*/

void				alloc_champ_mem(t_vm *vm, t_champ *champ_ptr, int offset)
{
	unsigned int	ctr;

	ctr = 0;
	while (ctr < champ_ptr->head.prog_size)
	{
		vm->mem[offset] = champ_ptr->prog[ctr];
		offset++;
		ctr++;
	}
}

/*
**	Function initialised the struct virtual machine. The memory
**	is allocated by calling alloc_champ_mem, and the rest of the
**	vm values are allocated inside this function
*/

void				init_vm(t_vm *vm, t_champ *champ_head, int argc)
{
	t_champ			*champ_ptr;
	int				space;
	int				champ_offset;

	champ_ptr = champ_head;
	space = MEM_SIZE / (argc - 1);
	champ_offset = 0;
	ft_bzero(vm->mem, MEM_SIZE);
	while (champ_ptr)
	{
		alloc_champ_mem(vm, champ_ptr, champ_offset);
		champ_ptr->pc = champ_offset;
		champ_offset += space;
		champ_ptr = champ_ptr->next;
	}
	vm->cur_cycle = 1;
	vm->cycle_to_die = CYCLE_TO_DIE;
	vm->cycle_delta = CYCLE_DELTA;
	vm->live_calls = 0;
	vm->checks = 0;
	vm->last_live = 0;
}
