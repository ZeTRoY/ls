/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 09:36:18 by aroi              #+#    #+#             */
/*   Updated: 2018/08/20 05:54:25 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h> //for stat and lstat
# include <pwd.h>
# include <grp.h>
# include <time.h>

typedef struct		s_options
{
	char			R;
	char			l;
	char			one;
	char			a;
	char			r;
	char			t;
	char			n;
}					t_options;

typedef struct		s_indent
{
	intmax_t		total;
	u_int16_t		block;
	u_int16_t		link;
	u_int16_t		user;
	u_int16_t		group;
	u_int16_t		size;
	u_int16_t		date;
}					t_indent;

typedef struct		s_info
{
	char			type;
	int				link_num;
	int				uid;
	int				gid;
	char			*user_name;
	char			*group_name;
	time_t			*time;
	uintmax_t		size;
	t_indent		ind;
}					t_info;

typedef struct		s_file
{
	t_options		flags;
	int				err;
	char			rights[12];
	char			date[13];
	char			*name;
	char			*path;
	struct s_file	*addr;
	struct s_file	*next;
	DIR				*dir;
	t_info			l_sign;
}					t_file;


#endif