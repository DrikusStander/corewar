/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_untils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 11:45:26 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/09/10 12:50:29 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vm.h"

/*
 **  Frees all malloced champion structs and the malloced vm
 */

void                free_structs(t_champ **head, t_vm **vm)
{
	t_champ         *champ_temp;

	while (*head)
	{
		champ_temp = (*head)->next;
		free(*head);
		*head = champ_temp;
	}
	free(*vm);
}

/*
**  Swops the bytes of a passed argument int
*/

int                 swop_bytes(int i, int no_bytes)
{
	if (no_bytes == 4)
	{
		i = (i >> 24 & 0xFF) | (i >> 8 & 0xFF00) |
			(i << 8 & 0xFF0000) | (i << 24 & 0xFF0000);
	}
	return (i);
}
