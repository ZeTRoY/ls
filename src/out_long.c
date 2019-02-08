/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_long.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 20:55:21 by aroi              #+#    #+#             */
/*   Updated: 2019/02/08 16:32:13 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int			get_stats(t_file *file)
{
	int			tmp;
	char		*path;

	get_rights(file);
	path = file->path ? file->path : file->name;
	file->acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	file->rights[10] = file->acl ? '+' : ' ';
	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0)
		file->rights[10] = '@';
	else
		errno = 0;
	file->rights[11] = '\0';
	if ((tmp = ft_count_digits_base(file->st.st_nlink, 10)) >
			file->addr->ind.link)
		file->addr->ind.link = tmp;
	get_ug_name(file);
	if ((tmp = ft_count_digits_base(file->st.st_size, 10)) >
			file->addr->ind.size)
		file->addr->ind.size = tmp;
	get_date(file);
	file->addr->ind.total += file->st.st_blocks;
	file->ind = file->addr->ind;
	return (1);
}

static void	out_link(t_file *file)
{
	char	*buff;

	if (file->rights[0] == 'l')
	{
		buff = ft_memalloc(4096);
		buff[4096] = '\0';
		write(1, " -> ", 4);
		if (file->path)
			readlink(file->path, buff, 4095) > 0 ?
				write(1, buff, ft_strlen(buff)) : 0;
		else
			readlink(file->name, buff, 4095) > 0 ?
				write(1, buff, ft_strlen(buff)) : 0;
		write(1, "\n", 1);
		free(buff);
	}
	else
		write(1, "\n", 1);
	ft_get_xattr(file);
}

void		ngo_options(t_file *file)
{
	if (file->flag & FG_G)
	{
		if (file->flag & FG_O)
			write(1, "  ", 2);
		else if (file->flag & FG_N)
			ft_printf("%-*d  ", file->addr->ind.group, file->st.st_gid);
		else
			ft_printf("%-*s  ", file->addr->ind.group, file->group);
	}
	else if (file->flag & FG_O)
		file->flag & FG_N ?
		ft_printf("%-*d  ", file->addr->ind.user, file->st.st_uid) :
		ft_printf("%-*s  ", file->addr->ind.user, file->user);
	else
		ft_printf("%-*d  %-*d  ", file->addr->ind.user, file->st.st_uid,
			file->addr->ind.group, file->st.st_gid);
}

void		output_long(t_file *file)
{
	if (file->flag & FG_G || file->flag & FG_N || file->flag & FG_O)
		ngo_options(file);
	else
		ft_printf("%-*s  %-*s  ", file->addr->ind.user, file->user,
			file->addr->ind.group, file->group);
	if (file->rights[0] != 'b' && file->rights[0] != 'c')
		ft_printf("%*d ", file->addr->ind.size, file->st.st_size);
	else if (minor(file->st.st_rdev) > 255 || minor(file->st.st_rdev) < 0)
		ft_printf("%3d, 0x%08x ", major(file->st.st_rdev),
			(u_int)(minor(file->st.st_rdev) - 3));
	else
		ft_printf("%3d, %3d ", major(file->st.st_rdev),
			minor(file->st.st_rdev));
	write(1, file->date, ft_strlen(file->date));
	write(1, " ", 1);
	(file->flag & FG_COLOR) && ft_add_color(file) ?
		write(1, file->name, ft_strlen(file->name)) && write(1, "\033[0m", 5) :
			write(1, file->name, ft_strlen(file->name));
	out_link(file);
}
