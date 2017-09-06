/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 16:17:54 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/09/04 11:34:05 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vm.h"

/*
**	Reads the info from file into the champion struct. Calls check magic
**	number func for a valid magic number, and checks the file size of the
**	champion that is does not exceed maximum size. Initialises program
**	carry, pc, registers and next executable cycle.
*/

void				read_champ(int fd, int prog_num, t_champ *champ_ptr,
		t_vm *vm, t_champ *champ_head)
{
	int				ctr;

	ctr = 2;
	read(fd, (void *)&champ_ptr->head.magic, 4);
	if (!check_key((void *)&champ_ptr->head.magic, 4))
	{
		ft_printf("\nInvalid file magic number for %s - exiting\n",
				champ_ptr->head.prog_name);
		free_structs(&champ_head, &vm);
		exit (0);
	}
	champ_ptr->head.magic = swop_bytes(champ_ptr->head.magic, 4);
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
			ft_printf("Player number %i already in use - system generating a new one\n", nbr);
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
					ft_printf("Invalid player number %i - number must be between 1 and 4. A player number will be system generated\n", p_num);
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
		fd = open(av[ctr], O_RDONLY);
		if (fd < 0)
		{
			ft_printf("Unable to open file %s - exiting\n", av[ctr]);
			free_structs(&champ_head, &vm);
			exit (0);
		}
		read_champ(fd, p_num, champ_ptr, vm, champ_head);
		p_num = 0;
		close(fd);
		ctr++;
		if (ctr < ac)
		{
			champ_ptr->next = ft_memalloc(sizeof(t_champ));
			champ_ptr = champ_ptr->next;
		}
		champ_ptr->next = NULL;
	}
}
