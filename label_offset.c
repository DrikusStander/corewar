/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_offset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 10:33:24 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/19 17:15:15 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/asm.h"

/*
**	Counts the number of bytes each argument takes, and modifies the bytes
**	variable inside the struct to the total. This value will be used to
**	calculate the offset between different labels.
**
**	Variable ctr starts at 1, as lst-data[0] will always be an opcode which
**	takes 1 byte.
*/
void			label_offset(t_prog *lst)
{
	int			ctr;
	int			tot_bytes;

	tot_bytes = 0;
	while (lst)
	{
		ctr = 0;
		if (lst->data)
		{
			while (lst->data[ctr])
			{
				if (ft_strcmp(lst->data[ctr], "live") == 0)
				{
					tot_bytes += 5;
					ctr += 2;
					continue ;
				}
				else if (ctr == 0)
				{
					ctr++;
					tot_bytes++;
				}
				if (lst->data[ctr][0] == 'r')
					tot_bytes += 1;
				else if (lst->data[ctr][0] == '%')
					tot_bytes += 2;
				else
					tot_bytes += 4;
				ctr++;
			}
		}
		lst->bytes = tot_bytes;
		lst = lst->next;
	}
}
