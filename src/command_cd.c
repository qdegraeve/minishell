/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 15:26:58 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/18 15:48:13 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_home(t_builtin *b, char *path)
{
	struct stat		stat;


	if (lstat(path, &stat) != 0)
	{
		ft_putendl_fd("erreur lstat", 2);
		ft_strdel(&path);
		return ;
	}
	if (!S_ISDIR(stat.st_mode))
	{
		ft_putstr_fd("cd: not a directory: ", 2);
		ft_putendl_fd(b->argv[1], 2);
		ft_strdel(&path);
		return ;
	}
	else
	{
		ft_strdel(&b->env[b->oldpwd]);
		b->env[b->oldpwd] = ft_strjoin("OLPWD=", b->env[b->pwd] + 4);
		chdir(path);
		ft_strdel(&b->env[b->pwd]);
		ft_strdel(&path);
		b->env[b->pwd] = ft_cjoin(ft_strdup("PWD="), getcwd(path, 255));
	}
}

void	cd_path(t_builtin *b)
{
	char			*path;

	if (b->argv[1][0] == '~')
		path = ft_strjoin(b->env[b->home] + 5, b->argv[1] + 1);
	else if (b->argv[1][0] == '/')
		path = ft_strdup(b->argv[1]);
	else
	{
		path = ft_strjoin(b->env[b->pwd] + 4, "/");
		path = ft_cjoin(path, ft_strdup(b->argv[1]));
	}
	cd_home(b, path);
}

void	exec_cd(t_builtin *b)
{
	if (!b->argv[1])
	{
		ft_strdel(&b->env[b->oldpwd]);
		b->env[b->oldpwd] = ft_strjoin("OLPWD=", b->env[b->pwd] + 4);
		chdir(b->env[b->home] + 5);
		ft_strdel(&b->env[b->pwd]);
		b->env[b->pwd] = ft_strjoin("PWD=", b->env[b->home] + 5);
		return ;
	}
	if (b->argv[2])
	{
		ft_putstr_fd("cd: string not in pwd:", 2);
		ft_putendl_fd(b->argv[1], 2);
		exit(EXIT_FAILURE);
	}
	else
		cd_path(b);
}
