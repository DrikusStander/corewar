/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 10:59:32 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/17 17:27:03 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ASM_H
# define __ASM_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include "op.h"

typedef struct s_prog	t_prog;
typedef struct s_args	t_args;

struct					s_prog
{
	char				*label;
	char				**data;
	t_prog				*next;
};

struct					s_args
{
	t_prog				*head;
	t_prog				*lst;
	char				*line;
	char				*trim_str;
	char				**ref;
	char				**ref2;
};

#endif
