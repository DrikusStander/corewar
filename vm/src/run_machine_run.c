/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_machine_run.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 16:44:22 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/29 15:42:36 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vm.h"


int				check_who_alive(t_champ *champ_head)
{
	t_champ		*champ_ptr;

	champ_ptr = champ_head;
	while (champ_ptr)
	{
		if (champ_ptr->alive)
			return (1);
		champ_ptr = champ_ptr->next;
	}
	return (0);
}


void			new_cycle_to_die(t_champ *champ_head, t_vm *vm)
{
	t_champ		*champ_ptr;

	champ_ptr = champ_head;
	while (champ_ptr)
	{
		champ_ptr->alive = 0;
		champ_ptr = champ_ptr->next;
	}
	if (vm->live_calls >= NBR_LIVE || vm->checks >= 10)
	{
		vm->cycle_to_die -= vm->cycle_delta;
		vm->checks = 0;
	}
	else
		vm->checks++;
	vm->live_calls = 0;
	vm->cur_cycle = 1;
}


void			call_live(t_champ *champ_head, t_champ *champ_ptr, t_vm *vm)
{
	int			p_num;
	int			ctr;

	ctr = 0;
	champ_ptr->pc++;
	while (ctr < 4)
	{
		(void *)&p_num[ctr] = (void *)&vm->mem[champ_ptr->pc];
		champ_ptr->pc++;
		ctr++;
	}
	p_num = swop_bytes(p_num, 4);
	champ_ptr = champ_head;
	while (champ_ptr)
	{
		if (champ_ptr->player_num == p_num)
		{
			champ_ptr->alive = 1;
			ft_printf("A process shows that player %i: (%s) is alive",
					champ_ptr->player_num, champ_ptr->head.prog_name);
		}
		champ_ptr = champ_ptr->next;
	}
}


void			exec_champ(t_champ *champ_ptr, t_vm *vm)
{
	if (vm->mem[champ_ptr->pc] == 1)
		call_live(champ_ptr, vm);
	else if (vm->mem[champ_ptr->pc] >= 2 && vm->mem[champ_ptr->pc] <= 16)
		func[vm->mem[champ_ptr->pc]](champ_ptr, vm);
}

void			run_machine_run(t_champ *champ_head, t_vm *vm)
{
	t_champ		*champ_ptr;

	while (check_who_alive(champ_head))
	{
		new_cycle_to_die(champ_head, vm);
		while (vm->cur_cycle <= vm->cycle_to_die)
		{
			champ_ptr = champ_head;
			while (champ_ptr)
			{
				if (champ_ptr->alive && !champ_ptr->exec_cycle)
					exec_champ(champ_ptr, vm);
				champ_ptr->exec_cycle--;
				champ_ptr = champ_ptr->next;
			}
			vm->cur_cycle++;
		}
	}
}
