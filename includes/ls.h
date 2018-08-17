/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 09:36:18 by aroi              #+#    #+#             */
/*   Updated: 2018/08/17 15:25:08 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include "libft.h"
# include <dirent.h>
# include <errno.h>

typedef struct		s_options
{
	char			R;
	char			l;
	char			one;
	char			a;
	char			r;
	char			t;
}					t_options;

typedef struct		s_ls
{
	t_options		flags;
	char			*name;
	char			*path;
	char			type;
	struct s_ls		*next;
}					t_ls;

#endif