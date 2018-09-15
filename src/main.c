/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 09:28:36 by aroi              #+#    #+#             */
/*   Updated: 2018/09/15 17:59:55 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
//	What does "unknown" type of file mean?
//	errors output - check
//	error leaks
//

#include "ls.h"
// #include <stdio.h>
// #include <stdlib.h>

// #include <pwd.h>
// #include <grp.h>

// char	*find_str(char *name)
// {
// 	char *str;

// 	str = ft_strrchr(name, '/');
// 	if (!str)
// 		str = name;
// 	else
// 		str++;
// 	return (str);
// }

void	error(char *str)
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

void	usage(char c, char *str) //should be illegal option here? is ./ft_ls ? and error output
{
	ft_putstr_fd("ls: ", 2);
	ft_putstr_fd("illegal option -- ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("\nusage: ls [-Ralrt1] [file ...]\n", 2);
	// system("leaks ft_ls");
	exit(1);
}

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

t_file	*t_partition(t_file *left, t_file **left1, t_file *right, t_file **right1)
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
		if (left->flag & FG_R ? current->st.st_mtime - pivot->st.st_mtime <= 0 : current->st.st_mtime - pivot->st.st_mtime >= 0)
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

t_file	*not_t_partition(t_file *left, t_file **left1, t_file *right, t_file **right1)
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
		if (left->flag & FG_R ? ft_strcmp(current->name, pivot->name) >= 0 : ft_strcmp(current->name, pivot->name) <= 0)
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

t_file		*new_file()
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
	return (file);
}

int		add_file(t_file **file, char *str)
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
	free(tmp);
	*file = NULL;
}

char		*make_new_path(char *path, char *str)
{
	char	*new;
	char	*tmp;

	tmp = 0;
	new = 0;
	if (!path)
		new = ft_strdup(str);
	else
	{
		tmp = ft_strjoin(path, "/");
		new = ft_strjoin(tmp, str);
		free(tmp);
	}
	// printf("%s and %s\n", dir->path, dir->name);
	return (new);
}

/*void		get_time(t_file *file)
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

// void		output_long(t_file *tmp)
// {
// 	char	*buff;
// 	char	*temp;
	
// 	tmp->stat.ind = tmp->addr->stat.ind;
// 	ft_printf("%s %*d", tmp->rights, tmp->stat.ind.link, tmp->stat.link_num);
// 	if (tmp->flag & FG_N)
// 		ft_printf("%*d %*d", tmp->stat.ind.user + 1, tmp->stat.uid, tmp->stat.ind.group + 1, tmp->stat.gid);
// 	else
// 		ft_printf("%*s %*s", tmp->stat.ind.user + 1, tmp->stat.user_name, tmp->stat.ind.group + 1, tmp->stat.group_name);
// 	ft_printf("%*d %s %s", tmp->stat.ind.size + 2, tmp->stat.size, tmp->date, tmp->name);
// 	if (tmp->rights[0] == 'l')
// 	{
// 		temp = ft_strjoin(tmp->path, tmp->name);
// 		buff = ft_memalloc(4096);
// 		buff[4096] ='\0';
// 		readlink(temp, buff, 4095) > 0 ? ft_printf(" -> %s\n", buff) : 0;
// 		free(buff);
// 		free(temp);
// 	}
// 	else
// 		ft_printf("\n");
// }

// void		output(t_file *file)
// {
// 	t_file *tmp;

// 	while (file)
// 	{
// 		if (file->name)
// 		{
// 			if (file->flag & FG_M && file->next)
// 				ft_printf("%s, ", file->name);
// 			else if ((file->flag & FG_ONE) || (file->flag & FG_M))
// 				ft_printf("%s\n", file->name);
// 			else if ((file->flag & FG_L) || (file->flag & FG_N))
// 				output_long(file);
// 		}
// 		tmp = file;
// 		file = file->next;
// 		// destroy_file(&tmp);
// 	}
// }

void		write_acl(t_file *file)
{
	char	**tmp;
	char	*text;
	
	text = acl_to_text(file->acl, NULL);
	tmp = ft_strsplit(ft_strchr(text, '\n') + 1, ':');
	write(1, " 0: ", 4);
	write(1, tmp[0], ft_strlen(tmp[0]));
	write(1, ":", 1);
	write(1, tmp[2], ft_strlen(tmp[2]));
	write(1, " ", 1);
	write(1, tmp[4], ft_strlen(tmp[4]));
	write(1, " ", 1);
	write(1, tmp[5], ft_strlen(tmp[5]));
	free(text);
	ft_freearr((void **)tmp);
}

void		get_date(t_file *file)
{
	uintmax_t	tmp;
	time_t		current_time;
	time_t		difference;
	char		*time_str;

	time_str = ctime(&file->st.st_mtime);
	time(&current_time);
	file->date[13] = '\0';
	ft_memcpy((void *)file->date, time_str + 4, 12);
	if (current_time > file->st.st_mtime)
		difference = current_time - file->st.st_mtime;
	else
		difference = file->st.st_mtime - current_time;
	if (difference > 15778463)
		ft_memcpy((void *)(file->date + 7), ft_strrchr(time_str, ' '), 6);
	!ft_isdigit(file->date[12]) ? file->date[12] = '\0' : 0;
	if ((tmp = ft_strlen(time_str)) > file->addr->ind.date)
		file->addr->ind.date = tmp;
}

void		get_ug_indent(t_file *file)
{
	int				tmp;

	if (file->flag & FG_N)
	{
		if ((tmp = ft_count_digits_base(file->st.st_uid, 10)) > file->addr->ind.user)
			file->addr->ind.user = tmp;
		if ((tmp = ft_count_digits_base(file->st.st_gid, 10)) > file->addr->ind.group)
			file->addr->ind.group = tmp;
	}
	else
	{
		if ((tmp = ft_strlen(file->user)) > file->addr->ind.user)
			file->addr->ind.user = tmp;
		if ((tmp = ft_strlen(file->group)) > file->addr->ind.group)
			file->addr->ind.group = tmp;
	}
}

void		get_ug_name(t_file *file)
{
	struct passwd	*pwuser;
	struct group	*grpnam;

	if (!(pwuser = getpwuid(file->st.st_uid)))
	{
		ft_printf("There's an error after trying to get user\n");
		exit(errno);
	}
	if (!(grpnam = getgrgid(file->st.st_gid)))
	{
		ft_printf("There's an error after trying to get group\n");
		exit(errno);
	}
	if (file->user)
		free(file->user);
	file->user = ft_strdup(pwuser->pw_name);
	if (file->group)
		free(file->group);
	file->group = ft_strdup(grpnam->gr_name);
	get_ug_indent(file);
}

void		get_rights(t_file *file)
{
	if (S_ISBLK(file->st.st_mode) || S_ISCHR(file->st.st_mode))
		file->rights[0] = S_ISBLK(file->st.st_mode) ? 'b' : 'c';
	else if (S_ISDIR(file->st.st_mode) || S_ISFIFO(file->st.st_mode))
		file->rights[0] = S_ISDIR(file->st.st_mode) ? 'd' : 'p';
	else if (S_ISLNK(file->st.st_mode) || S_ISREG(file->st.st_mode))
		file->rights[0] = S_ISLNK(file->st.st_mode) ? 'l' : '-';
	else
		file->rights[0] = S_ISSOCK(file->st.st_mode)? 's' : file->rights[0];
	file->rights[1] = file->st.st_mode & S_IRUSR ? 'r' : '-';
	file->rights[2] = file->st.st_mode & S_IWUSR ? 'w' : '-';
	if (file->st.st_mode & S_ISUID)
		file->rights[3] = file->st.st_mode & S_IXUSR ? 's' : 'S';
	else
		file->rights[3] = file->st.st_mode & S_IXUSR ? 'x' : '-';
	file->rights[4] = file->st.st_mode & S_IRGRP ? 'r' : '-';
	file->rights[5] = file->st.st_mode & S_IWGRP ? 'w' : '-';
	if (file->st.st_mode & S_ISGID)
		file->rights[6] = file->st.st_mode & S_IXGRP ? 's' : 'S';
	else
		file->rights[6] = file->st.st_mode & S_IXGRP ? 'x' : '-';
	file->rights[7] = file->st.st_mode & S_IROTH ? 'r' : '-';
	file->rights[8] = file->st.st_mode & S_IWOTH ? 'w' : '-';
	if (file->st.st_mode & S_ISVTX)
		file->rights[9] = file->st.st_mode & S_IXOTH ? 't' : 'T';
	else
		file->rights[9] = file->st.st_mode & S_IXOTH ? 'x' : '-';
}

int			get_stats(t_file *file)
{
	int			tmp;
	char		*path;

	get_rights(file);
	path = file->path ? file->path : file->name;
	file->acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	file->rights[10] = file->acl ? '+' : ' ';
	if (listxattr(path, NULL, 0, XATTR_NOFOLLOW) > 0)
		file->rights[10] = '@';
	else
		errno = 0;
	file->rights[11] = '\0';
	if ((tmp = ft_count_digits_base(file->st.st_nlink, 10)) > file->addr->ind.link)
		file->addr->ind.link = tmp;
	get_ug_name(file);
	if ((tmp = ft_count_digits_base(file->st.st_size, 10)) > file->addr->ind.size)
		file->addr->ind.size = tmp;
	get_date(file);
	file->addr->ind.total += file->st.st_blocks;
	file->ind = file->addr->ind;
	return (1);
}

void		output_long(t_file *file)
{
	char	*buff;
	char	*temp;

	ft_printf("%s %*d ", file->rights, file->addr->ind.link, file->st.st_nlink);
	if (file->flag & FG_N)
		ft_printf("%-*d  %-*d  ", file->addr->ind.user, file->st.st_uid, file->addr->ind.group, file->st.st_gid);
	else
		ft_printf("%-*s  %-*s  ", file->addr->ind.user, file->user, file->addr->ind.group, file->group);
	if (file->rights[0] != 'b' && file->rights[0] != 'c')
		ft_printf("%*d %s %s", file->addr->ind.size, file->st.st_size, file->date, file->name);
	else
		ft_printf("%3d, %3d %s %s", major(file->st.st_rdev), minor(file->st.st_rdev), file->date, file->name);
	if (file->rights[0] == 'l')
	{
		buff = ft_memalloc(4096);
		buff[4096] ='\0';
		if (file->path)
			readlink(file->path, buff, 4095) > 0 ? ft_printf(" -> %s\n", buff) : 0;
		else
			readlink(file->name, buff, 4095) > 0 ? ft_printf(" -> %s\n", buff) : 0;
		free(buff);
	}
	else
		ft_printf("\n");
	file->acl && (file->flag & FG_ACL) ? write_acl(file) : 0;
}

void	output_file(t_file *file)
{
	if (file->flag & FG_M)
		ft_printf("%s, ", file->name);
	else if (file->flag & FG_L)
		output_long(file);
	else
	// else if (file->flag & FG_ONE)
		ft_putendl(file->name);
	// else
	// 	ft_printf("No realisation yet\n");
	// 	output_columns(file);	
}

void		get_info(t_file **file, char *path, char *str)
{
	add_file(file, str);
	ft_strdel(&(*file)->path);
	(*file)->path = make_new_path(path, str);
	lstat((*file)->path, &(*file)->st) < 0 ? stat((*file)->path, &(*file)->st) : 0;
	get_stats(*file);
}

// void		open_dir(t_file *dir)
// {
// 	struct dirent	*dir_s;
// 	t_file			*new_dir;
// 	t_file			*tmp;


// 		new_dir = new_file();
// 		new_dir->flag = dir->flag;
// 		if (dir->flag & WR_PTH)
// 			ft_printf("%s:\n", dir->path ? dir->path : dir->name);
// 		if (dir->name[0] != '.' && dir->name[1] != '\0')
// 			new_dir->path = make_new_path(dir);
// 		while ((dir_s = readdir(dir->dir)))
// 		{
// 			if ((dir->flag & FG_A) || dir_s->d_name[0] != '.')
// 			{
// 				add_file(&new_dir, dir_s->d_name);
// 				get_stats(new_dir);
// 			}
// 		}
// 		tmp = dir;
// 		dir = dir->next;
// 		closedir(tmp->dir);
// 		// destroy_file(&tmp);
// 		new_dir = new_dir->addr;
// 		sort(&new_dir);
// 		if ((new_dir->flag & FG_L) || (new_dir->flag & FG_N))
// 			ft_printf("total %d\n", new_dir->stat.ind.total);
// 		while (new_dir && new_dir->name)
// 		{
// 			if ((new_dir->flag & FG_L) || (new_dir->flag & FG_N))
// 				output_long(new_dir);
// 			if (new_dir->flag & FG_ONE)
// 				ft_printf("%s\n", new_dir->name);
// 			tmp = new_dir;
// 			new_dir = new_dir->next;
// 			destroy_file(&tmp);
// 		}
// 		if (dir)
// 			write(1, "\n", 1);
// }

void		open_dir(t_file *directory)
{
	DIR				*dir;
	struct dirent	*ds;
	t_file			*file;
	t_file			*tmp;
	t_file			*iter;
	char			*helper;

	helper = directory->path ? directory->path : directory->name;
	file = new_file();
	directory->flag |= directory->flag & IS_FILE ? write(1, "\n", 1) & 0 : IS_FILE;
	directory->flag & WR_PTH ? ft_printf("%s:\n", helper) : 0;//sadasd
	directory->flag |= WR_PTH;
	file->flag = directory->flag;
	if (!(dir = opendir(helper)))
	{
		error(directory->name);
		destroy_file(&file);
		return ;
	}
	while ((ds = readdir(dir)))
	{
		if (!(directory->flag & FG_A) && ds->d_name[0] == '.')
			continue ;
		get_info(&file, helper, ds->d_name);
	}
	file = file->addr;
	if (!file->name)
	{
		while (file)
		{
			tmp = file;
			file = file->next;
			destroy_file(&tmp);
		}
		closedir(dir);
		return ;
	}
	if (!(file->flag & FG_F))
	{
		sort(&file, 0);
		file->flag & FG_T ? sort(&file, FG_T) : 0;
	}
	file->flag & FG_L ? ft_printf("total %d\n", file->ind.total) : 0;
	iter = file;
	while (iter)
	{
		output_file(iter);
		iter = iter->next;
	}
	while (file)
	{
		if ((file->name[0] != '.' || file->name[1]) && (file->name[0] != '.' || file->name[1] != '.'))
			S_ISDIR(file->st.st_mode) && (file->flag & FG_RECUR) ? open_dir(file) : 0;
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
			output_file(iter);
		}
		iter = iter->next;
	}
	(file->flag & FG_M)? write(1, "\n", 1) : 0;
	return (file->addr);
}

int		is_option(char c, u_int32_t *flag)
{
	// *flag = 0;
	if (c == 'a' || c == 'f')
		(*flag) |= c == 'f' ? FG_A | FG_F : FG_A;
	else if (c == '1' || c == 'r')
		(*flag) |= c == 'r' ? FG_R : ((((*flag) | FG_ONE)
			& ~FG_C) & ~FG_L) & ~FG_M;
	else if (c == 'l' || c == 'n')
		(*flag) |= c == 'l' ? (((((*flag) | FG_L) &
			~FG_C) & ~FG_ONE) & ~FG_M) : FG_L | FG_N;
	else if (c == 'g' || c == 'G')
		(*flag) |= c == 'g' ? FG_L | FG_G : FG_COLOR;
	else if (c == 't' || c == 'u')
		(*flag) |= c == 'u' ? FG_U : FG_T;
	else if (c == 'R' || c == 'd')
		(*flag) |= c == 'R' ? FG_RECUR : ~FG_RECUR | FG_D;
	else if (c == 'm')
		(*flag) |= ((((*flag) | FG_M) & ~FG_ONE) & ~FG_L) & ~FG_C;
	else if (c == 'C' && !((*flag) & FG_M))
		(*flag) |= (FG_C & ~FG_ONE) & ~FG_L;
	else if (c == 'h' || c == 'e')
		(*flag) |= c == 'h' ? FG_H : FG_ACL;
	else if (c == '@')
		(*flag) |= FG_EA;
	else
		return (0);
	return (1);
}

int		ft_parse_options(t_file *file, int argc, char **argv)
{
	int			i;
	int			j;

	i = 0;
	while (++i < argc && argv[i][0] == '-')
	{
		j = 0;
		if (argv[i][1] == 0)
		{
			file->flag & FG_F ? 0 : ft_quicksort_chars(argv, i, argc - 1);
			return (i - 1);
		}
		while (argv[i][++j])
			if (!is_option(argv[i][j], &file->flag))
			{
				if (argv[i][j] == '-' && !argv[i][j + 1])
				{
					file->flag & FG_F ? 0 : ft_quicksort_chars(argv, i + 1, argc - 1);
					return (i);
				}
				else
					usage(argv[i][j], argv[0]);
			}
	}
	file->flag & FG_F ? 0 : ft_quicksort_chars(argv, i, argc - 1);
	return (i - 1);
}

int		main(int argc, char **argv)
{
	int			index;
	int			i;
	struct stat	ds;
	t_file		*file;

	file = new_file();
	i = ft_parse_options(file, argc, argv);
	if (argc == i + 1)
		stat(".", &file->st) == 0 ? add_file(&file, ".") : error(".");
	(argc - i > 2)? file->flag |= WR_PTH : 0;
	while (++i < argc)
	{
		// if (file->flag & FG_L)
		// {

			if (file->flag & FG_L || (index = stat(argv[i], &ds)) < 0)
				(index = lstat(argv[i], &ds)) < 0 ? error(argv[i]) : 0;

		// }
		// else
		// {
			// (index = lstat(argv[i], &ds)) < 0 ? error(argv[i]) : 0;
			// 	ft_printf("soska\n");
		// }

		index == 0 ? add_file(&file, argv[i]) && ft_memcpy(&file->st, &ds,
			sizeof(struct stat)) && get_stats(file) : 0;
	}
	if (!(file->flag & FG_F))
	{
		sort(&file->addr, 0);
		file->flag & FG_T ? sort(&file->addr, FG_T) : 0;
	}
	file = write_files(file->addr);
	while (file->next)
	{
		// ft_printf("name: %s\n", file->name);
		S_ISDIR(file->st.st_mode) ? open_dir(file) : 0;
		file = file->next;
		file->flag |= IS_FILE;
	}
	S_ISDIR(file->st.st_mode) ? open_dir(file) : 0;

	// system("leaks ft_ls");
	return (0);
}