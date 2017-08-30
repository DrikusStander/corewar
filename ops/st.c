/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 16:51:54 by hstander          #+#    #+#             */
/*   Updated: 2017/08/30 12:23:13 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm/headers/vm.h"
#include <stdio.h>

void		ft_decode(unsigned int i, unsigned char *buf)
{
	buf[0] = (i & 0b11000000) >> 6;
	buf[1] = (i & 0b00110000) >> 4;
	buf[2] = (i & 0b00001100) >> 2;
	buf[3] = (i & 0b00000011);
}

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
	champ->exec_cycle = g_op_tab[2].no_cycles;
	acb = vm->mem[c_pc++];
	ft_decode(acb, dec);
	arg1 = vm->mem[c_pc++];
	if (dec[1] == 1)
	{
		arg2 = vm->mem[c_pc++];
		champ->reg[arg2] = champ->reg[arg1];
	}
	else
	{
		temp1 = (0x00ff & vm->mem[c_pc++]) * 256;
		temp2 = (0x00ff & vm->mem[c_pc++]);
		arg2 = temp1 + temp2;
		vm->mem[champ->pc + (arg2 % IDX_MOD)] = champ->reg[arg1];
	}
	champ->pc = c_pc;
}

