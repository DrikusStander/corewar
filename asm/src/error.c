/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 10:14:58 by hstander          #+#    #+#             */
/*   Updated: 2017/08/28 15:56:10 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/asm.h"

void	delete_cor(int error, t_args *ag)
{
	remove(ag->file_name);
	ft_printf_fd(2, "Aborting...\n");
	exit(error);
}

void	my_error(int error, t_args *ag)
{
	if (error == 1)
		ft_printf_fd(2, "Invalid register\n");
	if (error == 2)
		ft_printf("Invalid argument\n");
	if (error == 3)
		ft_printf_fd(2, "Unable to write to file\n");
	if (error == 4)
		ft_printf_fd(2, "Incorrect amount of arguements\n");
	if (error == 5)
		ft_printf_fd(2, "Non terminated string:\n%s\n", ag->trim_str);
	if (error == 6)
		ft_printf_fd(2, "Invalid Label\n");
	if (error == 7)
		ft_printf_fd(2, "Invalid op code\n");
	delete_cor(error, ag);
}
