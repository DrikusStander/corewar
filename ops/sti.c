/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 16:51:54 by hstander          #+#    #+#             */
/*   Updated: 2017/09/05 08:37:13 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm/headers/vm.h"

void		ft_sti(t_vm *vm, t_champ *champ)
{
	int				c_pc;
	unsigned char	dec[4];
	unsigned int	acb;
	int				arg1;
	int				arg2;
	int				arg3;
	int 			temp1;
	int				temp2;

	c_pc = champ->pc + 1;
	c_pc = mem_check(c_pc);
	champ->exec_cycle = g_op_tab[10].no_cycles;
	acb = vm->mem[c_pc++];
	c_pc = mem_check(c_pc);
	ft_decode(acb, dec);
	arg1 = vm->mem[c_pc++];
	c_pc = mem_check(c_pc);
	if (dec[1] == 1)
	{
		arg2 = vm->mem[c_pc++];
		c_pc = mem_check(c_pc);
		arg2 = champ->reg[arg2];
	}
	else if (dec[1] == 2)
	{
		temp1 = (0x00ff & vm->mem[c_pc++]) * 256;
		c_pc = mem_check(c_pc);
		temp2 = (0x00ff & vm->mem[c_pc++]);
		c_pc = mem_check(c_pc);
		arg2 = temp1 + temp2;
	}
	else
	{
		temp1 = (0x00ff & vm->mem[c_pc++]) * 256;
		c_pc = mem_check(c_pc);
		temp2 = (0x00ff & vm->mem[c_pc++]);
		c_pc = mem_check(c_pc);
		arg2 = temp1 + temp2;
		arg2 = vm->mem[mem_check(champ->pc + (arg2 % IDX_MOD))];
	}
	if (dec[2] == 1)
	{
		arg3 = vm->mem[c_pc++];
		c_pc = mem_check(c_pc);
		arg3 = champ->reg[arg3];
	}
	else
	{
		temp1 = (0x00ff & vm->mem[c_pc++]) * 256;
		c_pc = mem_check(c_pc);
		temp2 = (0x00ff & vm->mem[c_pc++]);
		c_pc = mem_check(c_pc);
		arg3 = temp1 + temp2;
	}
	vm->mem[mem_check(champ->pc + ((arg2 + arg3) % IDX_MOD))] = champ->reg[(arg1 & 0xff000000) >> 24];
	vm->mem[mem_check((champ->pc + 1) + ((arg2 + arg3) % IDX_MOD))] = champ->reg[(arg1 & 0x00ff0000) >> 16];
	vm->mem[mem_check((champ->pc + 2) + ((arg2 + arg3) % IDX_MOD))] = champ->reg[(arg1 & 0x0000ff00) >> 8];
	vm->mem[mem_check((champ->pc + 3) + ((arg2 + arg3) % IDX_MOD))] = champ->reg[(arg1 & 0xff0000ff)];
	champ->pc = c_pc;
}
