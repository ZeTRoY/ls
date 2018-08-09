/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 09:36:18 by aroi              #+#    #+#             */
/*   Updated: 2018/08/09 06:04:04 by aroi             ###   ########.fr       */
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
	char			*path;
	char			type;
	struct s_ls		*next;
	struct s_ls		*prev;
	struct s_ls		*parent;
	struct s_ls		*child;
}					t_ls;

#endif