/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 18:24:56 by aroi              #+#    #+#             */
/*   Updated: 2019/01/12 12:48:35 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int16_t	ft_what_bgcolor(char *str)
{
	if (*str == '\0')
		return (0);
	str++;
	if (!ft_strcmp(str, "red"))
		return (0x80);
	else if (!ft_strcmp(str, "green"))
		return (0x100);
	else if (!ft_strcmp(str, "brown"))
		return (0x200);
	else if (!ft_strcmp(str, "cyan"))
		return (0x400);
	else
		return (0);
}

static int16_t	ft_what_fgcolor(char *str, int qnt)
{
	short	num;
	char	*tmp;

	tmp = ft_strsub(str, 0, qnt);
	if (!ft_strcmp(tmp, "black"))
		num = 0x1;
	else if (!ft_strcmp(tmp, "red"))
		num = 0x2;
	else if (!ft_strcmp(tmp, "green"))
		num = 0x4;
	else if (!ft_strcmp(tmp, "brown"))
		num = 0x8;
	else if (!ft_strcmp(tmp, "blue"))
		num = 0x10;
	else if (!ft_strcmp(tmp, "magenta"))
		num = 0x20;
	else if (!ft_strcmp(tmp, "cyan"))
		num = 0x40;
	else if (!ft_strcmp(tmp, "eoc"))
		num = 0;
	else
		num = -0x800;
	ft_strdel(&tmp);
	return (num);
}

static char	ft_print_color(int16_t c)
{
	if (c < 0)
		return (0);
	if (c & 0x1)
		ft_putstr("\033[30m");
	else if (c & 0x2)
		ft_putstr("\033[31m");
	else if (c & 0x4)
		ft_putstr("\033[32m");
	else if (c & 0x8)
		ft_putstr("\033[38;2;165;42;42m");
	else if (c & 0x10)
		ft_putstr("\033[34m");
	else if (c & 0x20)
		ft_putstr("\033[35m");
	else if (c & 0x40)
		ft_putstr("\033[36m");
	else if (c == 0)
		ft_putstr("\033[0m");
	if (c & 0x80)
		ft_putstr("\033[41m");
	else if (c & 0x100)
		ft_putstr("\033[42m");
	else if (c & 0x200)
		ft_putstr("\033[48;2;165;42;42m");
	else if (c & 0x400)
		ft_putstr("\033[46m");
	return (1);
}

static int	ft_count(char *str)
{
	int	qnt;

	qnt = 0;
	while (ft_isalpha(*str++))
		qnt++;
	return (qnt);
}

void		ft_is_color(t_printf **printf)
{
	int		qnt;
	char	n;
	int		i;
	char	*str;

	i = 0;
	n = 1;
	while ((*printf)->str[i] != '}')
		i++;
	str = ft_strsub((*printf)->str, 1, i - 1);
	qnt = ft_count(str);
	if (!ft_print_color(ft_what_fgcolor(str, qnt) + ft_what_bgcolor(str + qnt)))
		n = 0;
	if (n)
	{
		while (*((*printf)->str) != '}')
		{
			(*printf)->str++;
			(*printf)->i++;
		}
		(*printf)->str++;
		(*printf)->i++;
	}
	ft_strdel(&str);
}
