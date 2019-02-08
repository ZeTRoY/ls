/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_columns.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 20:45:21 by aroi              #+#    #+#             */
/*   Updated: 2019/02/08 16:30:35 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static int	additional_colors(mode_t mode)
{
	if (!S_ISFIFO(mode))
		return (0);
	ft_putstr("\033[38;2;204;204;0m");
	return (1);
}

int			ft_add_color(t_file *file)
{
	if (S_ISDIR(file->st.st_mode) && (S_ISVTX & file->st.st_mode) &&
			(S_IWOTH & file->st.st_mode))
		ft_putstr("\033[30;42m");
	else if (S_ISDIR(file->st.st_mode) && (S_IWOTH & file->st.st_mode))
		ft_putstr("\033[30;48;2;165;42;42m");
	else if (S_ISDIR(file->st.st_mode))
		ft_putstr("\033[34;49m");
	else if (S_ISLNK(file->st.st_mode))
		ft_putstr("\033[35;49m");
	else if (S_ISSOCK(file->st.st_mode))
		ft_putstr("\033[32;49m");
	else if (S_ISBLK(file->st.st_mode))
		ft_putstr("\033[34;46m");
	else if (S_ISCHR(file->st.st_mode))
		ft_putstr("\033[34;48;2;165;42;42m");
	else if (S_ISUID & file->st.st_mode)
		ft_putstr("\033[30;41m");
	else if (S_ISGID & file->st.st_mode)
		ft_putstr("\033[30;46m");
	else if ((S_IXUSR & file->st.st_mode) && (S_IXGRP & file->st.st_mode) &&
			(S_IXOTH & file->st.st_mode))
		ft_putstr("\033[31;49m");
	else
		return (additional_colors(file->st.st_mode));
	return (1);
}

static void	print(int flag, t_file *iter, int size, int row)
{
	int i;
	int j;

	while (iter)
	{
		i = 0;
		j = 0;
		if (flag & FG_COLOR)
		{
			ft_add_color(iter);
			write(1, iter->name, ft_strlen(iter->name));
			write(1, "\033[0m", 4);
			while (j++ < size - ft_strlen(iter->name))
				write(1, " ", 1);
		}
		else
		{
			write(1, iter->name, ft_strlen(iter->name));
			while (j < size - ft_strlen(iter->name) && (j += 8))
				write(1, "\t", 1);
		}
		while (iter && i++ < row)
			iter = iter->next;
	}
}

static void	output(t_file *file, int row, int size)
{
	t_file	*iter;
	int		index;
	int		i;

	index = 0;
	while (index++ < row)
	{
		i = 0;
		iter = file;
		while (iter && i++ < index - 1)
			iter = iter->next;
		print(file->flag, iter, size, row);
		ft_putchar('\n');
	}
}

void		output_columns(t_file *file)
{
	t_file			*iter;
	int				size;
	int				n;
	struct winsize	win;
	int				row;

	size = 0;
	n = 0;
	row = 1;
	ioctl(0, TIOCGWINSZ, &win);
	iter = file;
	while (iter)
	{
		size = size < ft_strlen(iter->name) ? ft_strlen(iter->name) : size;
		n += 1;
		iter = iter->next;
	}
	if (file->flag & FG_COLOR)
		size = size + 1;
	else
		size += 8 - size % 8;
	while ((n / row + ((n % row != 0) ? 1 : 0)) * size > win.ws_col)
		row++;
	output(file, row, size);
}
