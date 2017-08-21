/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 10:21:51 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/21 13:10:50 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/asm.h"

void		ft_initstr(t_args *ag)
{
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
	ft_initstr(ag);
}

void		ft_writename(t_args *ag, int bytes)
{
	swap_bytes(COREWAR_EXEC_MAGIC, ag->fd);
	write(ag->fd, &ag->header->prog_name, (PROG_NAME_LENGTH + 4));
	swap_bytes(bytes, ag->fd);
	write(ag->fd, &ag->header->comment, (COMMENT_LENGTH + 4));
}

void		ft_readfile(t_args *ag)
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
		ag->line	= NULL;
	}
	close(ag->fd);
}


int			main(int argc, char **argv)
{
	t_prog	*head;
	t_args	ag;
	t_func	fc;

	ft_bzero(&ag, sizeof(t_args));
	ag.header = (header_t *)ft_memalloc(sizeof(header_t));
	head = NULL;
	ag.fd = check_arguments(&ag, argc, argv);
	ft_readfile(&ag);
	
	ag.fd = open(ag.file_name, O_WRONLY | O_TRUNC | O_CREAT , 0666);
	ft_init(&ag, &fc);


	
	int i = 0;
	int j = 0;
	int bytes;
	t_prog *lst;
	lst = ag.head;
	bytes = label_offset(lst);
	ft_writename(&ag, bytes);

	while (lst)
	{
		i = 0;
		if (lst->label)
			ft_printf("%s\n", lst->label);
		j = 0;
		if (lst->data)
		{
			while (j < 16)
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
			ft_printf("%s\n", lst->data[i]);
			i++;
		}
		lst = lst->next;
	}
	ft_free_all(&ag);
	close(ag.fd);
	return (0);
}
