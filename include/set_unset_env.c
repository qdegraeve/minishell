/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_unset_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 12:39:03 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/25 13:17:58 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		search_str(char a, char *str)
{
	int		i;

	i = 0;
	if (str)
	{
		while (str[i] && str[i] != a)
			i++;
	}
	if (str[i] == a)
		return (i);
	else
		return (-1);
}

void	set_env_one(t_builtin *b, char *add, char **env, int j)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], add, j) == 0)
		{
			ft_strdel(&env[i]);
			env[i] = add;
			b->argv = ft_tab_remove(b->argv, 0);
			exec_setenv(b);
			return ;
		}
		i++;
	}
	b->env = ft_tab_add(b->env, add);
	b->argv = ft_tab_remove(b->argv, 0);
}

void	exec_setenv(t_builtin *b)
{
	char	*new;
	int		j;

	j = 0;
	new = NULL;
	while (b->argv[0] && (j = search_str('=', b->argv[0])) >= 0)
	{
		new = ft_strdup(b->argv[0]);
		set_env_one(b, new, b->env_or_cpy ? b->env_cpy : b->env, j);
	}
}

void	unset_env_one(char *remove, char **env)
{
	int		j;

	j = 0;
	while (env[j])
	{
		if (ft_strncmp(remove, env[j], ft_strlen(remove)) == 0)
		{
			env = ft_tab_remove(env, j);
			break ;
		}
		j++;
	}
}

void	exec_unsetenv(t_builtin *b)
{
	int		i;

	i = 0;
	while (b->argv[i])
		i++;
	if (i < 2)
	{
		ft_putendl_fd("unsetenv: too few arguments", 2);
		return ;
	}
	i = 1;
	while (b->argv[i])
	{
		unset_env_one(b->argv[i], b->env);
		i++;
	}
}
