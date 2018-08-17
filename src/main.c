/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 09:28:36 by aroi              #+#    #+#             */
/*   Updated: 2018/08/17 17:20:01 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
//	What does "unknown" type of file mean?
//	should errors output to standart or errorr output
//

#include "ls.h"
// #include <stdio.h>
// #include <stdlib.h>
#include <time.h>

#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>

void	error(char *name, char *strerr)
{
	ft_printf("ft_ls: %s: %s\nerrno is: %d\n", name, strerr, errno);
	exit(errno);
}

void	usage(char c) //should be illegal option here?
{
	ft_printf("./ft_ls: illegal option -- %c\n", c);
	ft_printf("usage: ./ft_ls [-Ralrt1] [file ...]\n");
	exit(1);
}

// void	ft_get_data(t_ls *ls)
// {}

// int		ft_ls(t_ls *ls, char *str)
// {
// 	DIR				*dir;
// 	struct dirent	*ds;
// 	struct stat		sts;
// 	struct passwd *pwuser;
// 	struct group *grpnam;

// 	ls->str = str;
// 	if (!(dir = opendir(str)) && errno != 20)
// 		error(str, strerror(errno));
// 	if (errno == 20)
// 	{
// 		ft_printf("%s\n", str);
// 		return (0);
// 	}
// 	while ((ds = readdir(dir)))
// 	{
// 		if (!ls->a && ds->d_name[0] == '.')
// 			continue;
// 		if (ls->l)
// 			ft_get_data(ls);
// 		// ft_printf("%s\n\n", ds->d_name);
// 		stat(ds->d_name, &sts);
// 		pwuser = getpwuid(sts.st_uid);
// 		grpnam = getgrgid(sts.st_gid);
// 		ft_printf("%s:\n", ds->d_name);
// 		if (S_IFDIR == sts.st_mode)
// 			printf("KEK\n");
// 		ft_printf("\tType: %u\n", sts.st_mode);
// 		ft_printf("\t%s\n", pwuser->pw_name);
// 		ft_printf("\t%s\n", grpnam->gr_name);
// 		ft_printf("\tperms: %o\n", sts.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO));
// 		ft_printf("\tlinks: %d\n", sts.st_nlink);
// 		ft_printf("\tsize: %ld\n", sts.st_size); /* you may use %lld */
// 		ft_printf("\tatime: %s", ctime(&sts.st_atime));
// 		ft_printf("\tmtime: %s", ctime(&sts.st_mtime));
// 		ft_printf("\tctime: %s\n", ctime(&sts.st_ctime));
// 	}
// 	closedir(dir);
// 	return (0);
// }

t_ls	*end_of_list(t_ls *ls)
{
	t_ls	*tmp;

	tmp = ls;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_ls	*partition(t_ls *left, t_ls **left1, t_ls *right, t_ls **right1)
{
	t_ls	*pivot;
	t_ls	*prev;
	t_ls	*current;
	t_ls	*end;
	t_ls	*tmp;

	pivot = right;
	prev = NULL;
	current = left;
	end = pivot;
	while (current != pivot)
	{
		if (ft_strcmp(current->name, pivot->name) <= 0)
		{
			if (*left1 == NULL)
				*left1 = current;
			prev = current;
			current = current->next;
		}
		else
		{
			if (prev)
				prev->next = current->next;
			tmp = current->next;
			current->next = NULL;
			end->next = current;
			end = current;
			current = tmp;
		}
	}
	if (*left1 == NULL)
		*left1 = pivot;
	*right1 = end;
	return (pivot);
}

t_ls	*quicksort(t_ls	*left, t_ls *right)
{
	t_ls	*pivot;
	t_ls	*left1;
	t_ls	*right1;
	t_ls	*tmp;

	if (!left || left == right)
		return (left);
	left1 = NULL;
	right1 = NULL;
	pivot = partition(left, &left1, right, &right1);
	if (left1 != pivot)
	{
		tmp = left1;
		while (tmp->next != pivot)
			tmp = tmp->next;
		tmp->next = NULL;
		left1 = quicksort(left1, tmp);
		tmp = end_of_list(left1);
		tmp->next = pivot;
	}
	pivot->next = quicksort(pivot->next, right1);
	return (left1);
}

void	sort(t_ls **ls)
{
	// t_ls	*tmp;

	// tmp = *ls;
	*ls = quicksort(*ls, end_of_list(*ls));
}

// t_ls		*partition(t_ls *ls_left, t_ls *ls_right)
// {
// 	t_ls	*pivot;
// 	t_ls	*ls_partition;

// 	pivot = ls_right;
// 	while (1)
// 	{
// 		while (ls_left != pivot)
// 			ls_left = ls_left->next;
// 		while (ls_right != pivot)
// 			ls_right = ls_left->prev;
// 		if ()
// 			break;
// 		swap(ls_left, ls_right);
// 	}
// 	return (ls_partition)
// }

// void		quicksort(t_ls *ls_left, t_ls *ls_right)
// {
// 	t_ls	*ls_partition;

// 	if (!ls_left || ls_left == ls_right || ls_right->next == ls_left)
// 		return ;
// 	ls_partition = partition(ls_left, ls_right);
// 	quicksort(ls_left, ls_partition->prev);
// 	quicksort(ls_partition->next, ls_right);
// }

char		what_type_is(__uint8_t type)
{
	if (type == DT_BLK)
		return ('b');
	else if (type == DT_CHR)
		return ('c');
	else if (type == DT_DIR)
		return ('d');
	else if (type == DT_LNK)
		return ('l');
	else if (type == DT_SOCK)
		return ('s');
	else if (type == DT_FIFO)
		return ('p');
	else if (type == DT_REG)
		return ('-');
	return ('*');
}

t_ls	*ls_new(void)
{
	t_ls *ls;

	if (!(ls = (t_ls *)malloc(sizeof(t_ls))))
		return (0);
	ls->flags.R = 0;
	ls->flags.one = 0;
	ls->flags.l = 0;
	ls->flags.a = 0;
	ls->flags.t = 0;
	ls->flags.r = 0;
	ls->name = 0;
	ls->path = 0;
	ls->next = 0;
	return (ls);
}

t_ls		*ls_add(t_ls *ls, struct dirent *ds)
{
	t_ls	*new;

	new = ls_new();
	new->flags = ls->flags;
	ls->next = new;
	new->name = ds->d_name;
	new->type = what_type_is(ds->d_type);
	return (new);
}

t_ls		*reset_ls(t_ls *ls)
{
	t_ls *tmp;

	tmp = ls;
	while(ls->next)
	{
		ls = ls->next;
		if (tmp->path)
		free(tmp);
		tmp = ls;
	}
	return (ls);
}

char		*make_new_path(char *path, char *str)
{
	char	*new;
	char	*tmp;

	new = 0;
	if (path)
		new = ft_strjoin(path, "/");
	tmp = new;
	if (tmp && str)
	{
		new = ft_strjoin(tmp, str);
		free(tmp);
	}
	return (new);
}

int		find_friends(t_ls *ls, DIR *dir) //should be int return?
{
	int				num;
	struct dirent	*ds;
	t_ls			*tmp;

	num = 0;
	tmp = ls;
	while ((ds = readdir(dir)))
	{
		if (!tmp->flags.a && ds->d_name[0] == '.')
			continue;
		if (num > 0)
		{
			tmp->next = ls_add(tmp, ds);
			tmp = tmp->next;
			// printf("next: %c is for %s\n", tmp->type, ds->d_name);
		}
		else
		{
			tmp->type = what_type_is(ds->d_type);
			tmp->name = ds->d_name;
			// printf("first: %c is for %s\n", tmp->type, ds->d_name);
		}
		// tmp->nbr = num++;
		num++;
	}
	closedir(dir);
	return (num);
}

void		ft_ls(t_ls *ls, char *str)
{
	int		num;
	DIR		*dir;
	t_ls	*tmp;

	if (!(dir = opendir(str)) && errno != 20)
		error(str, strerror(errno));
	ls->path = make_new_path(ls->path, ls->name); //malloc?
	if (errno == 20)
	{
		ft_printf("%s\n", ls->name);
		return ;
	}
	num = find_friends(ls, dir);
	sort(&ls);
	tmp = ls;
	while (ls->flags.one && tmp)
	{
		printf("%s\n", tmp->name);
		tmp = tmp->next;
	}
	// while (ls->flags.R && ls->next)
	// {
	//	ft_ls(ls->child, )
	//	ls = ls->next;
	// }
}

// if (str[0] == '-' && (str[1] == 'R' || str[1] == 'l' || str[1] == '1'
// || str[1] == 'a' || sstr[1] == 't' || str[1] == 'r') && !str[2])

void		ft_parse_options(t_ls *ls, int argc, char **argv)
{
	int			i;
	int			j;

	i = 0;
	while (++i < argc && argv[i][0] == '-' && argv[i][1])
	{
		j = 0;
		while (argv[i][++j])
		{
			if (argv[i][j] == 'R')
				ls->flags.R = 1;
			else if (argv[i][j] == 'l')
				ls->flags.l = 1;
			else if (argv[i][j] == '1')
				ls->flags.one = 1;
			else if (argv[i][j] == 'a')
				ls->flags.a = 1;
			else if (argv[i][j] == 't')
				ls->flags.t = 1;
			else if (argv[i][j] == 'r')
				ls->flags.r = 1;
			else
				usage(argv[i][j]);
		}
	}
}

int		main(int argc, char **argv)
{
	int		i;
	t_ls	*ls;

	i = 1;
	ls = ls_new();
	ft_parse_options(ls, argc, argv);
	while (i < argc && argv[i][0] == '-' && argv[i][1])
		i++;
	if (argc - i == 0)
		ft_ls(ls, ".");
	else
		while (i < argc)
		{
			ft_ls(ls, argv[i]);
			if (i < argc - 1)
				ft_printf("\n");
			i++;
			reset_ls(ls);
		}
	return (0);
}