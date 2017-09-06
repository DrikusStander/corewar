/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 09:06:17 by chgreen           #+#    #+#             */
/*   Updated: 2017/09/05 16:58:46 by hstander         ###   ########.fr       */
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
	unsigned char	enc;
	unsigned char	dec[4];
	int				val;
	int				tmp;
	int 			c_pc;

	c_pc = champ->pc;
	tmp = 0;
	inc_pc(champ);
	enc = vm->mem[champ->pc];
	inc_pc(champ);
	ft_decode(enc, dec);
	if (dec[0] == 2)
	{
		val = direct(champ, vm);
		inc_pc(champ);
		champ->reg[vm->mem[champ->pc]] = val;
	}
	else
	{
		val = indirect(champ, vm);
		val = to_signed_int(val, 16);
		tmp	+= (vm->mem[mem_check(c_pc + (val % IDX_MOD))]) * 256;
		tmp	+= (vm->mem[mem_check(c_pc + 1 + (val % IDX_MOD))]);
		champ->reg[vm->mem[champ->pc]] = tmp; 
	}
	champ->exec_cycle += 5;
	if (champ->reg[vm->mem[champ->pc]] == 0)
			champ->carry = 1;
		else
			champ->carry = 0;
//	champ->carry = (champ->carry == 0 ? 1 : 0);
	inc_pc(champ);
}
