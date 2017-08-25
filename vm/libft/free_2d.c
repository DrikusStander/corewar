/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/28 11:09:23 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/07/28 11:15:08 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				free_2d(char ***array)
{
	int				ctr;

	if (!(*array))
		return ;
	ctr = 0;
	while ((*array) && (*array)[ctr])
	{
		free((*array)[ctr]);
		ctr++;
	}
	if ((*array))
		free((*array));
}
