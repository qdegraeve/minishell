/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 17:39:03 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/21 18:44:22 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env_index(t_builtin **b)
{
	int		i;

	i = 0;
	DEBUG
	while ((*b)->env && (*b)->env[i])
	{
		DEBUG
		if (!ft_strncmp((*b)->env[i], "PATH=", 5))
			(*b)->path_e = i;
		else if (!ft_strncmp((*b)->env[i], "HOME=", 5))
			(*b)->home = i;
		else if (!ft_strncmp((*b)->env[i], "PWD=", 4))
			(*b)->pwd = i;
		else if (!ft_strncmp((*b)->env[i], "OLDPWD=", 7))
			(*b)->oldpwd = i;
		i++;
	}
}

void	exec_exit(t_builtin *b)
{
	b->error = 1;
	exit(EXIT_SUCCESS);
}

void	get_command(char *command, t_builtin *b)
{
	int			i;
	t_commands	code_error[6] = {{"cd", &exec_cd}, \
	{"env", &exec_env},
	{"setenv", &exec_setenv},
	{"unsetenv", &exec_unsetenv},
	{"exit", &exec_exit},
	{"quit", &exec_exit}};

	i = 0;
	get_env_index(&b);
	while (i < 6)
	{
		if (!ft_strcmp(command, code_error[i].id))
		{
			DEBUG
			b->argv = ft_tab_remove(b->argv, 0);
			code_error[i].f(b);
			return ;
		}
		i++;
	}
}

void	get_path(char *command, t_builtin *b)
{
	char	*path;
	char	**test;
	int		i;

	path = NULL;
	test = NULL;
	if (b->env[0])
		test = ft_strsplit(b->env[b->path_e] + 5, ':');
	i = 0;
	while (test && test[i])
	{
		test[i] = ft_cjoin(test[i], ft_strdup("/"));
		path = ft_strjoin(test[i], command);
		if (access(path, X_OK) == 0)
		{
			b->path = path;
			return ;
		}
		else
			ft_strdel(&path);
		i++;
	}
}
