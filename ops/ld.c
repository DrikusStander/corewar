/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 09:06:17 by chgreen           #+#    #+#             */
/*   Updated: 2017/09/07 09:38:06 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm/headers/vm.h"

static void	inc_pc(t_champ *champ)
{
	champ->pc = mem_check(champ->pc);
	champ->pc++;
	champ->pc = mem_check(champ->pc);
}

/*
**Fetches 2 bytes if indirect val
*/

static int	indirect(t_champ *champ, t_vm *vm)
{
	unsigned char	bytes[2];
	int				i;
	int				tmp;

	i = 0;
	while (i < 2)
	{
		bytes[i] = vm->mem[champ->pc];
		i++;
		inc_pc(champ);
	}
	tmp = ((0x00ff & bytes[0]) * 256);
	tmp += ((0x00ff & bytes[1]));
	return (tmp);
}

/*
**Fetches 4 bytes if direct val
*/

static int	direct(t_champ *champ, t_vm *vm)
{
	int				tmp;
	unsigned char	byte[4];

	byte[0] = vm->mem[champ->pc];
	inc_pc(champ);
	byte[1] = vm->mem[champ->pc];
	inc_pc(champ);
	byte[2] = vm->mem[champ->pc];
	inc_pc(champ);
	byte[3] = vm->mem[champ->pc];
	inc_pc(champ);
	tmp = (0x00ff & byte[0]) * 256 * 256 * 256;
	tmp += ((0x00ff & byte[1]) * 256 * 256);
	tmp += ((0x00ff & byte[2]) * 256);
	tmp += ((0x00ff & byte[3]));
	return (tmp);
}

/*
**Fetches bytes from vm memory
**decodes encoding byte
**Sets register value accordingly
**sets exec_cycle
*/

void		ft_ld(t_vm *vm, t_champ *champ)
{
	unsigned char	dec[4];
	int				val;
	int				temp;

	inc_pc(champ);
	ft_decode(vm->mem[champ->pc], dec);
	inc_pc(champ);
	if (dec[0] == 2)
	{
		val = direct(champ, vm);
		champ->reg[vm->mem[champ->pc]] = val;
	}
	else
	{
		val = indirect(champ, vm);
		temp = vm->mem[mem_check(champ->pc + (val % IDX_MOD))];
		champ->reg[vm->mem[champ->pc]] = temp;
	}
	if (champ->reg[vm->mem[champ->pc]] == 0)
		champ->carry = 1;
	else
		champ->carry = 0;
	champ->exec_cycle += 5;
	inc_pc(champ);
}
