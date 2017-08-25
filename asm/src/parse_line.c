/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 11:07:51 by hstander          #+#    #+#             */
/*   Updated: 2017/08/25 14:57:46 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/asm.h"

/*
** void		ft_readfile(t_args *ag);
** reads the input file line by line passing each line to the parse line
** function.
*/

void	ft_readfile(t_args *ag)
{
	while (get_next_line(ag->fd, &ag->line) > 0)
	{
		parse_line(ag);
		if (ag->line)
		{
			free(ag->line);
			ag->line = NULL;
		}
	}
	if (ag->line)
	{
		free(ag->line);
		ag->line = NULL;
	}
	close(ag->fd);
}

/*
** void   parse_line(t_args *ag);
** Checks the line read from the file, and creates a linked list based on
** the data.
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
	else if ((i = ft_chr_i(ag->trim_str, ';')) > -1)
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
//	ft_printf("%s\n", ag->trim_str);
	free(ag->trim_str);
}
