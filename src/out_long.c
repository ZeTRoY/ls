/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_long.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 20:55:21 by aroi              #+#    #+#             */
/*   Updated: 2019/01/21 18:48:32 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	write_acl(t_file *file)
{
	char	**tmp;
	char	*text;

	text = acl_to_text(file->acl, NULL);
	tmp = ft_strsplit(ft_strchr(text, '\n') + 1, ':');
	write(1, " 0: ", 4);
	write(1, tmp[0], ft_strlen(tmp[0]));
	write(1, ":", 1);
	write(1, tmp[2], ft_strlen(tmp[2]));
	write(1, " ", 1);
	write(1, tmp[4], ft_strlen(tmp[4]));
	write(1, " ", 1);
	write(1, tmp[5], ft_strlen(tmp[5]));
	acl_free(text); //mb leaks? acl_free?
	ft_freearr((void **)tmp);
}

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

static void	ft_get_xattr(t_file *file)
{
	char	list[1024];
	char	*xattr;
	int		size;

	if (file->rights[10] == '@' && file->flag & FG_EXA)
	{
		xattr = list;
		listxattr(file->path, list, 1024, XATTR_NOFOLLOW);
		while (*xattr)
		{
			size = getxattr(file->path, xattr, NULL, 0, 0, XATTR_NOFOLLOW);
			ft_printf("\t%s\t%4d\n", xattr, size);
			xattr += ft_strlen(xattr) + 1;
		}
	}
	file->acl && (file->flag & FG_ACL) ? write_acl(file) : 0;
}

static void	out_link(t_file *file)
{
	char	*buff;

	if (file->rights[0] == 'l')
	{
		buff = ft_memalloc(4096);
		buff[4096] = '\0';
		if (file->path)
			readlink(file->path, buff, 4095) > 0 ? ft_printf(" -> %s\n", buff) : 0;
		else
			readlink(file->name, buff, 4095) > 0 ? ft_printf(" -> %s\n", buff) : 0;
		free(buff);
	}
	else
		ft_printf("\n");
	ft_get_xattr(file);
}

void		output_long(t_file *file)
{
	if (file->flag & FG_N)
		ft_printf("%-*d  %-*d  ", file->addr->ind.user, file->st.st_uid,
			file->addr->ind.group, file->st.st_gid);
	else
	{
		if ((file->flag & FG_G) == 0)
			ft_printf("%-*s  ", file->addr->ind.user, file->user);
		if ((file->flag & FG_O) == 0)
			ft_printf("%-*s  ", file->addr->ind.group, file->group);
	}
	(file->flag & FG_O) && (file->flag & FG_G) ? write(1, "  ", 2) : 0;
	if (file->rights[0] != 'b' && file->rights[0] != 'c')
		ft_printf("%*d ", file->addr->ind.size, file->st.st_size);
	else if (minor(file->st.st_rdev) > 255 || minor(file->st.st_rdev) < 0)
		ft_printf("%3d, 0x%08x ", major(file->st.st_rdev),
			(u_int)(minor(file->st.st_rdev) - 3));
	else
		ft_printf("%3d, %3d ", major(file->st.st_rdev),
			minor(file->st.st_rdev));
	ft_printf("%s ", file->date);
	(file->flag & FG_COLOR) && ft_add_color(file) ?
		write(1, file->name, ft_strlen(file->name)) && write(1, "\033[0m", 5) :
		// ft_printf("%s\033[0m", file->name) :
			write(1, file->name, ft_strlen(file->name));
	out_link(file);
}
