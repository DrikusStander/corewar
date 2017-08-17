/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 10:21:51 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/17 14:13:16 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/asm.h"

/*
 * frees the linked list
*/
void	ft_freelst(t_prog *lst)
{
	t_prog *temp;

	while (lst)
	{
		temp = lst;
		lst = lst->next;
		free(temp);
	}
}

/*
 * gets the length 2D array
*/
size_t	ft_arrlen(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

/*
 * swaps bytes for BIG ENDIAN
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

/*
 * finds the first occurence of c in str and returns the index of where it was 
 * found, else it returns -1
*/
int		ft_chr_i(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

/*
 * Checks the line read from the file, and creates a linked list based on
 * the data.
 */
void		parse_line(char *as_str, t_prog **head)
{
	char	*trim_str;
	char	*tmp;
	int		i;
	t_prog	*lst;
	t_prog	*temp;
	char	**ref;
	char	**ref2;

	temp = *head;
	while (temp && temp->next)
		temp = temp->next;

	trim_str = ft_strtrim(as_str);
	if ((i = ft_chr_i(trim_str, '#')) > -1)
	{
		tmp = ft_strsub(trim_str, 0, i);
		free(trim_str);
		trim_str = tmp;
	}
	if (trim_str[0] == '.')
	{
		if (ft_strncmp(trim_str, ".name", 5) == 0)
		{
			lst = (t_prog *)ft_memalloc(sizeof(t_prog));
			lst->data = ft_strsplit(trim_str, '"');
			lst->next = NULL;
		}
		else if (ft_strncmp(trim_str, ".comment", 8) == 0)
		{
			lst = (t_prog *)ft_memalloc(sizeof(t_prog));
			lst->data = ft_strsplit(trim_str, '"');
			lst->next = NULL;
		}
		else
		{
			ft_printf("Invalid command %s\n", trim_str);
			exit(-1);
		}
	}
	else if (trim_str[0] == '#')
		return ;
	else if (trim_str[0])
	{
		int k = 0;
		int len ;
		int cnt = 0;
		lst = (t_prog *)ft_memalloc(sizeof(t_prog));
		if ((i = ft_chr_i(trim_str, ':')) > -1)
		{
			if (i > 0 && trim_str[i - 1] != '%')
			{
				lst->label = ft_strsub(trim_str, 0, i);
				if(*(trim_str + i + 1) != '\0')
				{
					ref = ft_strsplit(trim_str + i + 1, ',');
					ref2 = ft_split(ref[0], ' ');
					len = ft_arrlen(ref) + ft_arrlen(ref2);
					lst->data = (char **)ft_memalloc(sizeof(char *) * (len));
					while (ref2[cnt])
					{
						lst->data[k] = ft_strdup(ref2[cnt]);
						k++;
						cnt++;
					}
					cnt = 1;
					while (ref[cnt])
					{
						lst->data[k] = ft_strdup(ref[cnt]);
						k++;
						cnt++;
					}
					lst->data[k] = NULL;
					lst->next = NULL;
					free_2d(&ref);
					free_2d(&ref2);
				}
				else
					lst->data = NULL;
			}
			else
			{
				lst->label = NULL;
				ref = ft_strsplit(trim_str, ',');
				ref2 = ft_split(ref[0], ' ');
				len = ft_arrlen(ref) + ft_arrlen(ref2);
				lst->data = (char **)ft_memalloc(sizeof(char *) * (len));
				while (ref2[cnt])
				{
					lst->data[k] = ft_strdup(ref2[cnt]);
					k++;
					cnt++;
				}
				cnt = 1;
				while (ref[cnt])
				{
					lst->data[k] = ft_strdup(ref[cnt]);
					k++;
					cnt++;
				}
				lst->data[k] = NULL;
				lst->next = NULL;
				free_2d(&ref);
				free_2d(&ref2);
			}
		}
		else
		{
			k = 0;
			ref = ft_strsplit(trim_str, ',');
			ref2 = ft_split(ref[0], ' ');
			len = ft_arrlen(ref) + ft_arrlen(ref2);
			lst->data = (char **)ft_memalloc(sizeof(char *) * (len));
		while (ref2[cnt])
			{
				lst->data[k] = ft_strdup(ref2[cnt]);
				k++;
				cnt++;
			}
			cnt = 1;
			while (ref[cnt])
			{
				lst->data[k] = ft_strdup(ref[cnt]);
				k++;
				cnt++;
			}
			lst->data[k] = NULL;
			lst->next = NULL;
			free_2d(&ref);
			free_2d(&ref2);
		}
		ft_printf("Label or instruction\n");
	}
	else
	{
		free(trim_str);
		return ;
	}
	if (*head)
		temp->next = lst;
	else
		*head = lst;
	ft_printf("%s\n\n", trim_str);
	free(trim_str);
}

/*
void		parse_list(char *as_str, int fd2, header_t *header)
{
	char	*trim_str;
	char	**temp;
	trim_str = ft_strtrim(as_str);
	if (trim_str[0] == '.')
	{
		if (ft_strncmp(trim_str, ".name", 5) == 0)
		{
			temp = ft_strsplit(trim_str, '"');
			header->magic = COREWAR_EXEC_MAGIC;
			swap_bytes(header->magic, fd2);
			ft_strcpy(header->prog_name, temp[1]);
			write(fd2, temp[1], (PROG_NAME_LENGTH + 4));
		}
		else if (ft_strncmp(trim_str, ".comment", 8) == 0)
		{
			temp = ft_strsplit(trim_str, '"');
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
*/

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
 * Checks that correct number of arguments received, and that the passed 
 * argument ends with '.s'.
 * If arguments are correct, tries to open the file and return fd 
 * if successfull.
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
	t_prog	*head;

	head = NULL;
	fd2 = open("test.cor", O_WRONLY | O_TRUNC | O_CREAT , 0666);
	fd = check_arguments(argc, argv);
	header.prog_size = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	as_str = NULL;
	while ((offset = get_next_line(fd, &as_str)) > 0)
	{
		parse_line(as_str, &head);
		if (as_str)
		{
			free(as_str);
			as_str = NULL;
		}
	}
	if (as_str)
		{
			free(as_str);
			as_str = NULL;
		}

	int i = 0;
	t_prog *lst;
	lst = head;
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
	ft_freelst(head);
	close(fd);
	return (0);
}
