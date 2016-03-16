/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 15:26:58 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/16 16:42:19 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_home(t_builtin *b)
{
	char			*path;
	struct stat		stat;


	path = ft_strjoin(b->envir[b->home] + 5, b->argv[1] + 1);
	if (lstat(path, &stat) != 0)
	{
		ft_putendl_fd("erreur lstat", 2);
		exit(EXIT_FAILURE);
	}
	if (!S_ISDIR(stat.st_mode))
	{
		ft_putstr_fd(b->argv[1], 2);
		ft_putendl_fd(": not a directory", 2);
		exit(EXIT_FAILURE);
	}
	else
	{
	ft_printf("b->pwd == [%d]\nb->path == [%d]\nb->envir == %s\npath == %s\n",b->pwd, b->path, b->envir[b->home], path);
	chdir(path);
	ft_strdel(&path);
	}
}

void	exec_cd(t_builtin *b)
{
	if (b->argv[2])
	{
		ft_putstr_fd("cd: string not in pwd:", 2);
		ft_putendl_fd(b->argv[1], 2);
		exit(EXIT_FAILURE);
	}
	else
	{
		if (b->argv[1][0] == '~')
			cd_home(b);
//		else if (b->argv[1][0] == '/')
//			pipi;
//		else
//			prout;
	}
}
