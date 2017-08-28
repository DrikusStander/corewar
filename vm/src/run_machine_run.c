/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_machine_run.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 16:44:22 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/28 17:52:19 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vm.h"

void			exec_champ(t_champ champ_ptr, t_vm vm)
{
}


void			check_if_alive(t_champ champ_ptr, int check_nbr_live)
{
	if (check_nbr_live)
	{
		if (champ_ptr->nbr_live < NBR_LIVE)
			champ_ptr->alive = 0;
	}
	if (champ_ptr->calls_without_live < MAX_CHECKS)
		champ_ptr->alive = 0;
}

void			run_machine_run(t_champ *champ_head, t_vm *vm)
{
	t_champ		*champ_ptr;

	while (vm->cycle_to_die > 0)
	{
		vm->cur_cycle = 1;
		while (vm->cur_cycle < vm->cycle_to_die)
		{
			champ_ptr = champ_head;
			while (champ_ptr)
			{
				check_if_alive(champ_ptr, 0);
				if (champ_ptr->alive)
					exec_champ(champ_ptr, vm);
				champ_ptr = champ_ptr->next;
			}
			vm->cur_cycle++;
		}
		vm->cycle_to_die -= vm->cycle_delta;
		check_if_alive(champ_ptr, 1);
	}
}
