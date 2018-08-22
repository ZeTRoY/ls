/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 09:28:36 by aroi              #+#    #+#             */
/*   Updated: 2018/08/22 20:28:27 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
//	What does "unknown" type of file mean?
//	should errors output to standart or errorr output
//	error leaks
//

#include "ls.h"
// #include <stdio.h>
// #include <stdlib.h>

// #include <pwd.h>
// #include <grp.h>

char	*find_str(char *name)
{
	char *str;

	str = ft_strrchr(name, '/');
	if (!str)
		str = name;
	else
		str++;
	return (str);
}

void	error(char *name, char *strerr)
{
	ft_printf("ft_ls: %s: %s\n", find_str(name), strerr);
}

void	usage(char c) //should be illegal option here?
{
	ft_printf("./ft_ls: illegal option -- %c\n", c);
	ft_printf("usage: ./ft_ls [-Ralrt1] [file ...]\n");
	system("leaks ft_ls");
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

t_file	*end_of_list(t_file *ls)
{
	t_file	*tmp;

	tmp = ls;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	kek(t_file **current, t_file **prev, t_file **end)
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

t_file	*partition(t_file *left, t_file **left1, t_file *right, t_file **right1)
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
		if (ft_strcmp(current->name, pivot->name) <= 0)
		{
			if (*left1 == NULL)
				*left1 = current;
			prev = current;
			current = current->next;
		}
		else
			kek(&current, &prev, &end);
	}
	if (*left1 == NULL)
		*left1 = pivot;
	*right1 = end;
	return (pivot);
}

t_file	*quicksort(t_file	*left, t_file *right)
{
	t_file	*pivot;
	t_file	*left1;
	t_file	*right1;
	t_file	*tmp;

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

void	sort(t_file **ls)
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

// t_ls	*ls_new(void)
// {
// 	t_ls *ls;

// 	if (!(ls = (t_ls *)malloc(sizeof(t_ls))))
// 		return (0);
// 	ls->flags.R = 0;
// 	ls->flags.one = 0;
// 	ls->flags.l = 0;
// 	ls->flags.a = 0;
// 	ls->flags.t = 0;
// 	ls->flags.r = 0;
// 	ls->name = 0;
// 	ls->path = 0;
// 	ls->next = 0;
// 	return (ls);
// }

// t_options	new_flags()
// {
// 	t_options flags;

// 	flags.a = 0;
// 	flags.R = 0;
// 	flags.one = 0;
// 	flags.r = 0;
// 	flags.t = 0;
// 	flags.l = 0;
// 	return (flags);
// }

// void		ls_add(t_ls **ls, struct dirent *ds)
// {
// 	t_ls	*new;

// 	new = ls_new();
// 	new->flags = (*ls)->flags;
// 	(*ls)->next = new;
// 	new->name = ds->d_name;
// 	new->type = what_type_is(ds->d_type);
// }


t_file		*new_file()
{
	t_file	*file;

	if (!(file = (t_file *)malloc(sizeof(t_file))))
		return (NULL);
	file->flag = FG_C;
	file->err = 0;
	file->name = NULL;
	file->path = NULL;
	file->addr = file;
	file->next = NULL;
	file->dir = NULL;
	file->stat.ind.total = 0;
	file->stat.ind.link = 0;
	file->stat.ind.user = 0;
	file->stat.ind.group = 0;
	file->stat.ind.size = 0;
	file->stat.ind.date = 0;
	return (file);
}

void		add_file(t_file **file, char *str)
{
	t_file *tmp;

	if (!(*file)->name)
	{
		(*file)->err = errno;
		(*file)->name = ft_strdup(str);
		return ;
	}
	tmp = (*file)->addr;
	(*file)->next = new_file();
	(*file) = (*file)->next;
	(*file)->flag = tmp->flag;
	(*file)->err = errno;
	(*file)->addr = tmp;
	(*file)->name = ft_strdup(str);
	(*file)->path = ft_strdup(tmp->path);
// 	new = ls_new();
// 	new->flags = (*ls)->flags;
// 	(*ls)->next = new;
// 	new->name = ds->d_name;
// 	new->type = what_type_is(ds->d_type);
}

void		destroy_file(t_file **file)
{
	t_file *tmp;

	tmp = *file;
	if (!*file)
		return ;
	if (tmp->name)
		free(tmp->name);
	if (tmp->path)
		free(tmp->path);
	if (tmp->stat.user_name)
		free(tmp->stat.user_name);
	if (tmp->stat.group_name)
		free(tmp->stat.group_name);
	if (tmp->dir)
		closedir(tmp->dir);
	free(*file);
	*file = NULL;
}

/*void		add_not_a_dir(t_file **file, struct dirent *ds)
{
	t_file *tmp;

	if (!(*file)->name)
	{
		(*file)->err = errno;
		(*file)->name = ds->d_name;
		return ;
	}
	tmp = (*file)->addr;
	(*file)->next = new_file((*file)->flags);
	(*file) = (*file)->next;
	(*file)->err = errno;
	(*file)->addr = tmp;
	(*file)->name = ds->d_name;
	// ft_printf("str: %s and errno: %d\n", str, errno);
}*/

char		*make_new_path(t_file *dir)
{
	char	*now;
	char	*tmp;
	int i;

	tmp = 0;
	now = 0;
	i = 0;
	if (!dir->name)
	{
		ft_printf("%s cannot be initialized.\n", dir->name);
		return (NULL);
	}
	if (!dir->path)
		dir->path = ft_strjoin(dir->name, "/");
	else
	{
		now = ft_strjoin(dir->path, dir->name);
		free(dir->path);
		dir->path = ft_strjoin(now, "/");
		free(now);
	}
	// printf("%s and %s\n", dir->path, dir->name);
	return (dir->path);
}

/*
// int		find_friends(t_ls *ls, DIR *dir) //should be int return?
// {
// 	int				num;
// 	struct dirent	*ds;
// 	t_ls			*tmp;

// 	num = 0;
// 	tmp = ls;
// 	while ((ds = readdir(dir)))
// 	{
// 		if (!tmp->flags.a && ds->d_name[0] == '.')
// 			continue;
// 		if (num > 0)
// 		{
// 			ls_add(&tmp, ds);
// 			tmp = tmp->next;
// 			// printf("next: %c is for %s\n", tmp->type, ds->d_name);
// 		}
// 		else
// 		{
// 			tmp->type = what_type_is(ds->d_type);
// 			tmp->name = ds->d_name;
// 			// printf("first: %c is for %s\n", tmp->type, ds->d_name);
// 		}
// 		// tmp->nbr = num++;
// 		num++;
// 	}
// 	closedir(dir);
// 	return (num);
// }

void		get_time(t_file *file)
{
	uintmax_t	tmp;
	time_t		current_time;
	time_t		difference;
	char		*time_str;

	time_str = ctime(file->l_sign.time);
	time(&current_time);
	ft_memcpy((void *)file->date, time_str + 4, 12);
	file->date[12] = '\0';
	if (current_time > *file->l_sign.time)
		difference = current_time - *file->l_sign.time;
	else
		difference = *file->l_sign.time - current_time;
	if (difference > 15778463)
	{
		file->date[7] = ' ';
		ft_memcpy((void *)(file->date + 8), time_str + 20, 4);
	}
	if ((tmp = ft_strlen(time_str)) > file->addr->l_sign.ind.date)
		file->addr->l_sign.ind.date = tmp;
}

void		get_user_info(t_file *file, struct stat ds)
{
	uintmax_t		tmp;
	struct passwd	*pwuser;

	if(!(pwuser = getpwuid(ds.st_uid)))
	{
		printf("Some problems with username\n");//lol1
		exit(1);//delete later?
	}
	file->l_sign.user_name = ft_strdup(pwuser->pw_name); //don't forget to free
	file->l_sign.uid = ds.st_uid;
	if (file->flags.n)
	{
		if ((tmp = ft_count_digits_base(ds.st_gid, 10)) > file->addr->l_sign.ind.user)
			file->addr->l_sign.ind.user = tmp;
	}
	else
		if ((tmp = ft_strlen(pwuser->pw_name)) > file->addr->l_sign.ind.user)
			file->addr->l_sign.ind.user = tmp;
}

void		get_group_info(t_file *file, struct stat ds)
{
	uintmax_t		tmp;
	struct group	*grpnam;

	if (!(grpnam = getgrgid(ds.st_gid)))
	{
		printf("Some problems with groupname\n");//lol2
		exit(1);//delete later?
	}
	file->l_sign.group_name = ft_strdup(grpnam->gr_name); //don't forget to free
	file->l_sign.gid = ds.st_gid;
	if (file->flags.n)
	{
		if ((tmp = ft_count_digits_base(ds.st_gid, 10)) > file->addr->l_sign.ind.group)
			file->addr->l_sign.ind.group = tmp;
	}
	else
		if ((tmp = ft_strlen(grpnam->gr_name)) > file->addr->l_sign.ind.group)
			file->addr->l_sign.ind.group = tmp;
}

void		record_rights(t_file *file, __uint16_t mode)
{
	file->rights[1] = mode & S_IRUSR ? 'r' : '-';
	file->rights[2] = mode & S_IWUSR ? 'w' : '-';
	if (mode & S_IXUSR)
		file->rights[3] = mode & S_ISUID ? 's' : 'x';
	else
		file->rights[3] = mode & S_ISUID ? 'S' : '-';
	file->rights[4] = mode & S_IRGRP ? 'r' : '-';
	file->rights[5] = mode & S_IWGRP ? 'w' : '-';
	if (mode & S_IXGRP)
		file->rights[6] = mode & S_ISGID ? 's' : 'x';
	else
		file->rights[6] = mode & S_ISGID ? 'S' : '-';
	file->rights[7] = mode & S_IROTH ? 'r' : '-';
	file->rights[8] = mode & S_IWOTH ? 'w' : '-';
	if (mode & S_IXOTH)
		file->rights[9] = mode & S_ISVTX ? 't' : 'x';
	else
		file->rights[9] = mode & S_ISVTX ? 'T' : '-';
	file->rights[10] = ' ';
	file->rights[11] = '\0';
}

t_file		*add_long_format(t_file *file, __uint8_t type)
{
	char		*temp;
	uintmax_t	tmp;
	struct stat	dirstr;
	
	//  && file->path[ft_strlen(file->path) - 1] == '/'
	file->rights[0] = what_type_is(type);
	if (file->rights[0] == 'l')
	{
		if (lstat((temp = ft_strjoin(file->path, file->name)), &dirstr) == -1)
			error(file->name, strerror(errno));
	}
	// else if (file->rights[0] == 'l')
	// {
	// 	if (lstat((temp = ft_strsub(file->path, 0, ft_strlen(file->path) - 1)), &dirstr) == -1)
	// 		error(file->name, strerror(errno));
	// 	printf("omg: %s\n", temp);
	// }
	else
	{
		if (stat(temp = ft_strjoin(file->path, file->name), &dirstr) == -1)
			error(file->name, strerror(errno));
	}
	printf("? %s\n", temp);
	
	file->addr->l_sign.ind.block = dirstr.st_blocks;
	file->addr->l_sign.ind.total += dirstr.st_blocks;
	file->l_sign.type = what_type_is(type);
	record_rights(file, dirstr.st_mode);
	file->l_sign.link_num = dirstr.st_nlink;
	if ((tmp = ft_count_digits_base(dirstr.st_nlink, 10)) > file->addr->l_sign.ind.link)
		file->addr->l_sign.ind.link = tmp;
	get_user_info(file, dirstr);
	get_group_info(file, dirstr);
	file->l_sign.size = dirstr.st_size;
	if ((tmp = ft_count_digits_base(dirstr.st_size, 10)) > file->addr->l_sign.ind.size)
		file->addr->l_sign.ind.size = tmp;
	file->l_sign.time = (time_t *)&dirstr.st_mtimespec;
	get_time(file);
	free(temp);
	return (file);
}

void		create_indentation(t_file *file)
{
	file->l_sign.ind.block = 0;
	file->l_sign.ind.link = 0;
	file->l_sign.ind.user = 0;
	file->l_sign.ind.group = 0;
	file->l_sign.ind.size = 0;
	file->l_sign.ind.date = 0;
	file->l_sign.ind.total = 0;
}

void		add_files_of_dir(t_file **tmp, struct dirent *ds)
{
	if (!(*tmp)->flags.a && ds->d_name[0] == '.')
		return;
	if ((*tmp)->name)
		add_not_a_dir(tmp, ds);
	else
		(*tmp)->name = ds->d_name;
	if ((*tmp)->flags.l)
	{
		(*tmp)->path = (*tmp)->addr->path;
		if (*tmp == (*tmp)->addr)
			create_indentation(*tmp);
		add_long_format(*tmp, ds->d_type);
	}
}*/

/*void		output_dir(t_file *ls)
{
	t_file	*tmp;

	tmp = ls;
	if (ls->flags.l)
		ft_printf("total %d\n", ls->addr->l_sign.ind.total);
	while (tmp)
	{
		output_long(tmp);
		tmp = tmp->next;
	}
}

void		open_dir(t_file **tmp)
{
	t_file			*inner_file;
	t_file			*temp;
	struct dirent	*ds;

	inner_file = new_file((*tmp)->flags);
	inner_file->path = (*tmp)->path;
	while ((ds = readdir((*tmp)->dir)))
		add_files_of_dir(&inner_file, ds);
	inner_file = inner_file->addr;
	if (inner_file->name)
	{
		sort(&inner_file);
		output_dir(inner_file);
	}
	while (inner_file)
	{
		// if (inner_file->flags.R && inner_file->err != ENOTDIR && inner_file->l_sign.type != 'l')
		// {}
		temp = inner_file;
		inner_file = inner_file->next;
		free(temp);
	}
	*tmp = (*tmp)->next;
}

void		output(t_file *file, t_file *dir)
{
	// int		num;
	t_file 	*tmp;

	// num = 0;
	if (file->name)
	{
		sort(&file);
		tmp = file;
		while (tmp)
		{
			if (tmp->flags.one)
				ft_printf("%s\n", tmp->name);
			else if (tmp->flags.l)
			{
				// ft_printf("%s", strerror(tmp->err));
				output_long(add_long_format(tmp, DT_REG));
			}
			tmp = tmp->next;
		}
		if (dir->name)
			printf("\n");
	}
	if (dir->name)
	{
		sort(&dir);
		tmp = dir;
		while (tmp)
		{
			printf("path: %s\n", tmp->path);
			if (error || file->name || dir->next)
				printf("%s:\n", tmp->name);
			if (tmp->err && tmp->err != ENOTDIR)
			{
				printf("./ft_ls: %s: %s\n", find_str(tmp->name), strerror(tmp->err));
				tmp = tmp->next;
			}
			else
				open_dir(&tmp);
			if (tmp)
				printf("\n");
		}
	}
}
*/

void		output_long(t_file *tmp)
{
	char	*buff;
	char	*temp;
	
	tmp->stat.ind = tmp->addr->stat.ind;
	ft_printf("%s %*d", tmp->rights, tmp->stat.ind.link, tmp->stat.link_num);
	if (tmp->flag & FG_N)
		ft_printf("%*d %*d", tmp->stat.ind.user + 1, tmp->stat.uid, tmp->stat.ind.group + 1, tmp->stat.gid);
	else
		ft_printf("%*s %*s", tmp->stat.ind.user + 1, tmp->stat.user_name, tmp->stat.ind.group + 1, tmp->stat.group_name);
	ft_printf("%*d %s %s", tmp->stat.ind.size + 2, tmp->stat.size, tmp->date, tmp->name);
	if (tmp->rights[0] == 'l')
	{
		temp = ft_strjoin(tmp->path, tmp->name);
		buff = ft_memalloc(4096);
		buff[4096] ='\0';
		readlink(temp, buff, 4095) > 0 ? ft_printf(" -> %s\n", buff) : 0;
		free(buff);
		free(temp);
	}
	else
		ft_printf("\n");
}

void		output(t_file *file)
{
	t_file *tmp;

	while (file)
	{
		if (file->name)
		{
			if (file->flag & FG_M && file->next)
				ft_printf("%s, ", file->name);
			else if ((file->flag & FG_ONE) || (file->flag & FG_M))
				ft_printf("%s\n", file->name);
			else if ((file->flag & FG_L) || (file->flag & FG_N))
				output_long(file);
		}
		tmp = file;
		file = file->next;
		// destroy_file(&tmp);
	}
}

void		get_date(t_file *file, time_t *time_s)
{
	uintmax_t	tmp;
	time_t		current_time;
	time_t		difference;
	char		*time_str;

	time_str = ctime(time_s);
	time(&current_time);
	ft_memcpy((void *)file->date, time_str + 4, 12);
	file->date[12] = '\0';
	if (current_time > *time_s)
		difference = current_time - *time_s;
	else
		difference = *time_s - current_time;
	if (difference > 15778463)
	{
		file->date[7] = ' ';
		ft_memcpy((void *)(file->date + 8), time_str + 20, 4);
	}
	if ((tmp = ft_strlen(time_str)) > file->stat.ind.date)
		file->stat.ind.date = tmp;
}

void		get_ug_indent(t_file *file)
{
	int				tmp;

	if (file->flag & FG_N)
	{
		if ((tmp = ft_count_digits_base(file->stat.uid, 10)) > file->stat.ind.user)
			file->stat.ind.user = tmp;
		if ((tmp = ft_count_digits_base(file->stat.gid, 10)) > file->stat.ind.group)
			file->stat.ind.group = tmp;
	}
	else
	{
		if ((tmp = ft_strlen(file->stat.user_name)) > file->stat.ind.user)
			file->stat.ind.user = tmp;
		if ((tmp = ft_strlen(file->stat.group_name)) > file->stat.ind.group)
			file->stat.ind.group = tmp;
	}
}

void		get_ug_name(t_file *file)
{
	struct passwd	*pwuser;
	struct group	*grpnam;

	if (!(pwuser = getpwuid(file->stat.uid)))
	{
		ft_printf("There's an error after trying to get user\n");
		exit(errno);
	}
	if (!(grpnam = getgrgid(file->stat.gid)))
	{
		ft_printf("There's an error after trying to get group\n");
		exit(errno);
	}
	file->stat.user_name = ft_strdup(pwuser->pw_name);
	file->stat.group_name = ft_strdup(grpnam->gr_name);
	get_ug_indent(file);
}

void		get_rights(t_file *file, mode_t mode)
{
	if (S_ISBLK(mode) || S_ISCHR(mode))
		file->rights[0] = S_ISBLK(mode) ? 'b' : 'c';
	else if (S_ISDIR(mode) || S_ISFIFO(mode))
		file->rights[0] = S_ISDIR(mode) ? 'd' : 'p';
	else if (S_ISLNK(mode) || S_ISREG(mode))
		file->rights[0] = S_ISLNK(mode) ? 'l' : '-';
	else
		file->rights[0] = S_ISSOCK(mode)? 's' : file->rights[0];
	file->rights[1] = mode & S_IRUSR ? 'r' : '-';
	file->rights[2] = mode & S_IWUSR ? 'w' : '-';
	if (mode & S_ISUID)
		file->rights[3] = mode & S_IXUSR ? 's' : 'S';
	else
		file->rights[3] = mode & S_IXUSR ? 'x' : '-';
	file->rights[4] = mode & S_IRGRP ? 'r' : '-';
	file->rights[5] = mode & S_IWGRP ? 'w' : '-';
	if (mode & S_ISGID)
		file->rights[6] = mode & S_IXGRP ? 's' : 'S';
	else
		file->rights[6] = mode & S_IXGRP ? 'x' : '-';
	file->rights[7] = mode & S_IROTH ? 'r' : '-';
	file->rights[8] = mode & S_IWOTH ? 'r' : '-';
	if (mode & S_ISVTX)
		file->rights[9] = mode & S_IXOTH ? 't' : 'T';
	else
		file->rights[9] = mode & S_IXOTH ? 'x' : '-';
}

void		get_stats(t_file *file)
{
	char		*temp;
	int			tmp;
	struct stat	ds;

	temp = ft_strjoin(file->path, file->name);
	if (lstat(temp, &ds) < 0)
		if (stat(temp, &ds) < 0)
			error(file->name, strerror(errno));
	file->stat.ind = file->addr->stat.ind;
	get_rights(file, ds.st_mode);
	file->rights[10] = ' ';
	file->rights[11] = '\0';
	file->stat.link_num = ds.st_nlink;
	if ((tmp = ft_count_digits_base(ds.st_nlink, 10)) > file->stat.ind.link)
		file->stat.ind.link = tmp;
	file->stat.uid = ds.st_uid;
	file->stat.gid = ds.st_gid;
	get_ug_name(file);
	file->stat.size = ds.st_size;
	if ((tmp = ft_count_digits_base(ds.st_size, 10)) > file->stat.ind.size)
		file->stat.ind.size = tmp;
	get_date(file, &ds.st_mtime);
	file->stat.ind.total += ds.st_blocks;
	file->addr->stat.ind = file->stat.ind;
	free(temp);
}

void		open_dir(t_file *dir)
{
	struct dirent	*dir_s;
	t_file			*new_dir;
	t_file			*tmp;


		new_dir = new_file();
		new_dir->flag = dir->flag;
		if (dir->flag & WR_PTH)
			ft_printf("%s:\n", dir->path ? dir->path : dir->name);
		if (dir->name[0] != '.' && dir->name[1] != '\0')
			new_dir->path = make_new_path(dir);
		while ((dir_s = readdir(dir->dir)))
		{
			if ((dir->flag & FG_A) || dir_s->d_name[0] != '.')
			{
				add_file(&new_dir, dir_s->d_name);
				get_stats(new_dir);
			}
		}
		tmp = dir;
		dir = dir->next;
		// destroy_file(&tmp);
		new_dir = new_dir->addr;
		sort(&new_dir);
		if ((new_dir->flag & FG_L) || (new_dir->flag & FG_N))
			ft_printf("total %d\n", new_dir->stat.ind.total);
		while (new_dir && new_dir->name)
		{
			if ((new_dir->flag & FG_L) || (new_dir->flag & FG_N))
				output_long(new_dir);
			if (new_dir->flag & FG_ONE)
				ft_printf("%s\n", new_dir->name);
			tmp = new_dir;
			new_dir = new_dir->next;
			// destroy_file(&tmp);
		}
		if (dir)
			write(1, "\n", 1);
}

void		find_errors(t_file **file, t_file **dir, char *str)
{
	DIR		*direct;

	if ((!(direct = opendir(str)) && errno == ENOENT) ||  (str[ft_strlen(str) - 1] == '/' && errno == ENOTDIR))
		error(str, strerror(errno));
	else if (errno == ENOTDIR)
	{
		add_file(file, str);
		get_stats(*file);
	}
	else
	{
		add_file(dir, str);
		get_stats(*dir);
		if ((*dir)->name)
			(*dir)->dir = direct;
	}
	errno = 0;
}

int		ft_parse_options(t_file *file, int argc, char **argv)
{
	int			i;
	int			j;

	i = 0;
	while (++i < argc && argv[i][0] == '-')
	{
		j = 0;
		while (argv[i][++j])
		{
			if (argv[i][j] == 'a' || argv[i][j] == 'f')
				file->flag |= argv[i][j] == 'f' ? FG_A | FG_F : FG_F;
			else if (argv[i][j] == '1' || argv[i][j] == 'r')
				file->flag |= argv[i][j] == 'r' ? FG_R : (((file->flag | FG_ONE)
					& ~FG_C) & ~FG_L) & ~FG_M;
			else if (argv[i][j] == 'l' || argv[i][j] == 'n')
				file->flag |= argv[i][j] == 'l' ? ((((file->flag | FG_L) &
					~FG_C) & ~FG_ONE) & ~FG_M) | FG_F : FG_L | FG_N;
			else if (argv[i][j] == 'g' || argv[i][j] == 'G')
				file->flag |= argv[i][j] == 'g' ? FG_L | FG_G : FG_COLOR;
			else if (argv[i][j] == 't' || argv[i][j] == 'u')
				file->flag |= argv[i][j] == 'u' ? FG_U : FG_T;
			else if (argv[i][j] == 'R' || argv[i][j] == 'd')
				file->flag |= argv[i][j] == 'R' ? FG_RECUR : ~FG_RECUR | FG_D;
			else if (argv[i][j] == 'm')
				file->flag |= ((FG_M & ~FG_ONE) & ~FG_L) & ~FG_C;
			else if (argv[i][j] == 'C' && !(file->flag & FG_M))
				file->flag |= (FG_C & ~FG_ONE) & ~FG_L;
			else if (argv[i][j] == 'h')
				file->flag |= FG_H;
			else if (argv[i][j] == '-' && !argv[i][j + 1])
				return (i + 1);
			else
				usage(argv[i][j]);
		}
	}
	return (i);
}

int		main(int argc, char **argv)
{
	int			i;
	t_file		*file;
	t_file		*dir;

	file = new_file();
	dir = new_file();
	i = ft_parse_options(dir, argc, argv);
	ft_quicksort_chars(argv, i, argc - 1);
	if (argc - i == 0)
	{
		find_errors(&file, &dir, ".");
		open_dir(dir->addr);
	}
	argc - i > 1 ? dir->flag |= WR_PTH : 0;
	file->flag = dir->flag;
	if (argc - i > 0)
	{
		while (i < argc)
		{
			find_errors(&file, &dir, argv[i]);
			i++;
		}
		if (file->name)
		{
			output(file->addr);
			dir->name ? write(1, "\n", 1): 0;
		}
		while (dir && dir->dir)
		{
			open_dir(dir->addr);
			dir = dir->next;
		}
	}
	// system("leaks ft_ls");
	// output(file ? file->addr : NULL, dir ? dir->addr : NULL, error ? error->addr : NULL);
	return (0);
}