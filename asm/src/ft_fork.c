/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 08:19:21 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/24 08:59:49 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Swops the bits of an int from little endian to big endian
**	and prints to file the correct number of bytes
*/

static int			swop_int_bits(int fd, int i)
{
	i = ((i >> 8) && 0xFF) | ((i << 8) && 0xFF00);
	write(fd, (void *)&i, 2);
}

/*
**	Function to assemble op code fork. Takes a struct pointer to the current
**	opcode and its's data, and a pointer to a struct containing the fd to
**	write to. Function checks the arguments for validity. Then parses the value
**	gets the offset if a label and then writes to file.
*/

void			ft_fork(t_args *ag, t_prog *lst)
{
	char		*sub;
	int			arg_param;

	sub = NULL;
	arg_param = 0;
	if (lst->data[1][0] != '%' || lst->data[2])
	{
		ft_printf("Invalid arguments for fork - exiting fork function\n");
		return ;
	}
	if (lst->data[1][1] == ':')
	{
		sub = ft_strsub(lst->data[1], 2, (ft_strlen(lst->data[1] - 2)));
		arg_param = get_label_offset(sub, ag);
	}
	else
	{
		sub = ft_strsub(lst->data[1], 1, (ft_strlen(lst->data[1] - 1)));
		arg_param = ft_atoi(sub);
	}
	write(ag->fd, 12, 1);
	swop_int_bits(ag->fd, arg_param);
}
