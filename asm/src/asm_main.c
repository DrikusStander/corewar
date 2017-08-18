/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 10:21:51 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/18 11:10:43 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/asm.h"

int			main(int argc, char **argv)
{
	int		fd;
	int		fd2;
	int 	offset;
	header_t header;
	t_prog	*head;
	t_args	ag;

	ft_bzero(&ag, sizeof(t_args));
	head = NULL;
	fd2 = open("test.cor", O_WRONLY | O_TRUNC | O_CREAT , 0666);
	fd = check_arguments(argc, argv);
	header.prog_size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	while ((offset = get_next_line(fd, &ag.line)) > 0)
	{
		parse_line(&ag);
		if (ag.line)
		{
			free(ag.line);
			ag.line = NULL;
		}
	}
	if (ag.line)
		{
			free(ag.line);
			ag.line	= NULL;
		}
	int i = 0;
	t_prog *lst;
	lst = ag.head;
	while (lst)
	{
		i = 0;
		ft_printf("-------------\n");
		if (lst->label)
		{
			ft_printf("-->%s\n", lst->label);
			free(lst->label);
		}
		while (lst->data && lst->data[i])
		{
			ft_printf("-->%s\n", lst->data[i]);
			free(lst->data[i]);
			i++;
		}
		if (lst->data)
			free(lst->data);
		lst = lst->next;
	}
	ft_printf("-------------\n");
	ft_freelst(ag.head);
	close(fd);
	return (0);
}
