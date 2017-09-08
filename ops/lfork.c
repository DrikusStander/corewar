/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 16:51:54 by hstander          #+#    #+#             */
/*   Updated: 2017/09/08 11:05:29 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm/headers/vm.h"

void		ft_lfork(t_vm *vm, t_champ *champ)
{
	int				c_pc;
	int				arg1;
	int				temp1;
	int				temp2;
	t_champ			*new_champ;

	ft_printf("lfork start pc = %d\n", champ->pc);
	new_champ = (t_champ *)ft_memalloc(sizeof(t_champ));
	c_pc = champ->pc + 1;
	c_pc = mem_check(c_pc);
	champ->exec_cycle = g_op_tab[14].no_cycles;
	temp1 = (0x00ff & vm->mem[c_pc++]) * 256;
	c_pc = mem_check(c_pc);
	temp2 = (0x00ff & vm->mem[c_pc++]);
	c_pc = mem_check(c_pc);
	arg1 = temp1 + temp2;
	arg1 = to_signed_int(arg1, 16);
	if (arg1 == 0)
		champ->carry = 1;
	else
		champ->carry = 0;
	init_champ(champ, new_champ);
	new_champ->pc = mem_check(champ->pc + arg1);
	champ->pc = c_pc;
	ft_printf("lforki end pc = %d\n", champ->pc);
	while (champ->next)
		champ = champ->next;
	champ->next = new_champ;
}
