/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 20:47:22 by aroi              #+#    #+#             */
/*   Updated: 2019/01/19 20:47:23 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_file	*end_of_list(t_file *ls)
{
	t_file	*tmp;

	tmp = ls;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_file	*quicksort(t_file *left, t_file *right, int flag)
{
	t_file	*pivot;
	t_file	*left1;
	t_file	*right1;
	t_file	*tmp;

	if (!left || left == right)
		return (left);
	left1 = NULL;
	right1 = NULL;
	pivot = flag == FG_T ? t_partition(left, &left1, right, &right1)
		: not_t_partition(left, &left1, right, &right1);
	if (left1 != pivot)
	{
		tmp = left1;
		while (tmp->next != pivot)
			tmp = tmp->next;
		tmp->next = NULL;
		left1 = quicksort(left1, tmp, flag);
		tmp = end_of_list(left1);
		tmp->next = pivot;
	}
	pivot->next = quicksort(pivot->next, right1, flag);
	return (left1);
}

void	sort(t_file **ls, int flag)
{
	t_file	*tmp;

	*ls = quicksort(*ls, end_of_list(*ls), flag);
	tmp = *ls;
	tmp->ind = tmp->addr->ind;
	while (tmp)
	{
		tmp->addr = *ls;
		tmp = tmp->next;
	}
}
