/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 19:57:29 by aroi              #+#    #+#             */
/*   Updated: 2019/01/21 13:03:16 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static int	quick_write(char *name)
{
	write(1, name, ft_strlen(name));
	return (1);
}

static void	output_m(t_file *file)
{
	struct winsize	win;

	ioctl(0, TIOCGWINSZ, &win);
	if (file->next == NULL)
	{
		if (file->addr->x + ft_strlen(file->name) + 1 > win.ws_col)
			ft_putchar('\n');
		(file->flag & FG_COLOR) && ft_add_color(file) ?
			quick_write(file->name) && write(1, "\033[0m\n", 5) :
				quick_write(file->name) && write(1, "\n", 1);
	}
	else
	{
		if (file->addr->x + ft_strlen(file->name) + 2 < win.ws_col)
			file->addr->x += ft_strlen(file->name) + 2;
		else
		{
			file->addr->x = ft_strlen(file->name) + 2;
			ft_putchar('\n');
		}
		(file->flag & FG_COLOR) && ft_add_color(file) ?
			quick_write(file->name) && write(1, "\033[0m, ", 6):
				quick_write(file->name) && write(1, ", ", 2);
	}
}

void		output_file(t_file *file)
{
	if (file->flag & FG_M)
		output_m(file);
	else if (file->flag & FG_L)
	{
		ft_printf("%s %*d ", file->rights, file->addr->ind.link,
			file->st.st_nlink);
		output_long(file);
	}
	else if (file->flag & FG_ONE)
		ft_putendl(file->name);
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
