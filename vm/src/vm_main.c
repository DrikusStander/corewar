/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 08:34:55 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/09/04 08:13:17 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vm.h"

void				free_structs(t_champ **head, t_vm **vm)
{
	t_champ			*champ_temp;

	while (*head)
	{
		champ_temp = (*head)->next;
		free(*head);
		*head = champ_temp;
	}
	free(*vm);
}


int					count_flags(int argc, char **argv)
{
	int				ret;

	ret = 0;
	argc--;
	while (argc > 0)
	{
		if (ft_strcmp(argv[argc], "-n") == 0)
			ret += 2;
		else if (ft_strcmp(argv[argc], "-dump") == 0)
			ret += 2;
		argc--;
	}
	return (ret);
}


int					main(int argc, char **argv)
{
	t_champ			*champ_head;
	t_vm			*vm;

	if (argc < 2 || (argc - count_flags(argc, argv)) > MAX_PLAYERS + 1)
	{
		ft_printf("Usage with max %i champs: ./corewar <champ1.cor> <...>\n",
				MAX_PLAYERS);
		ft_printf("    -dump <nbr_cycles> - dumps memory after nbr_cycles\n");
		ft_printf("    -n <player_nbr> - assigns the next player player_nbr\n");
		return (0);
	}
	champ_head = ft_memalloc(sizeof(t_champ));
	vm = ft_memalloc(sizeof(t_vm));
	open_files(argc, argv, champ_head, vm);
	init_vm(vm, champ_head, (argc - count_flags(argc, argv)));

	print_vm(*vm);
	t_champ			*champ_ptr = champ_head;
/*	while (champ_ptr)
	{
		print_champ(champ_ptr);
		ft_printf("\n");
		champ_ptr = champ_ptr->next;
	}

*/	run_machine_run(champ_head, vm);
	champ_ptr = champ_head;
	while (champ_ptr)
	{
		print_champ(champ_ptr);
		ft_printf("\n");
		champ_ptr = champ_ptr->next;
	}
	print_vm(*vm);
	free_structs(&champ_head, &vm);	
	if (vm->last_live != 0)
		ft_printf("Player %i won\n", vm->last_live);
	else
		ft_printf("No live calls\n");
	return (0);
}
