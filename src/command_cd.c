/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 15:26:58 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/25 17:12:42 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_home(t_builtin *b, char *path)
{
	t_stat		stat;
	char		*pwd;

	pwd = NULL;
	if (lstat(path, &stat) != 0)
	{
		b->error = 1;
		ft_strdel(&path);
		return ;
	}
	if (!S_ISDIR(stat.st_mode))
	{
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putendl_fd(b->argv[0], 2);
		ft_strdel(&path);
		b->error = 1;
		return ;
	}
	else
	{
		set_env_one(b, ft_cjoin(ft_strdup("OLDPWD="), getcwd(pwd, 255)), 7);
		chdir(path);
		ft_strdel(&path);
		set_env_one(b, ft_cjoin(ft_strdup("PWD="), getcwd(path, 255)), 4);
	}
}

void	cd_path(t_builtin *b)
{
	char			*path;
	char			*pwd;

	pwd = NULL;
	if (b->argv[0][0] == '~')
		path = ft_strjoin(b->env[b->home] + 5, b->argv[0] + 1);
	else if (b->argv[0][0] == '/')
		path = ft_strdup(b->argv[0]);
	else
	{
		path = ft_cjoin(getcwd(pwd, 255), ft_strdup("/"));
		path = ft_cjoin(path, ft_strdup(b->argv[0]));
	}
	cd_home(b, path);
}

void	cd_no_home(t_builtin *b)
{
	b->error = 1;
	ft_putendl_fd("cd: no home directory", 2);
}

void	exec_cd(t_builtin *b)
{
	char		*pwd;

	pwd = NULL;
	if (!b->argv[0])
	{
		if (b->home != -1)
		{
			set_env_one(b, ft_cjoin(ft_strdup("OLDPWD="), getcwd(pwd, 255)), 7);
			chdir(b->env[b->home] + 5);
			set_env_one(b, ft_cjoin(ft_strdup("PWD="), getcwd(pwd, 255)), 4);
		}
		else
			cd_no_home(b);
		return ;
	}
	if (b->argv[1])
	{
		ft_putstr_fd("cd: string not in pwd:", 2);
		ft_putendl_fd(b->argv[0], 2);
		b->error = 1;
		exit(EXIT_FAILURE);
	}
	else
		cd_path(b);
}
