/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_offset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 10:33:24 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/19 11:05:27 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Counts the number of bytes each argument takes, and modifies the bytes
**	variable inside the struct to the total. This value will be used to
**	calculate the offset between different labels.
**
**	Variable ctr starts at 1, as lst-data[0] will always be an opcode which
**	takes 1 byte.
**
**	Variable tot_bytes starts at 1, as the opcode is already taken into account
*/
void			label_offset(t_prog *lst)
{
	int			ctr;
	int			tot_bytes;

	tot_bytes = 1;
	while (lst)
	{
		ctr = 1;
		if (ft_strcmp(lst->data[0], "live") == 0)
		{
			tot_bytes += 4;
		}
		while (lst->data[ctr])
		{
			if (lst->data[ctr][0] == 'r')
				tot_bytes += 1;
			else if (lst->data[ctr][0] == '%')
				tot_bytes += 2;
			else
				tot_bytes += 4;
			ctr++;
		}
		lst->bytes = tot_bytes;
		lst = lst->next;
	}
}
