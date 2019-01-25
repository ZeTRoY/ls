/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 20:53:44 by aroi              #+#    #+#             */
/*   Updated: 2019/01/25 18:06:13 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	error_handler(char *str)
{
	write(2, "ls: ", 4);
	if (!str[0])
	{
		write(2, ": ", 2);
		perror("");
	}
	else
		perror(str);
}

void	usage(char c, char *str)
{
	write(2, "ls: illegal option -- ", 22);
	ft_putchar_fd(c, 2);
	write(2, "\nusage: ls [-CGR@aefglmnort1] [file ...]\n", 41);
	exit(1);
}
