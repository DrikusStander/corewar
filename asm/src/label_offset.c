/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_offset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 10:33:24 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/21 10:41:47 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/asm.h"

/*
**	Counts the number of bytes each argument takes, and modifies the bytes
**	variable inside the struct to the total. This value will be used to
**	calculate the offset between different labels.
*/
int				label_offset(t_prog *lst, t_size *size_head)
{
	int			ctr;
	int			tot_bytes;
	t_size		*size_ptr;

	tot_bytes = 0;
	size_ptr = size_head;
	while (lst)
	{
		ctr = 0;
		if (lst->label)
		{
			if (size_ptr == NULL)
				size_ptr = ft_memalloc(sizeof(t_size));
			else
			{
				size_ptr->next = ft_memalloc(sizeof(t_size));
				size_ptr = size_ptr->next;
			}
			size_ptr->label = ft_strdup(lst->label);
			ft_printf("label :%s\n", size_ptr->label);
			size_ptr->offset = tot_bytes;
			ft_printf("offse :%i\n", size_ptr->offset);
		}
		if (lst->data)
		{
			
			while (lst->data[ctr])
			{
				if (ft_strcmp(lst->data[ctr], "live") == 0)
				{
					tot_bytes += 5;
					ft_printf("live :added 5\n");
					ctr += 2;
					continue ;
				}
				else if (ctr == 0)
				{
					ctr++;
					tot_bytes++;
				}
				
				if (lst->data[ctr][0] == 'r')
				{
					tot_bytes += 1;
					ft_printf("r :added 1\n");
				}
				else if (lst->data[ctr][0] == '%')
				{
					tot_bytes += 2;
					ft_printf("per :added 2\n");
				}
				else
				{
					tot_bytes += 4;
					ft_printf("indi :added 4\n");
				}
				ctr++;
			}
		}
		lst->bytes = tot_bytes;
		lst = lst->next;
	}
	size_ptr->next = NULL;
	return (tot_bytes);
}
