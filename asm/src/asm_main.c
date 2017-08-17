/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 10:21:51 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/17 18:10:33 by hstander         ###   ########.fr       */
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
 * if a line starts with a '.' it checks if the line is the program name or the
 * program comments, and saves it into a list item
*/
void	ft_nm_com(t_args *ag)
{
	if (ft_strncmp(ag->trim_str, ".name", 5) == 0)
	{
		ag->lst = (t_prog *)ft_memalloc(sizeof(t_prog));
		ag->lst->data = ft_strsplit(ag->trim_str, '"');
	}
	else if (ft_strncmp(ag->trim_str, ".comment", 8) == 0)
	{
		ag->lst = (t_prog *)ft_memalloc(sizeof(t_prog));
		ag->lst->data = ft_strsplit(ag->trim_str, '"');
	}
	else
	{
		ft_printf("Invalid command %s\n", ag->trim_str);
		exit(-1);
	}
}


/*
 * if the line consists of a label the label and any commands that are on the
 * same line is saved into a list item
*/
void	ft_lbl(t_args *ag, int i)
{
	int		cnt;
	int		len;
	int		k;

	cnt = 0;
	k = 0;
	ag->lst->label = ft_strsub(ag->trim_str, 0, i);
	if (*(ag->trim_str + i + 1) != '\0')
	{
		ag->ref = ft_strsplit(ag->trim_str + i + 1, ',');
		ag->ref2 = ft_split(ag->ref[0], ' ');
		len = ft_arrlen(ag->ref) + ft_arrlen(ag->ref2);
		ag->lst->data = (char **)ft_memalloc(sizeof(char *) * (len));
		while (ag->ref2[cnt])
			ag->lst->data[k++] = ft_strdup(ag->ref2[cnt++]);
		cnt = 1;
		while (ag->ref[cnt])
			ag->lst->data[k++] = ft_strdup(ag->ref[cnt++]);
		ag->lst->data[k] = NULL;
		free_2d(&ag->ref);
		free_2d(&ag->ref2);
	}
	else
		ag->lst->data = NULL;
}

/*
 * gets the commands in the line, and save it in a list item
*/ 
void	ft_com(t_args *ag)
{
	int		len;
	int		cnt;
	int		k;

	cnt = 0;
	k = 0;
	ag->lst->label = NULL;
	ag->ref = ft_strsplit(ag->trim_str, ',');
	ag->ref2 = ft_split(ag->ref[0], ' ');
	len = ft_arrlen(ag->ref) + ft_arrlen(ag->ref2);
	ag->lst->data = (char **)ft_memalloc(sizeof(char *) * (len));
	while (ag->ref2[cnt])
		ag->lst->data[k++] = ft_strdup(ag->ref2[cnt++]);
	cnt = 1;
	while (ag->ref[cnt])
		ag->lst->data[k++] = ft_strdup(ag->ref[cnt++]);
	ag->lst->data[k] = NULL;
	free_2d(&ag->ref);
	free_2d(&ag->ref2);
}

/*
 * checks if a line contains a label and calls the correct function for parsing 
 * the line.
*/ 
void	ft_lbl_com(t_args *ag)
{
	int 	i;

	ag->lst = (t_prog *)ft_memalloc(sizeof(t_prog));
	if ((i = ft_chr_i(ag->trim_str, ':')) > -1)
	{
		if (i > 0 && ag->trim_str[i - 1] != '%')
			ft_lbl(ag, i);
		else
			ft_com(ag);
	}
	else
		ft_com(ag);
	ft_printf("Label or instruction\n");
}

/*
 * sets the head of the linked list, and if the head is already set it links the
 * next item of the list to the previous.
*/
void	ft_setlist(t_args *ag)
{
	t_prog	*temp;
	
	temp = ag->head;
	while (temp && temp->next)
		temp = temp->next;
	if (ag->head)
		temp->next = ag->lst;
	else
		ag->head = ag->lst;

}

/*
 * Checks the line read from the file, and creates a linked list based on
 * the data.
 */
void		parse_line(t_args *ag)
{
	char	*tmp;
	int		i;
	
	ag->trim_str = ft_strtrim(ag->line);
	if ((i = ft_chr_i(ag->trim_str, '#')) > -1)
	{
		tmp = ft_strsub(ag->trim_str, 0, i);
		free(ag->trim_str);
		ag->trim_str = tmp;
	}
	if (ag->trim_str[0] == '.')
		ft_nm_com(ag);
	else if (ag->trim_str[0])
		ft_lbl_com(ag);
	else
	{
		free(ag->trim_str);
		return ;
	}
	ft_setlist(ag);
	ft_printf("%s\n", ag->trim_str);
	free(ag->trim_str);
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
