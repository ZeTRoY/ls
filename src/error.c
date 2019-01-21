/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 20:53:44 by aroi              #+#    #+#             */
/*   Updated: 2019/01/21 19:05:06 by aroi             ###   ########.fr       */
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
	// ft_putstr_fd("ls: ", 2);
	// ft_putstr_fd("illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	write(2, "\nusage: ls [-@CGRaefglmnort1] [file ...]\n", 41);
	// ft_putstr_fd("\nusage: ls [-@CGRaefglmnort1] [file ...]\n", 2);
	exit(1);
}
