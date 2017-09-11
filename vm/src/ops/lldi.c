/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 16:51:54 by hstander          #+#    #+#             */
/*   Updated: 2017/09/10 13:05:17 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/vm.h"

static int	ft_s(int arg1, int arg2, t_vm *vm, int c_pc)
{
	int     arg;
	int     s;

	s = arg1 + arg2;
	arg = (((0x00ff & vm->mem[mem_check((c_pc + (s % IDX_MOD)))]) * 256) * 256) * 256;
	arg += (((0x00ff & vm->mem[mem_check(((c_pc + 1) + (s % IDX_MOD)))]) * 256) * 256);
	arg += ((0x00ff & vm->mem[mem_check(((c_pc + 2) + (s % IDX_MOD)))]) * 256);
	arg += (0x00ff & vm->mem[mem_check(((c_pc + 3) + (s % IDX_MOD)))]);
	return (arg);
}

static int	ft_get_arg(t_vm *vm, int *c_pc, unsigned char dec, t_champ *champ)
{
	int		arg1;
	int		temp;

	if (dec == 1)
		arg1 = ft_reg(vm, c_pc, champ);
	else if (dec == 2)
		arg1 = ft_indirect(vm, c_pc);
	else
	{
		arg1 = ft_indirect(vm, c_pc);
		temp = vm->mem[mem_check(champ->pc + arg1)] * 256;
		temp += vm->mem[mem_check((champ->pc + 1) + arg1)];
		temp = to_signed_int(temp, 16);
		arg1 = temp;
	}
	return (arg1);
}

void		ft_lldi(t_vm *vm, t_champ *champ)
{
	int				c_pc;
	unsigned char	dec[4];
	int				arg1;
	int				arg2;
	int				arg3;

	c_pc = mem_check(champ->pc + 1);
	champ->exec_cycle = g_op_tab[9].no_cycles;
	ft_decode(vm->mem[c_pc++], dec);
	c_pc = mem_check(c_pc);
	arg1 = ft_get_arg(vm, &c_pc, dec[0], champ);
	arg2 = ft_get_arg(vm, &c_pc, dec[1], champ);
	arg3 = vm->mem[c_pc++];
	c_pc = mem_check(c_pc);
	if ((champ->reg[arg3] = ft_s(arg1, arg2, vm, champ->pc)))
		champ->carry = 0;
	else
		champ->carry = 1;
	champ->pc = c_pc;
}