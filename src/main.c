/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 19:29:28 by aroi              #+#    #+#             */
/*   Updated: 2019/01/21 11:28:50 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	open_directories(t_file **file)
{
	while ((*file)->next)
	{
		S_ISDIR((*file)->st.st_mode) ? open_dir(*file) : 0;
		*file = (*file)->next;
		(*file)->flag |= IS_FILE;
	}
	S_ISDIR((*file)->st.st_mode) ? open_dir(*file) : 0;
}

int			is_option(char c, u_int32_t *flag)
{
	if (c == 'a' || c == 'f')
		(*flag) |= c == 'f' ? FG_A | FG_F : FG_A;
	else if (c == '1' || c == 'l')
		(*flag) = c == '1' ? ((((*flag) | FG_ONE)
			& ~FG_C) & ~FG_L) & ~FG_M : (((((*flag) | FG_L)
				& ~FG_C) & ~FG_ONE) & ~FG_M);
	else if (c == 'r' || c == 'n')
		(*flag) = c == 'l' ? (*flag) | FG_R : (((((*flag) | FG_L | FG_N)
			& ~FG_C) & ~FG_ONE) & ~FG_M);
	else if (c == 'g' || c == 'o')
		(*flag) = c == 'g' ? (((((*flag) | FG_L | FG_G) & ~FG_C) & ~FG_ONE) &
			~FG_M) : (((((*flag) | FG_L | FG_O) & ~FG_C) & ~FG_ONE) & ~FG_M);
	else if (c == 't' || c == '@')
		(*flag) |= c == 't' ? FG_T : FG_EXA;
	else if (c == 'R' || c == 'G')
		(*flag) |= c == 'R' ? FG_RECUR : FG_COLOR;
	else if (c == 'm' || (c == 'C' && !((*flag) & FG_M)))
		(*flag) = c == 'm' ? ((((*flag) | FG_M) & ~FG_ONE) & ~FG_L) & ~FG_C :
			(((*flag) | FG_C) & ~FG_ONE) & ~FG_L;
	else if (c == 'e')
		(*flag) |= FG_ACL;
	else
		return (0);
	return (1);
}

static int	quicksort_n_return(int flag, int i, int argc, char **argv)
{
	flag & FG_F ? 0 : ft_quicksort_chars(argv, i, argc - 1);
	return (i - 1);
}

int			ft_parse_options(t_file *file, int argc, char **argv)
{
	int			i;
	int			j;

	i = 0;
	while (++i < argc && argv[i][0] == '-')
	{
		j = 0;
		if (argv[i][1] == 0)
		{
			return (quicksort_n_return(file->flag, i, argc, argv));
		}
		while (argv[i][++j])
			if (!is_option(argv[i][j], &file->flag))
			{
				if (argv[i][j] == '-' && !argv[i][j + 1])
				{
					file->flag & FG_F ? 0 :
						ft_quicksort_chars(argv, i + 1, argc - 1);
					return (i);
				}
				else
					usage(argv[i][j], argv[0]);
			}
	}
	return (quicksort_n_return(file->flag, i, argc, argv));
}

int			main(int argc, char **argv)
{
	int			index;
	int			i;
	struct stat	ds;
	t_file		*file;

	file = new_file();
	i = ft_parse_options(file, argc, argv);
	if (argc == i + 1)
		stat(".", &file->st) == 0 ? add_file(&file, ".") : error(".");
	(argc - i > 2) ? file->flag |= WR_PTH : 0;
	while (++i < argc)
	{
		if (file->flag & FG_L || (index = stat(argv[i], &ds)) < 0)
			(index = lstat(argv[i], &ds)) < 0 ? error(argv[i]) : 0;
		index == 0 ? add_file(&file, argv[i]) && ft_memcpy(&file->st, &ds,
			sizeof(struct stat)) && get_stats(file) : 0;
	}
	if (!(file->flag & FG_F))
	{
		sort(&file->addr, 0);
		file->flag & FG_T ? sort(&file->addr, FG_T) : 0;
	}
	file = write_files(file->addr);
	open_directories(&file);
	// system("leaks ft_ls");
	return (0);
}
