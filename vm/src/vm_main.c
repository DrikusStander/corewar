/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 08:34:55 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/20 15:29:42 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vm.h"
#include <stdio.h>

void		check_cor_header(int fd, void *head_buf, char *file_name)
{
	int		m_n;
	void	*magic_nbr;
	int i = 0;

	ft_printf("fd :%i\n", fd);
	if (ft_memcmp(head_buf, magic_nbr, 4) != 0)
	{
		ft_printf("Invalid magic number in header of %s - exiting\n", file_name);
		//free(head_buf);
		close(fd);
		exit (0);
	}
}

void		check_cor_files(int ac, char **av)
{
	int		ctr;
	int		fd;
	int		read_ret;
	void	*head_buf;

	ctr = 1;
	head_buf = malloc(sizeof(header_t));
	while (ctr <= ac)
	{
		fd = open(av[ctr], O_RDONLY);
		if (fd < 0)
		{
			ft_printf("Unable to open file %s - exiting\n", av[ctr]);
			free(head_buf);
			exit (0);
		}
		read_ret = read(fd, head_buf, sizeof(head_buf));
		check_cor_header(fd, head_buf, av[ctr]);
		ctr++;
	}
}


int			main(int argc, char **argv)
{
	if (argc < 2 || argc > 5)
	{
		ft_printf("Usage: ./corewar <champ1.cor> <...>\n");
		return (0);
	}
	check_cor_files(argc, argv);
	return (0);
}
