/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 08:34:55 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/30 08:29:25 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vm.h"

int					main(int argc, char **argv)
{
	t_champ			*champ_head;
	t_vm			*vm;
	
	if (argc < 2 || argc > 5)
	{
		ft_printf("Usage with max %i champs: ./corewar <champ1.cor> <...>\n",
				MAX_PLAYERS);
		return (0);
	}
	champ_head = ft_memalloc(sizeof(t_champ));
	vm = ft_memalloc(sizeof(t_vm));
	open_files(argc, argv, champ_head);
	init_vm(vm, champ_head, argc);
	print_vm(*vm);

	t_champ			*champ_ptr = champ_head;
	while (champ_ptr)
	{
		print_champ(champ_ptr);
		ft_printf("\n");
		champ_ptr = champ_ptr->next;
	}

	run_machine_run(champ_head, vm);
//	free_champs;
	return (0);
}
