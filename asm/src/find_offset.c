/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_offset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 15:21:05 by hstander          #+#    #+#             */
/*   Updated: 2017/08/24 14:05:37 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/asm.h"

/*
** loops through the list to find the offset of the current label, then loops 
** through the list again to find the offset of the label that was called,
** then returns the result of the first minus the second.
*/
int		get_label_offset(char *sub, t_args *ag)
{
	int		arg_param;
	t_prog	*head;

	head = ag->head;
	arg_param = 0;
	while (head)
	{
		if (head->label)
		{
			if (ft_strncmp(head->label, ag->cur_label,
						ft_strlen(ag->cur_label)) == 0)
			{
				ft_printf("head->label =%s cur->label =%s\n", head->label, ag->cur_label);
				arg_param += head->bytes;
			}
		}
		head = head->next;
	}
	head = ag->head;
	while (head)
	{
	
		if (head->label)
			if (ft_strncmp(head->label, sub, ft_strlen(sub)) == 0)
				break ;
		head = head->next;
	}
	arg_param = (arg_param - head->bytes) * -1;
	ft_printf("%d\n", arg_param);
	return (arg_param);
}
