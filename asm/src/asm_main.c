/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 10:21:51 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/18 15:25:24 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/asm.h"



void		ft_init(t_args *ag, t_func *fc)
{
	ag->f_str = (char **)ft_memalloc(sizeof(char *) * 17);
	fc->func[0] = &ft_lfork;
	fc->func[1] = &ft_sti;
	fc->func[2] = &ft_fork;
	fc->func[3] = &ft_lld;
	fc->func[4] = &ft_ld;
	fc->func[5] = &ft_add;
	fc->func[6] = &ft_zjmp;
	fc->func[7] = &ft_sub;
	fc->func[8] = &ft_ldi;
	fc->func[9] = &ft_or;
	fc->func[10] = &ft_st;
	fc->func[11] = &ft_aff;
	fc->func[12] = &ft_live;
	fc->func[13] = &ft_xor;
	fc->func[14] = &ft_lldi;
	fc->func[15] = &ft_and;
	ag->f_str[0] = ft_strdup("lfork");
	ag->f_str[1] = ft_strdup("sti");
	ag->f_str[2] = ft_strdup("fork");
	ag->f_str[3] = ft_strdup("lld");
	ag->f_str[4] = ft_strdup("ld");
	ag->f_str[5] = ft_strdup("add");
	ag->f_str[6] = ft_strdup("zjmp");
	ag->f_str[7] = ft_strdup("sub");
	ag->f_str[8] = ft_strdup("ldi");
	ag->f_str[9] = ft_strdup("or");
	ag->f_str[10] = ft_strdup("st");
	ag->f_str[11] = ft_strdup("aff");
	ag->f_str[12] = ft_strdup("live");
	ag->f_str[13] = ft_strdup("xor");
	ag->f_str[14] = ft_strdup("lldi");
	ag->f_str[15] = ft_strdup("and");
}

int			main(int argc, char **argv)
{
	int		fd;
	t_prog	*head;
	t_args	ag;
	t_func	fc;

	ft_bzero(&ag, sizeof(t_args));
	ag.header = (header_t *)ft_memalloc(sizeof(header_t));
	head = NULL;
	fd = check_arguments(argc, argv);
	while (get_next_line(fd, &ag.line) > 0)
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
	close(fd);
	ag.fd = open("test.cor", O_WRONLY | O_TRUNC | O_CREAT , 0666);
	ft_init(&ag, &fc);


	
	int i = 0;
	int j = 0;
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
		j = 0;
		if (lst->data)
		{
			while (j < 15)
			{
				if (ft_strcmp(ag.f_str[j], lst->data[0]) == 0)
				{
					ft_printf("===============\n");
					fc.func[j](&ag, lst);
					ft_printf("===============\n");
					break ;
				}
				j++;
			}
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
	ft_printf("name:\n%s\n", ag.header->prog_name);
	ft_printf("comment:\n%s\n", ag.header->comment);

	ft_freelst(ag.head);
	close(ag.fd);
	return (0);
}
