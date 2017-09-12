/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chgreen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 13:11:12 by chgreen           #+#    #+#             */
/*   Updated: 2017/09/12 11:30:37 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/vm.h"

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
	tmp = to_signed_ind(bytes);
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
	inc_pc(champ);
	tmp = to_signed_dir(byte);
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
	unsigned char	tmp[2];

	temp = champ->pc;
	inc_pc(champ);
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
		tmp[0] = vm->mem[mem_check(temp + val)];
		tmp[1] = vm->mem[mem_check((temp + 1) + val)];
		temp2 = to_signed_ind(tmp);
		champ->reg[vm->mem[champ->pc]] = temp2;
	}
	if (champ->reg[vm->mem[champ->pc]])
		champ->carry = 0;
	else
		champ->carry = 1;
	champ->exec_cycle += 10;
	inc_pc(champ);
}
