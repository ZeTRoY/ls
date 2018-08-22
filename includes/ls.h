/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 09:36:18 by aroi              #+#    #+#             */
/*   Updated: 2018/08/22 17:19:35 by aroi             ###   ########.fr       */
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

# define FG_C		0x1
# define FG_ONE		0x2
# define FG_L		0x4
# define FG_RECUR	0x8
# define FG_A		0x10
# define FG_R		0x20
# define FG_T		0x40
# define FG_D		0x80
# define FG_G		0x100
# define FG_F		0x200
# define FG_COLOR	0x400
# define FG_U		0x800
# define FG_M		0x1000
# define FG_N		0x2000
# define FG_H		0x4000
# define WR_PTH		0x8000

typedef struct		s_indent
{
	intmax_t		total;
	u_int16_t		link;
	u_int16_t		user;
	u_int16_t		group;
	u_int16_t		size;
	u_int16_t		date;
}					t_indent;

typedef struct		s_info
{
	int				link_num;
	int				uid;
	int				gid;
	char			*user_name;
	char			*group_name;
	uintmax_t		size;
	time_t			*time;
	t_indent		ind;
}					t_info;

typedef struct		s_file
{
	u_int32_t		flag;
	int				err;
	char			rights[12];
	char			date[13];
	char			*name;
	char			*path;
	struct s_file	*addr;
	struct s_file	*next;
	DIR				*dir;
	t_info			stat;
}					t_file;

#endif