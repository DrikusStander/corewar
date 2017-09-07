/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 08:34:55 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/09/07 10:28:11 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vm.h"

/*
**	Frees all malloced champion structs and the malloced vm
*/

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

/*
**	Counts the number of flag arguments
*/

int					count_flags(int argc, char **argv)
{
	int				ret;
	int				arg_count;

	ret = 0;
	argc--;
	arg_count = argc;
	while (argc > 0)
	{
		if (ft_strcmp(argv[argc], "-n") == 0)
		{
			if ((arg_count >= argc + 1) && (ft_atoi(argv[argc + 1]) == 0))
			{
				ft_printf("-n usage: -n <player_number> - exiting\n");
				exit (0);
			}
			ret += 2;
		}
		else if (ft_strcmp(argv[argc], "-dump") == 0)
		{
			if ((arg_count >= argc + 1) && (ft_atoi(argv[argc + 1]) == 0))
			{
				ft_printf("-dump usage: -dump <num_cycles> - exiting\n");
				exit (0);
			}
			ret += 2;
		}
		argc--;
	}
	return (ret);
}

/*
**	Finds the struct with the last live call (if any) and prints 
**	out the winner
*/

void				find_winner_struct(t_champ *champ_head, int ll)
{
	t_champ			*champ_ptr;

	if (ll == 0)
	{
		ft_printf("No live calls\n");
		return ;
	}
	champ_ptr = champ_head;
	while (champ_ptr && champ_ptr->player_num != ll)
		champ_ptr = champ_ptr->next;
	ft_printf("Player %i (%s) is the winner\n", champ_ptr->player_num,
			champ_ptr->head.prog_name);
}

/*
**	Reverses the champion list as last player plays first
*/

void				reverse_list(t_champ **champ_head)
{
	t_champ			*champ_ptr;
	t_champ			*new_head;

	new_head = *champ_head;
	while (new_head->next)
		new_head = new_head->next;
	while (1)
	{
		champ_ptr = *champ_head;
		while (champ_ptr->next && champ_ptr->next->next)
			champ_ptr = champ_ptr->next;
		if (champ_ptr == *champ_head)
		{
			if (champ_ptr->next)
				champ_ptr->next->next = champ_ptr;
			champ_ptr->next = NULL;
			break ;
		}
		champ_ptr->next->next = champ_ptr;
		champ_ptr->next = NULL;
	}
	*champ_head = new_head;
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

//	print_vm(*vm, 64);
	t_champ			*champ_ptr = champ_head;
/*	while (champ_ptr)
	{
		print_champ(champ_ptr);
		ft_printf("\n");
		champ_ptr = champ_ptr->next;
	}
*/	reverse_list(&champ_head);
	run_machine_run(champ_head, vm);
	
	champ_ptr = champ_head;
/*	while (champ_ptr)
	{
		print_champ(champ_ptr);
		ft_printf("\n");
		champ_ptr = champ_ptr->next;
	}
	print_vm(*vm, 64);
*/	find_winner_struct(champ_head, vm->last_live);
	free_structs(&champ_head, &vm);	
//	print_vm(*vm, 64);
	getch();
	endwin();
	while (champ_ptr)
	{
		print_champ(champ_ptr);
		ft_printf("\n");
		champ_ptr = champ_ptr->next;
	}
	return (0);
}
