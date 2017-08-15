/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 10:21:51 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/15 16:27:42 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/asm.h"

/*
 **	Checks the line read from the file, and calls relevant function to process the line
 */

void	swap_bytes(unsigned int i, int fd)
{
	unsigned char buf[4];
	buf[0] = (i & 0xff000000) >> 24;
	buf[1] = (i & 0x00ff0000) >> 16;
	buf[2] = (i & 0x0000ff00) >> 8;
	buf[3] = (i & 0x000000ff);
	write(fd, buf, sizeof(i));
}

void		parse_line(char *as_str, t_prog *head)
{
	char	*trim_str;
	char	**temp;
	t_prog	*lst;

	trim_str = ft_strtrim(as_str);
	if (trim_str[0] == '.')
	{
		if (ft_strncmp(trim_str, ".name", 5) == 0)
		{
			lst = ft_memalloc(sizeof(t_prog));
			lst->data = ft_strsplit(trim_str, '"');
			free(trim_str);
		}
		else if (ft_strncmp(trim_str, ".comment", 8) == 0)
		{
			lst = ft_memalloc(sizeof(t_prog));
			lst->data = ft_strsplit(trim_str, '"');

			free(trim_str);
		}
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

void		parse_list(char *as_str, int fd2, header_t *header/*, int fd, int offset*/)
{
	char	*trim_str;
	char	**temp;
	trim_str = ft_strtrim(as_str);
	if (trim_str[0] == '.')
	{
		if (ft_strncmp(trim_str, ".name", 5) == 0)
		{
			temp = ft_strsplit(trim_str, '"');
			free(trim_str);
			header->magic = COREWAR_EXEC_MAGIC;
			swap_bytes(header->magic, fd2);
			ft_strcpy(header->prog_name, temp[1]);
			write(fd2, temp[1], (PROG_NAME_LENGTH + 4));
		}
		else if (ft_strncmp(trim_str, ".comment", 8) == 0)
		{
			temp = ft_strsplit(trim_str, '"');
			free(trim_str);
			ft_strcpy(header->comment, temp[1]);
			swap_bytes(header->prog_size,fd2);
			write(fd2, temp[1], (COMMENT_LENGTH + 4));
		}
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
	int		fd2;
	int 	offset;
	header_t header;
	
	fd2 = open("test.s", O_WRONLY | O_TRUNC /*| O_CREAT , 0666*/);
	fd = check_arguments(argc, argv);
	header.prog_size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	as_str = NULL;
	while ((offset = get_next_line(fd, &as_str)) > 0)
	{
		parse_line(as_str, fd2, &header/*, fd, offset*/);
		if (as_str)
			free(as_str);
	}
	close(fd);
	return (0);
}
