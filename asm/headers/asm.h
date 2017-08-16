/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvan-roo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 10:59:32 by gvan-roo          #+#    #+#             */
/*   Updated: 2017/08/16 10:08:26 by hstander         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __ASM_H
# define __ASM_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include "op.h"

typedef struct s_prog	t_prog;

struct					s_prog
{
	char				**data;
	t_prog				*next;
};

#endif
