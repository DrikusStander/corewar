/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 16:51:54 by hstander          #+#    #+#             */
/*   Updated: 2017/08/30 17:32:16 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm/headers/vm.h"

void		ft_and(t_vm *vm, t_champ *champ)
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
	champ->exec_cycle = g_op_tab[5].no_cycles;
	acb = vm->mem[c_pc++];
	ft_decode(acb, dec);
	if (dec[0] == 1)
	{
		arg1 = vm->mem[c_pc++];
		arg1 = champ->reg[arg1];
	}
	else if (dec[0] == 2)
	{
		temp1 = (((0x00ff & vm->mem[c_pc++]) * 256) * 256) *256;
		temp2 = ((0x00ff & vm->mem[c_pc++]) * 256) * 256;
		arg1 = temp1 + temp2;
		temp1 = (0x00ff & vm->mem[c_pc++]) * 256;
		temp2 = (0x00ff & vm->mem[c_pc++]);
		arg1 = temp1 + temp2;
	}
	else
	{
		temp1 = (0x00ff & vm->mem[c_pc++]) * 256;
		temp2 = (0x00ff & vm->mem[c_pc++]);
		arg1 = temp1 + temp2;
		arg1 = vm->mem[champ->pc + (arg1 % IDX_MOD)];
	}
	if (dec[1] == 1)
	{
		arg2 = vm->mem[c_pc++];
		arg2 = champ->reg[arg2];
	}
	else if (dec[1] == 2)
	{
		temp1 = (((0x00ff & vm->mem[c_pc++]) * 256) * 256) *256;
		temp2 = ((0x00ff & vm->mem[c_pc++]) * 256) * 256;
		arg2 = temp1 + temp2;
		temp1 = (0x00ff & vm->mem[c_pc++]) * 256;
		temp2 = (0x00ff & vm->mem[c_pc++]);
		arg2 = temp1 + temp2;
	}
	else
	{
		temp1 = (0x00ff & vm->mem[c_pc++]) * 256;
		temp2 = (0x00ff & vm->mem[c_pc++]);
		arg2 = temp1 + temp2;
		arg2 = vm->mem[champ->pc + (arg2 % IDX_MOD)];
	}
	arg3 = vm->mem[c_pc++];
	champ->reg[arg3] = arg1 & arg2;	
	champ->pc = c_pc;
}
