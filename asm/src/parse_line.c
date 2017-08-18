/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 11:07:51 by hstander          #+#    #+#             */
/*   Updated: 2017/08/18 11:08:53 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/asm.h"

/*
 * Checks the line read from the file, and creates a linked list based on
 * the data.
 */
void	parse_line(t_args *ag)
{
	char	*tmp;
	int		i;

	ag->trim_str = ft_strtrim(ag->line);
	if ((i = ft_chr_i(ag->trim_str, '#')) > -1)
	{
		tmp = ft_strsub(ag->trim_str, 0, i);
		free(ag->trim_str);
		ag->trim_str = tmp;
	}
	if (ag->trim_str[0] == '.')
		ft_nm_com(ag);
	else if (ag->trim_str[0])
		ft_lbl_com(ag);
	else
	{
		free(ag->trim_str);
		return ;
	}
	ft_setlist(ag);
	ft_printf("%s\n", ag->trim_str);
	free(ag->trim_str);
}
