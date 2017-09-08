/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_machine_run.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 16:44:22 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/09/08 18:26:15 by gvan-roo         ###   ########.fr       */
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
		if (!champ_ptr->called_alive)
			champ_ptr->alive = 0;
		champ_ptr->called_alive = 0;
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
	champ_ptr->pc = mem_check(champ_ptr->pc);
	champ_ptr->exec_cycle += g_op_tab[0].no_cycles;
	p_num = vm->mem[mem_check(champ_ptr->pc)] * 256 * 256 * 256;
	p_num += vm->mem[mem_check(champ_ptr->pc + 1)] * 256 * 256;
	p_num += vm->mem[mem_check(champ_ptr->pc + 2)] * 256;
	p_num += vm->mem[mem_check(champ_ptr->pc + 3)];
	champ_ptr->pc = mem_check(champ_ptr->pc + 4);
	champ_ptr->called_alive = 1;
	champ_ptr = champ_head;
	while (champ_ptr)
	{
		if (champ_ptr->player_num == p_num)
		{
//			ft_printf("A process shows that player %i (%s) is alive\n",
//					champ_ptr->player_num, champ_ptr->head.prog_name);
			vm->last_live = champ_ptr->player_num;
			vm->live_calls++;
		}
		champ_ptr = champ_ptr->next;
	}
}

void			exec_champ(t_champ *champ_head, t_champ *champ_ptr, t_vm *vm)
{
	if (vm->mem[champ_ptr->pc] == 1)
	{
		call_live(champ_head, champ_ptr, vm);
	}
	else if (vm->mem[champ_ptr->pc] >= 2 && vm->mem[champ_ptr->pc] <= 16)
	{
		vm->func[vm->mem[champ_ptr->pc]](vm, champ_ptr);
	}
	else
	{
		champ_ptr->exec_cycle++;
	}
}

void			run_machine_run(t_champ *champ_head, t_vm *vm)
{
	t_champ		*champ_ptr;
	while (check_who_alive(champ_head))
	{
		while (vm->cur_cycle < vm->cycle_to_die)
		{
			if (vm->dump_cycle != 0 && vm->total_cycles >= vm->dump_cycle)
			{
				endwin();
				champ_ptr = champ_head;
				 while (champ_ptr)
				{
				     print_champ(champ_ptr);
				     ft_printf("\n");
				     champ_ptr = champ_ptr->next;
				}
				print_memory((void *)&vm->mem, MEM_SIZE, 64);
				free_structs(&champ_head, &vm);
				exit(0);
			}
//			ft_printf("----------------->total cycles: %i\n", vm->total_cycles);
//			ft_printf("----------------->cur_cycle: %i\n", vm->cur_cycle);
//			ft_printf("----------------->live calls: %i\n", vm->live_calls);
//			ft_printf("----------------->checks: %i\n", vm->checks);
//			ft_printf("----------------->cycle to die: %i\n", vm->cycle_to_die);
			champ_ptr = champ_head;
			while (champ_ptr)
			{
				if (champ_ptr->alive && !champ_ptr->exec_cycle)
				{
					exec_champ(champ_head, champ_ptr, vm);
				}
				if (champ_ptr->exec_cycle)
					champ_ptr->exec_cycle--;
				champ_ptr = champ_ptr->next;
			}
//			print_vm(*vm, 64);
			print_vm_nc(*vm, 64);
			vm->cur_cycle++;
			vm->total_cycles++;
		}
		new_cycle_to_die(champ_head, vm);
	}
}
