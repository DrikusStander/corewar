/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extras.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 12:56:02 by hstander          #+#    #+#             */
/*   Updated: 2017/09/01 11:33:40 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm/headers/vm.h"

int to_signed_int(unsigned int value, int bitLength)
{
	int signed_value;

	signed_value = value;
	if (value >> (bitLength - 1))
		signed_value |= -1 << bitLength;
	return (signed_value);
}

void        ft_decode(unsigned int i, unsigned char *buf)
{
	buf[0] = (i & 0b11000000) >> 6;
	buf[1] = (i & 0b00110000) >> 4;
	buf[2] = (i & 0b00001100) >> 2;
	buf[3] = (i & 0b00000011);
}

int         mem_check(int pc)
{
	return (pc % MEM_SIZE);
}

void        init_champ(t_champ *champ, t_champ *new_champ)
{
	int     i;

	i = 0;
	new_champ->player_num = champ->player_num;
	new_champ->head = champ->head;
	while (champ->prog[i])
	{
		new_champ->prog[i] = champ->prog[i];
		i++;
	}
	new_champ->alive = champ->alive;
	new_champ->called_alive = champ->called_alive;
	new_champ->carry = champ->carry;
	new_champ->exec_cycle = champ->exec_cycle;
	new_champ->next = NULL;
	i = 0;
	while (i < 17)
	{
		new_champ->reg[i] = champ->reg[i];
		i++;
	}
}
