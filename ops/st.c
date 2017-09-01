/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 16:51:54 by hstander          #+#    #+#             */
/*   Updated: 2017/09/01 08:57:49 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm/headers/vm.h"

void		ft_st(t_vm *vm, t_champ *champ)
{
	int				c_pc;
	unsigned char	dec[4];
	unsigned int	acb;
	int				arg1;
	int				arg2;
	int 			temp1;
	int				temp2;

	c_pc = champ->pc + 1;
	c_pc = mem_check(c_pc);
	champ->exec_cycle = g_op_tab[2].no_cycles;
	acb = vm->mem[c_pc++];
	ft_decode(acb, dec);
	c_pc = mem_check(c_pc);
	arg1 = vm->mem[c_pc++];
	c_pc = mem_check(c_pc);
	if (dec[1] == 1)
	{
		arg2 = vm->mem[c_pc++];
		c_pc = mem_check(c_pc);
		champ->reg[arg2] = champ->reg[arg1];
	}
	else
	{
		temp1 = (0x00ff & vm->mem[c_pc++]) * 256;
		c_pc = mem_check(c_pc);
		temp2 = (0x00ff & vm->mem[c_pc++]);
		c_pc = mem_check(c_pc);
		arg2 = temp1 + temp2;
		arg2 = to_signed_int(arg2, 16);
		vm->mem[mem_check(champ->pc + (arg2 % IDX_MOD))] = champ->reg[arg1];
	}
	champ->pc = c_pc;
}

