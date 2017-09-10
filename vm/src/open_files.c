/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 16:17:54 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/09/10 14:20:05 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vm.h"

int					get_next_player_number(t_champ *champ_head)
{
	int				ctr;
	t_champ			*champ_ptr;
	int				flag;

	ctr = 1;
	champ_ptr = champ_head;
	while (ctr <= 4)
	{
		flag = 1;
		while (champ_ptr)
		{
			if (ctr == champ_ptr->player_num)
				flag = 0;
			champ_ptr = champ_ptr->next;
		}
		if (flag)
			break ;
		ctr++;
		champ_ptr = champ_head;
	}
	return (ctr);
}

int					check_availible_num(t_champ *champ_head, int nbr)
{
	t_champ			*champ_ptr;

	champ_ptr = champ_head;
	while (champ_ptr)
	{
		if (champ_ptr->player_num == nbr)
		{
			ft_printf("Player number %i already in use -", nbr);
			ft_printf(" system generating a new one\n");
			return (1);
		}
		champ_ptr = champ_ptr->next;
	}
	return (0);
}

/*
**	Tries to open files passed as arguments to main. If successfull
**	mallocs space for a new champion, and call read function which
**	reads the file info into the champion struct.
*/

void				open_files(int ac, char **av, t_champ *champ_head, t_vm *vm)
{
	int				ctr;
	int				fd;
	t_champ			*champ_ptr;
	int				p_num;

	ctr = 1;
	vm->dump_cycle = 0;
	p_num = 0;
	champ_head->player_num = 0;
	champ_ptr = champ_head;
	while (ctr < ac)
	{
		if (ft_strcmp(av[ctr], "-dump") == 0)
		{
			if ((ctr + 1) < ac)
				vm->dump_cycle = ft_atoi(av[ctr + 1]);
			ctr += 2;
			continue ;
		}
		if (ft_strcmp(av[ctr], "-n") == 0)
		{
			if ((ctr + 1) < ac)
			{
				p_num = ft_atoi(av[ctr + 1]);
				if (p_num < 1 || p_num > 4)
				{
					ft_printf("Invalid player number %i - number", p_num);
					ft_printf(" must be between 1 and 4. A player number ");
					ft_printf("will be system generated\n");
					p_num = get_next_player_number(champ_head);
				}
				else if (check_availible_num(champ_head, p_num))
					p_num = get_next_player_number(champ_head);
			}
			ctr += 2;
			continue ;
		}
		if (p_num == 0)
			p_num = get_next_player_number(champ_head);
		if ((fd = open(av[ctr], O_RDONLY)) < 0)
		{
			ft_printf("Unable to open file %s - exiting\n", av[ctr]);
			free_structs(&champ_head, &vm);
			exit(0);
		}
		read_champ(fd, p_num, champ_ptr, vm, champ_head);
		p_num = 0;
		close(fd);
		ctr++;
		if (ctr < ac && (ft_strcmp(av[ctr], "-dump") != 0 || (ctr + 2) < ac))
		{
			champ_ptr->next = ft_memalloc(sizeof(t_champ));
			champ_ptr = champ_ptr->next;
		}
		champ_ptr->next = NULL;
	}
}
