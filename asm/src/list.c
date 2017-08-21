/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 10:55:53 by hstander          #+#    #+#             */
/*   Updated: 2017/08/21 10:05:14 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/asm.h"

/*
 * checks if a line contains a label and calls the correct function for parsing
 * the line.
 */
void	ft_lbl_com(t_args *ag)
{
	int		i;

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
		ag->lst->data[k++] = ft_strtrim(ag->ref2[cnt++])/*ft_strdup(ag->ref2[cnt++])*/;
	cnt = 1;
	while (ag->ref[cnt])
		ag->lst->data[k++] = ft_strtrim(ag->ref[cnt++]) /*ft_strdup(ag->ref[cnt++])*/;
	ag->lst->data[k] = NULL;
	free_2d(&ag->ref);
	free_2d(&ag->ref2);
}

/*
 * saves the name of the program to the header struct if it passes all the 
 * tests.
 */
void	ft_name(t_args *ag, int i)
{
	int		j;
	char	*temp;

	if ((j = ft_chrn_i(ag->trim_str, '"')) > i)
	{
		temp = ft_strsub(ag->trim_str, (i + 1), (j - i - 1));
		if (ft_strlen(temp) > PROG_NAME_LENGTH)
		{
			ft_printf("Name to big:\n%s\n", ag->trim_str);
			free(temp);
			exit(-1);
		}
		ft_strcpy(ag->header->prog_name, temp);
		free(temp);
	}
	else
	{
		ft_printf("Non terminated string:\n%s\n", ag->trim_str);
		exit(-1);
	}
}

/*
 * saves the comment of the program to the header struct if it passes all the 
 * tests.
 */
void	ft_comment(t_args *ag, int i)
{
	int		j;
	char	*temp;

	if ((j = ft_chrn_i(ag->trim_str, '"')) > i)
	{
		temp = ft_strsub(ag->trim_str, (i + 1), (j - i - 1));
		if (ft_strlen(temp) > COMMENT_LENGTH)
		{
			ft_printf("comment to big:\n%s\n", ag->trim_str);
			free(temp);
			exit(-1);
		}
		ft_strcpy(ag->header->comment, temp);
		free(temp);
	}
	else
	{
		ft_printf("Non terminated string:\n%s\n", ag->trim_str);
		exit(-1);
	}
}

/*
 * prints a error message depending on the input integer.
 */
int		ft_exit_nmcm(t_args *ag, int i)
{
	if (i == -1)
		ft_printf("Invalid name:\n%s\n", ag->trim_str);
	if (i == -2)
			ft_printf("Invalid comment:\n%s\n", ag->trim_str);
	if (i == -3)
		ft_printf("Invalid command %s\n", ag->trim_str);
	return (i);
}

/*
 * if a line starts with a '.' it checks if the line is the program name or the
 * program comments, and calls the relevant function to save the name or 
 * comment into the header struct.
 */
void	ft_nm_com(t_args *ag)
{
	int		i;

	if (ft_strncmp(ag->trim_str, ".name", 5) == 0)
	{
		if ((i = ft_chr_i(ag->trim_str, '"')) > -1)
			ft_name(ag, i);
		else
			exit(ft_exit_nmcm(ag, -1));
	}
	else if (ft_strncmp(ag->trim_str, ".comment", 8) == 0)
	{
		if ((i = ft_chr_i(ag->trim_str, '"')) > -1)
			ft_comment(ag, i);
		else
			exit(ft_exit_nmcm(ag, -2));
	}
	else
		exit(ft_exit_nmcm(ag, -3));
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
			ag->lst->data[k++] = ft_strtrim(ag->ref2[cnt++])/*ft_strdup(ag->ref2[cnt++])*/;
		cnt = 1;
		while (ag->ref[cnt])
			ag->lst->data[k++] = ft_strtrim(ag->ref[cnt++]) /*ft_strdup(ag->ref[cnt++])*/;
		ag->lst->data[k] = NULL;
		free_2d(&ag->ref);
		free_2d(&ag->ref2);
	}
	else
		ag->lst->data = NULL;
}
