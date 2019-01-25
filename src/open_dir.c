/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 19:49:58 by aroi              #+#    #+#             */
/*   Updated: 2019/01/25 10:23:25 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static int	isnt_proper_name(DIR *dir, t_file **file)
{
	t_file *tmp;

	*file = (*file)->addr;
	if (!(*file)->name)
	{
		while (*file)
		{
			tmp = *file;
			*file = (*file)->next;
			destroy_file(&tmp);
		}
		closedir(dir);
		return (1);
	}
	return (0);
}

static DIR	*create_file(t_file *directory, t_file **file)
{
	DIR				*dir;
	struct dirent	*ds;
	char			*path;

	*file = new_file();
	path = directory->path ? directory->path : directory->name;
	directory->flag |= directory->flag & IS_FILE ?
		write(1, "\n", 1) & 0 : IS_FILE;
	directory->flag & WR_PTH ? write(1, path, ft_strlen(path)) &&
		write(1, ":\n", 2) : 0;
	directory->flag |= WR_PTH;
	(*file)->flag = directory->flag;
	if (dir = opendir(path))
	{
		error_handler(directory->name);
		destroy_file(file);
		return (0);
	}
	while ((ds = readdir(dir)))
	{
		if (!(directory->flag & FG_A) && ds->d_name[0] == '.')
			continue ;
		get_info(file, path, ds->d_name);
	}
	return (dir);
}

static void	out_file(t_file *file)
{
	t_file *iter;

	iter = file;
	file->flag & FG_L ? write(1, "total ", 6) &&
		ft_printf("%d", file->ind.total) && write(1, "\n", 1) : 0;
	if (file->flag & FG_C)
		output_columns(file);
	else
		while (iter)
		{
			output_file(iter);
			iter = iter->next;
		}
}

void		open_dir(t_file *directory)
{
	DIR				*dir;
	t_file			*tmp;
	t_file			*file;

	if (((dir = create_file(directory, &file)) == NULL ||
			isnt_proper_name(dir, &file)) && destroy_file(&file))
		return ;
	if (!(file->flag & FG_F))
	{
		sort(&file, 0);
		file->flag & FG_T ? sort(&file, FG_T) : 0;
	}
	out_file(file);
	while (file)
	{
		if ((file->name[0] != '.' || file->name[1]) && (file->name[0] != '.'
					|| file->name[1] != '.'))
			S_ISDIR(file->st.st_mode) && (file->flag & FG_RECUR) ?
				open_dir(file) : 0;
		tmp = file;
		file = file->next;
		destroy_file(&tmp);
	}
	closedir(dir);
}

t_file		*write_files(t_file *file)
{
	t_file	*iter;

	iter = file;
	while (iter && iter->name)
	{
		if (!S_ISDIR(iter->st.st_mode))
		{
			file->flag |= IS_FILE;
			file->ind = file->addr->ind;
			if (file->flag & FG_C)
				output_columns(file);
			else
				output_file(iter);
		}
		iter = iter->next;
	}
	return (file->addr);
}
