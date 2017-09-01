/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 09:06:17 by chgreen           #+#    #+#             */
/*   Updated: 2017/09/01 07:53:36 by chgreen          ###   ########.fr       */
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
	int				pc;

	pc = champ->pc;
	byte[0] = vm->mem[pc];
	pc++;
	byte[1] = vm->mem[pc];
	pc++;
	byte[2] = vm->mem[pc];
	pc++;
	byte[3] = vm->mem[pc];
	tmp = (0x00ff & byte[0]) * 256 * 256 * 256;
	tmp += ((0x00ff & byte[1]) * 256 * 256);
	tmp += ((0x00ff & byte[2]) * 256);
	tmp += ((0x00ff & byte[3]));
	champ->pc = pc;
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
	unsigned char	enc;
	unsigned char	dec[4];
	int				val;

	champ->pc++;
	enc = vm->mem[champ->pc];
	champ->pc++;
	ft_decode(enc, dec);
	if (dec[0] == 2)
	{
		val = direct(champ, vm);
		champ->pc++;
		champ->reg[vm->mem[champ->pc]] = val;
	}
	else
	{
		val = indirect(champ, vm);
		champ->reg[vm->mem[champ->pc]] = vm->mem[champ->pc + (val % IDX_MOD)];
	}
	champ->exec_cycle += 5;
	champ->pc++;
}
