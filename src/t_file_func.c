/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 20:46:14 by aroi              #+#    #+#             */
/*   Updated: 2019/01/19 20:57:31 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_file		*new_file(void)
{
	t_file	*file;

	if (!(file = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	file->flag = FG_C;
	file->name = NULL;
	file->user = NULL;
	file->group = NULL;
	file->path = NULL;
	// file->size = NULL;
	file->addr = file;
	file->next = NULL;
	file->ind.date = 1;
	file->ind.group = 1;
	file->ind.link = 1;
	file->ind.user = 1;
	file->ind.size = 1;
	file->ind.total = 0;
	file->acl = NULL;
	file->x = 0;
	return (file);
}

int			add_file(t_file **file, char *str)
{
	t_file *tmp;

	if ((*file)->name)
	{
		tmp = (*file)->addr;
		(*file)->next = new_file();
		(*file) = (*file)->next;
		(*file)->flag = tmp->flag;
		(*file)->addr = tmp;
	}
	ft_strdel(&(*file)->name);
	(*file)->name = ft_strdup(str);
	return (1);
}

void		destroy_file(t_file **file)
{
	t_file *tmp;

	tmp = *file;
	if (!tmp)
		return ;
	free(tmp->name);
	ft_strdel(&tmp->path);
	free(tmp->user);
	free(tmp->group);
	// if (tmp->acl != NULL)
	acl_free((void *)tmp->acl);
	free(tmp);
	*file = NULL;
}
