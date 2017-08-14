/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 10:21:51 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/13 15:12:43 by gvan-roo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/asm.h"

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
			ft_printf("Champion name\n");
		else if (ft_strncmp(trim_str, ".comment", 8) == 0)
			ft_printf("Champion description\n");
		else
			ft_printf("Compiler instruction\n");
	}
	else if (trim_str[0] == '#')
		ft_printf("Comment\n");
	else if (trim_str[0])
		ft_printf("Label or instruction\n");
	else
		ft_printf("Empty line\n");
	ft_printf("%s\n\n", trim_str);
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
**	If arguments are correct, tries to open the file and return fd if successfull.
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
