/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 10:21:51 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/15 09:45:13 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/asm.h"

/*
**	Checks whether line contains a label and if so sends to function processing label pointers
*/
void		parse_label_op(char *as_str)
{
	int		ctr;
	char	*label;
	char	*temp;

	ctr = 0;
	label = NULL;
	temp = NULL;
	while ((as_str[ctr] >= 'a' && as_str[ctr] <= 'z') || (as_str[ctr] >= '0' &&
		   as_str[ctr] <= '9') || as_str[ctr] == '_')
		ctr++;
	if (as_str[ctr] == ':')
	{
		label = ft_strsub(as_str, 0, ctr);
		temp = as_str;
		as_str = ft_strsub(as_str, (ctr + 1), (ft_strlen(as_str) - ctr));
		free(temp);
		temp = as_str;
		as_str = ft_strtrim(as_str);
		free(temp);
	}
	if (label)
		ft_printf("label  :%s\n", label);
	ft_printf("opcode :%s\n", as_str);
}
		

/*
**	Checks the line read from the file, and calls relevant function to process the line
*/
void		parse_line(char *as_str)
{
	char	*trim_str;

	trim_str = ft_strtrim(as_str);
	if (trim_str[0] == '.')
	{
		if (ft_strncmp(trim_str, ".name", 5) == 0)
		{
			ft_printf("Champion name\n");
			ft_printf("%s\n", trim_str);
		}
		else if (ft_strncmp(trim_str, ".comment", 8) == 0)
		{
			ft_printf("Champion description\n");
			ft_printf("%s\n", trim_str);
		}
		else
		{
			ft_printf("Compiler instruction\n");
			ft_printf("%s\n", trim_str);
		}
	}
	else if (trim_str[0] == '#')
	{
		ft_printf("Comment\n");
		ft_printf("%s\n", trim_str);
	}
	else if (trim_str[0])
		parse_label_op(trim_str);
	else
		ft_printf("Empty line\n");
}

/*
**	Checks that the last two chars in the file name is '.s'.
*/
int			check_valid_file(char *file_name)
{
	int		fn_len;

	fn_len = ft_strlen(file_name);
	if (file_name[fn_len - 1] != 's' || file_name[fn_len - 2] != '.')
		return (1);
	else
		return (0);
}

/*
**	Checks that correct number of arguments received, and that the passed argument ends with '.s'.
**	If arguments are correct, tries to open the file and returns fd if successfull.
*/
int			check_arguments(int argc, char **argv)
{
	int		fd;

	if (argc != 2)
	{
		ft_printf("Invalid number of arguments. Usage: ./asm mychampion.s\n");
		exit(0);
	}
	if (check_valid_file(argv[1]) != 0)
	{
		ft_printf("Invalid file - file must end with .s extension\n");
		exit(0);
	}
	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		perror("Error");
		exit(0);
	}
	return (fd);
}

int			main(int argc, char **argv)
{
	int		fd;
	char	*as_str;

	fd = check_arguments(argc, argv);
	as_str = NULL;
	while (get_next_line(fd, &as_str) > 0)
	{
		parse_line(as_str);
		if (as_str)
			free(as_str);
	}
	return (0);
}
