/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 09:36:18 by aroi              #+#    #+#             */
/*   Updated: 2019/01/21 19:54:54 by aroi             ###   ########.fr       */
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
# include <sys/ioctl.h>

# define FG_C		0x1
# define FG_ONE		0x2
# define FG_L		0x4
# define FG_RECUR	0x8
# define FG_A		0x10
# define FG_R		0x20
# define FG_T		0x40
# define FG_O		0x80
# define FG_G		0x100
# define FG_F		0x200
# define FG_COLOR	0x400
# define FG_M		0x8000
# define FG_N		0x1000
# define FG_ACL		0x2000
# define FG_EXA		0x4000
# define WR_PTH		0x80000
# define IS_FILE	0x10000

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
	struct s_file	*addr;
	struct s_file	*next;
	struct stat		st;
	t_indent		ind;
	acl_t			acl;
	u_int16_t		x;
}					t_file;

t_file				*new_file(void);
int					add_file(t_file **file, char *str);
int					destroy_file(t_file **file);
void				sort(t_file **ls, int flag);
t_file				*t_partition(t_file *left, t_file **left1,
	t_file *right, t_file **right1);
t_file				*not_t_partition(t_file *left, t_file **left1,
	t_file *right, t_file **right1);
void				open_dir(t_file *directory);
t_file				*write_files(t_file *file);
void				error_handler(char *str);
void				usage(char c, char *str);
void				output_long(t_file *file);
void				output_columns(t_file *file);
int					get_stats(t_file *file);
void				get_date(t_file *file);
void				get_ug_name(t_file *file);
void				get_rights(t_file *file);
void				output_file(t_file *file);
void				get_info(t_file **file, char *path, char *str);
int					ft_add_color(t_file *file);

#endif
