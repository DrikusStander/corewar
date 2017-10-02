/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_vm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 15:46:38 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/09/26 16:15:16 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vm.h"

void	check_dump_cycle(t_champ *champ_head, t_vm *vm)
{
	if (vm->dump_cycle != 0 && vm->total_cycles >= vm->dump_cycle)
	{
		endwin();
		print_memory((void *)&vm->mem, MEM_SIZE, 64);
		free_structs(&champ_head, &vm);
		exit(0);
	}
}

void	init_ncurses(int ncurses)
{
	if (ncurses == 1)
	{
		initscr();
		start_color();
		init_color(COLOR_WHITE, 400, 400, 400);
		init_color(COLOR_GREEN, 0, 600, 0);
		init_pair(0, COLOR_WHITE, COLOR_BLACK);
		init_pair(1, COLOR_BLUE, COLOR_BLACK);
		init_pair(2, COLOR_RED, COLOR_BLACK);
		init_pair(3, COLOR_GREEN, COLOR_BLACK);
		init_pair(4, COLOR_CYAN, COLOR_BLACK);
	}
}

void	end_ncurses(int ncurses)
{
	if (ncurses == 1)
	{
		getch();
		endwin();
	}
}

void	print_ifno_nc(t_vm *vm, t_champ *champ)
{
	if (vm->ncurses == 0)
	{
		ft_printf("A process shows that player %i (%s) is alive\n",
				champ->player_num, champ->head.prog_name);
	}
}
