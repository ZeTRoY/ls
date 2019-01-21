/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 20:53:13 by aroi              #+#    #+#             */
/*   Updated: 2019/01/19 20:53:20 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void		kek(t_file **current, t_file **prev, t_file **end)
{
	t_file	*tmp;

	if (*prev)
		(*prev)->next = (*current)->next;
	tmp = (*current)->next;
	(*current)->next = NULL;
	(*end)->next = *current;
	*end = *current;
	*current = tmp;
}

static t_file	*get_ends(t_file **left, t_file **right, t_file *end,
	t_file *pivot)
{
	if (*left == NULL)
		*left = pivot;
	*right = end;
	return (pivot);
}

t_file			*t_partition(t_file *left, t_file **left1, t_file *right,
	t_file **right1)
{
	t_file	*pivot;
	t_file	*prev;
	t_file	*current;
	t_file	*end;

	pivot = right;
	prev = NULL;
	current = left;
	end = pivot;
	while (current != pivot)
	{
		if (left->flag & FG_R ? current->st.st_mtime - pivot->st.st_mtime <= 0 :
			current->st.st_mtime - pivot->st.st_mtime >= 0)
		{
			if (*left1 == NULL)
				*left1 = current;
			prev = current;
			current = current->next;
		}
		else
			kek(&current, &prev, &end);
	}
	return (get_ends(left1, right1, end, pivot));
}

t_file			*not_t_partition(t_file *left, t_file **left1, t_file *right,
	t_file **right1)
{
	t_file	*pivot;
	t_file	*prev;
	t_file	*current;
	t_file	*end;

	pivot = right;
	prev = NULL;
	current = left;
	end = pivot;
	while (current != pivot)
	{
		if (left->flag & FG_R ? ft_strcmp(current->name, pivot->name) >= 0 :
			ft_strcmp(current->name, pivot->name) <= 0)
		{
			if (*left1 == NULL)
				*left1 = current;
			prev = current;
			current = current->next;
		}
		else
			kek(&current, &prev, &end);
	}
	return (get_ends(left1, right1, end, pivot));
}
