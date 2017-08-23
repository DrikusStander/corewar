/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 10:21:51 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/23 10:26:07 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/asm.h"

/*
** writes magic number, program name, program size and program comments to the
** binary file.
*/

void		ft_writename(t_args *ag)
{
	swap_bytes(COREWAR_EXEC_MAGIC, ag->fd);
	write(ag->fd, &ag->header->prog_name, (PROG_NAME_LENGTH + 4));
	swap_bytes(ag->header->prog_size, ag->fd);
	write(ag->fd, &ag->header->comment, (COMMENT_LENGTH + 4));
}

/*
** iterates through the list and calls the relevant function according to the op
*/

void		ft_list_iter(t_args *ag)
{
	t_prog	*lst;
	int		i;

	lst = ag->head;
	i = 0;
	while (lst)
	{
		i = 0;
		if (lst->label)
			ag->cur_label = lst->label;
		if (lst->data != NULL)
		{
			while (i < 16)
			{
				if (ft_strcmp(ag->f_str[i], lst->data[0]) == 0)
				{
					ag->func[i](ag, lst);
					break ;
				}
				i++;
			}
		}
		lst = lst->next;
	}
}

void		temp_print(t_args *ag)
{
	int		i; 
	t_prog	*lst;

	lst = ag->head;	
	i = 0;
	while (lst)
	{
		i = 0;
		if (lst->label)
			ft_printf("%s\n", lst->label);
		while (lst->data && lst->data[i])
		{
			ft_printf("%s\n", lst->data[i]);
			i++;
		}
		lst = lst->next;
	}
	ft_printf("bytes :%i\n", ag->header->prog_size);
}

int			main(int argc, char **argv)
{
	t_args	ag;
	t_prog	*lst;

	ft_bzero(&ag, sizeof(t_args));
	ag.header = (header_t *)ft_memalloc(sizeof(header_t));
	ag.fd = check_arguments(&ag, argc, argv);
	ft_readfile(&ag);
	ag.fd = open(ag.file_name, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	ft_init(&ag);
	lst = ag.head;
	ag.header->prog_size = label_offset(lst);
	ft_writename(&ag);
	ft_list_iter(&ag);

	temp_print(&ag);

	ft_free_all(&ag);
	close(ag.fd);
	return (0);
}
