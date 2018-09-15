/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 09:36:18 by aroi              #+#    #+#             */
/*   Updated: 2018/09/15 17:27:09 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include "libft.h"
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/acl.h>
# include <sys/xattr.h>

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
# define FG_ACL		0x8000
# define FG_EA		0x10000
# define WR_PTH		0x20000
# define IS_FILE	0x40000

typedef struct		s_indent
{
	intmax_t		total;
	u_int16_t		link;
	u_int16_t		user;
	u_int16_t		group;
	u_int16_t		size;
	u_int16_t		date;
}					t_indent;

typedef struct		s_file
{
	u_int32_t		flag;
	char			rights[12];
	char			date[14];
	char			*str;
	char			*name;
	char			*path;
	char			*user;
	char			*group;
	// char			*size;
	struct s_file	*addr;
	struct s_file	*next;
	struct stat		st;
	t_indent		ind;
	acl_t			acl;
}					t_file;

#endif