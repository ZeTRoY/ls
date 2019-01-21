/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 19:57:29 by aroi              #+#    #+#             */
/*   Updated: 2019/01/21 11:39:13 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	output_m(t_file *next, int x, char *name)
{
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	if (next == NULL)
	{
		if (x + ft_strlen(name) + 1 > win.ws_col)
			ft_putchar('\n');
		ft_printf("%s\n", name);
	}
	else
	{
		if (x + ft_strlen(name) + 2 < win.ws_col)
			x += ft_strlen(name) + 2;
		else
		{
			x = ft_strlen(name) + 2;
			ft_putchar('\n');
		}
		ft_printf("%s, ", name);
	}
}

void		output_file(t_file *file)
{
	if (file->flag & FG_COLOR)
		ft_add_color(file);
	if (file->flag & FG_M)
		output_m(file->next, file->addr->x, file->name);
	else if (file->flag & FG_L)
		output_long(file);
	else if (file->flag & FG_ONE)
		ft_putendl(file->name);
	ft_putstr("\033[0m");
}

static char	*make_new_path(char *path, char *str)
{
	char	*new;
	char	*tmp;

	tmp = 0;
	new = 0;
	if (!path)
		new = ft_strdup(str);
	else
	{
		tmp = ft_strjoin(path, "/");
		new = ft_strjoin(tmp, str);
		free(tmp);
	}
	// printf("%s and %s\n", dir->path, dir->name);
	return (new);
}

void		get_info(t_file **file, char *path, char *str)
{
	add_file(file, str);
	ft_strdel(&(*file)->path);
	(*file)->path = make_new_path(path, str);
	lstat((*file)->path, &(*file)->st) < 0 ?
		stat((*file)->path, &(*file)->st) : 0;
	get_stats(*file);
}
