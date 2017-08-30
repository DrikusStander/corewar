/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 16:51:54 by hstander          #+#    #+#             */
/*   Updated: 2017/08/30 10:14:44 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm/headers/vm.h"
#include <stdio.h>

void		ft_decode(unsigned int i, unsigned char *buf)
{
	buf[0] = (i & 0xff000000) >> 24;
	buf[1] = (i & 0x00ff0000) >> 16;
	buf[2] = (i & 0x0000ff00) >> 8;
	buf[3] = (i & 0x000000ff);
}

void		ft_st(t_vm *vm, t_champ *champ)
{
	int				c_pc;
	unsigned char	dec[4];
	unsigned int	acb;
	int i = 0;

	c_pc = champ->pc + 1;
	champ->exec_cycle = g_op_tab[2].no_cycles;
	acb = vm->mem[c_pc];
	ft_decode(acb, dec);
	while (i < 4)
	{
		printf("---------->%d", dec[i]);
		i++;


	}
}

