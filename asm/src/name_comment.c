/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_comment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/21 15:13:23 by hstander          #+#    #+#             */
/*   Updated: 2017/08/21 15:16:31 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/asm.h"

/*
** saves the name of the program to the header struct if it passes all the
** tests.
*/

void	ft_name(t_args *ag, int i)
{
	int		j;
	char	*temp;

	if ((j = ft_chrn_i(ag->trim_str, '"')) > i)
	{
		temp = ft_strsub(ag->trim_str, (i + 1), (j - i - 1));
		if (ft_strlen(temp) > PROG_NAME_LENGTH)
		{
			ft_printf("Name to big:\n%s\n", ag->trim_str);
			free(temp);
			exit(-1);
		}
		ft_strcpy(ag->header->prog_name, temp);
		free(temp);
	}
	else
	{
		ft_printf("Non terminated string:\n%s\n", ag->trim_str);
		exit(-1);
	}
}

/*
** saves the comment of the program to the header struct if it passes all the
** tests.
*/

void	ft_comment(t_args *ag, int i)
{
	int		j;
	char	*temp;

	if ((j = ft_chrn_i(ag->trim_str, '"')) > i)
	{
		temp = ft_strsub(ag->trim_str, (i + 1), (j - i - 1));
		if (ft_strlen(temp) > COMMENT_LENGTH)
		{
			ft_printf("comment to big:\n%s\n", ag->trim_str);
			free(temp);
			exit(-1);
		}
		ft_strcpy(ag->header->comment, temp);
		free(temp);
	}
	else
	{
		ft_printf("Non terminated string:\n%s\n", ag->trim_str);
		exit(-1);
	}
}

/*
** prints a error message depending on the input integer.
*/

int		ft_exit_nmcm(t_args *ag, int i)
{
	if (i == -1)
		ft_printf("Invalid name:\n%s\n", ag->trim_str);
	if (i == -2)
		ft_printf("Invalid comment:\n%s\n", ag->trim_str);
	if (i == -3)
		ft_printf("Invalid command %s\n", ag->trim_str);
	return (i);
}

/*
** if a line starts with a '.' it checks if the line is the program name or the
** program comments, and calls the relevant function to save the name or
** comment into the header struct.
*/

void	ft_nm_com(t_args *ag)
{
	int		i;

	if (ft_strncmp(ag->trim_str, ".name", 5) == 0)
	{
		if ((i = ft_chr_i(ag->trim_str, '"')) > -1)
			ft_name(ag, i);
		else
			exit(ft_exit_nmcm(ag, -1));
	}
	else if (ft_strncmp(ag->trim_str, ".comment", 8) == 0)
	{
		if ((i = ft_chr_i(ag->trim_str, '"')) > -1)
			ft_comment(ag, i);
		else
			exit(ft_exit_nmcm(ag, -2));
	}
	else
		exit(ft_exit_nmcm(ag, -3));
}
