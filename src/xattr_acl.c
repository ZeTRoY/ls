/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xattr_acl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 18:52:58 by aroi              #+#    #+#             */
/*   Updated: 2019/02/08 16:32:28 by aroi             ###   ########.fr       */
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
	acl_free(text);
	ft_freearr((void **)tmp);
}

void		ft_get_xattr(t_file *file)
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
			write(1, "\t", 1);
			write(1, xattr, ft_strlen(xattr));
			write(1, "\t", 1);
			ft_printf("%4d", size);
			write(1, "\n", 1);
			xattr += ft_strlen(xattr) + 1;
		}
	}
	file->acl && (file->flag & FG_ACL) ? write_acl(file) : 0;
}
