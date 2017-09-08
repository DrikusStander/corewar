/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 13:11:12 by chgreen           #+#    #+#             */
/*   Updated: 2017/09/08 11:29:24 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm/headers/vm.h"

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
		champ->pc++;
		champ->pc = mem_check(champ->pc);
	}
	tmp = ((0x00ff & bytes[0]) * 256);
	tmp += ((0x00ff & bytes[1]));
	return (tmp);
}

static void	inc_pc(t_champ *champ)
{
	champ->pc = mem_check(champ->pc);
	champ->pc++;
	champ->pc = mem_check(champ->pc);
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

void		ft_lld(t_vm *vm, t_champ *champ)
{
	unsigned char	dec[4];
	int				val;
	int				temp;
	int				temp2;

	temp = champ->pc;
	inc_pc(champ);
	inc_pc(champ);
	ft_decode(vm->mem[champ->pc], dec);
	inc_pc(champ);
	if (dec[0] == 2)
	{
		val = direct(champ, vm);
		val = to_signed_int(val, 16);
		inc_pc(champ);
		champ->reg[vm->mem[champ->pc]] = val;
	}
	else
	{
		val = indirect(champ, vm);
		val = to_signed_int(val, 16);
		temp2 = vm->mem[mem_check(temp + (val % IDX_MOD))] * 256;
		temp2 += vm->mem[mem_check((temp + 1) + (val % IDX_MOD))];
		champ->reg[vm->mem[champ->pc]] = temp2;
	}
	if (champ->reg[vm->mem[champ->pc]])
		champ->carry = 0;
	else
		champ->carry = 1;
	champ->exec_cycle += 10;
	inc_pc(champ);
}
