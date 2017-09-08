/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 16:51:54 by hstander          #+#    #+#             */
/*   Updated: 2017/09/08 11:04:26 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm/headers/vm.h"

void		ft_zjmp(t_vm *vm, t_champ *champ)
{
	int				c_pc;
	int				arg1;
	int				temp1;
	int				temp2;

	ft_printf("zjmp old PC = %d\n", champ->pc);
	c_pc = champ->pc + 1;
	c_pc = mem_check(c_pc);
	champ->exec_cycle = g_op_tab[8].no_cycles;
	if (champ->carry == 1)
	{
		temp1 = (0x00ff & vm->mem[c_pc++]) * 256;
		c_pc = mem_check(c_pc);
		temp2 = (0x00ff & vm->mem[c_pc++]);
		c_pc = mem_check(c_pc);
		arg1 = temp1 + temp2;
		arg1 = to_signed_int(arg1, 16);
		ft_printf("zjmp arg1 = %d\n", arg1);
		champ->pc = mem_check(champ->pc + (arg1 % IDX_MOD));
		ft_printf("zjmp new PC = %d\n", champ->pc);
	}
	else
		champ->pc = mem_check(champ->pc + 3);
}
