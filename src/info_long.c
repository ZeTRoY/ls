/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_long.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroi <aroi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 20:33:21 by aroi              #+#    #+#             */
/*   Updated: 2019/01/19 21:04:13 by aroi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

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
		if ((tmp = ft_count_digits_base(file->st.st_uid, 10)) >
				file->addr->ind.user)
			file->addr->ind.user = tmp;
		if ((tmp = ft_count_digits_base(file->st.st_gid, 10)) >
				file->addr->ind.group)
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

static void	get_type(char *type, mode_t mode)
{
	if (S_ISBLK(mode) || S_ISCHR(mode))
		*type = S_ISBLK(mode) ? 'b' : 'c';
	else if (S_ISDIR(mode) || S_ISFIFO(mode))
		*type = S_ISDIR(mode) ? 'd' : 'p';
	else if (S_ISLNK(mode) || S_ISREG(mode))
		*type = S_ISLNK(mode) ? 'l' : '-';
	else
		*type = S_ISSOCK(mode) ? 's' : *type;
}

void		get_rights(t_file *file)
{
	get_type(&file->rights[0], file->st.st_mode);
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
