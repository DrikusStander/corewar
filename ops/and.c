/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 16:51:54 by hstander          #+#    #+#             */
/*   Updated: 2017/09/08 12:14:38 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm/headers/vm.h"

int			ft_direct(t_vm *vm, int *c_pc)
{
	int		arg;

	arg = (((0x00ff & vm->mem[*c_pc]) * 256) * 256) * 256;
	*c_pc = mem_check(*c_pc + 1);
	arg += (((0x00ff & vm->mem[*c_pc]) * 256) * 256);
	*c_pc = mem_check(*c_pc + 1);
	arg += ((0x00ff & vm->mem[*c_pc]) * 256);
	*c_pc = mem_check(*c_pc + 1);
	arg += (0x00ff & vm->mem[*c_pc]);
	*c_pc = mem_check(*c_pc + 1);
	arg = to_signed_int(arg, 16);
	return (arg);
}

int			ft_indirect(t_vm *vm, int *c_pc)
{
	int		arg;

	arg = ((0x00ff & vm->mem[*c_pc]) * 256);
	*c_pc = mem_check(*c_pc + 1);
	arg += (0x00ff & vm->mem[*c_pc]);
	*c_pc = mem_check(*c_pc + 1);
	arg = to_signed_int(arg, 16);
	return (arg);
}

int			ft_reg(t_vm *vm, int *c_pc, t_champ *champ)
{
	int		arg;

	arg = vm->mem[*c_pc];
	*c_pc = mem_check(*c_pc + 1);
	arg = champ->reg[arg];
	return (arg);
}

static int	ft_get_arg(t_vm *vm, int *c_pc, unsigned char dec, t_champ *champ)
{
	int		arg1;

	if (dec == 1)
		arg1 = ft_reg(vm, c_pc, champ);
	else if (dec == 2)
	{
		arg1 = ft_direct(vm, c_pc);
		arg1 = to_signed_int(arg1, 16);
	}
	else
	{
		arg1 = ft_indirect(vm, c_pc);
		arg1 = vm->mem[mem_check(champ->pc + (arg1 % IDX_MOD))];
	}
	return (arg1);
}

void		ft_and(t_vm *vm, t_champ *champ)
{
	int				c_pc;
	unsigned char	dec[4];
	int				arg1;
	int				arg2;
	int				arg3;

	c_pc = mem_check(champ->pc + 1);
	champ->exec_cycle = g_op_tab[5].no_cycles;
	ft_decode(vm->mem[c_pc++], dec);
	c_pc = mem_check(c_pc);
	arg1 = ft_get_arg(vm, &c_pc, dec[0], champ);
	arg2 = ft_get_arg(vm, &c_pc, dec[1], champ);
	arg3 = vm->mem[c_pc++];
	c_pc = mem_check(c_pc);
	if ((champ->reg[arg3] = arg1 & arg2))
		champ->carry = 0;
	else
		champ->carry = 1;
	champ->pc = c_pc;
}
