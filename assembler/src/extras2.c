/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstander <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 12:05:41 by hstander          #+#    #+#             */
/*   Updated: 2017/08/28 13:48:21 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/asm.h"

int			arg_label(int arg, t_args *ag, t_prog *lst)
{
	char	*sub;
	int		arg_param;

	sub = ft_join(lst->data[arg], 1, (ft_strlen(lst->data[arg]) - 1));
	arg_param = get_label_offset(sub, ag, lst);
	free(sub);
	return (arg_param);
}

char		*ft_join(char *str, int begin, int len)
{
	char	*temp;
	char	*sub;

	temp = ft_strsub(str, begin, len);
	sub = ft_strjoin(temp, ":");
	free(temp);
	return (sub);
}

char		*ft_substr(char *str, int len)
{
	char	*sub;

	sub = ft_strsub(str, 0, len);
	free(str);
	return (sub);
}
