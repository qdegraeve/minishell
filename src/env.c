/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 17:46:23 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/21 18:55:46 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_options(t_builtin *b, char *av)
{
	int		i;

	i = 0;
	while (av[i])
	{
		if (av[i] == 'u')
			b->env_u = 1;
		else if (av[i] == 'P')
			b->env_p = 1;
		else if (av[i] == 'i')
			b->env_i = 1;
		else if (av[i] == 'v')
			b->env_v = 1;
		i++;
	}
	b->env_or_cpy = 1;
}

void	exec_env(t_builtin *b)
{
	int		i;
	int		j;

	i = 0;

	j = 0;
	if (!b->argv[0])
	{
		while (b->env[i])
			ft_printf("%s\n", b->env[i++]);
		return ;
	}
	while (b->argv[i][0] == '-')
	{
		DEBUG
		env_options(b, b->argv[i]);
		b->argv = ft_tab_remove(b->argv, i);
	}
	if (!b->env_i)
		b->env_cpy = ft_tab_strcpy(b->env);
	DEBUG
	if (b->env_u)
	{
		DEBUG
		unset_env_one(b, b->argv[0]);
		b->argv = ft_tab_remove(b->argv, 0);
	}
	else
	{
		b->env_or_cpy = 1;
		exec_setenv(b);
	}
	if (b->argv[0])
	{
		DEBUG
		get_path(b->argv[0], b);
		return ;
	}
	else
	{
		DEBUG
		while ( b->env_cpy[i])
		{
			DEBUG
			ft_printf("%s\n", b->env_cpy[i]);
			i++;
		}
		return ;
	}
}

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

void	exec_setenv(t_builtin *b)
{
	int		i;
	int		j;
	char	*new;
	char	**env;

	j = 0;
	new = NULL;
	env = b->env_or_cpy ? b->env_cpy : b->env;
	while (b->argv[0] && (j = search_str('=', b->argv[0])) >= 0)
	{
		i = 0;
		new = ft_strdup(b->argv[0]);
		while (env[i])
		{
			if (ft_strncmp(env[i], new, j) == 0)
			{
				ft_strdel(&env[i]);
				env[i] = new;
			}
			i++;
		}
		if (!env[i])
			env = ft_tab_add(env, new);
		DEBUG
		b->argv = ft_tab_remove(b->argv, 0);
	}
}

void	unset_env_one(t_builtin *b, char *remove)
{
	int		j;
	char	**env;

	j = 0;
	env = b->env_or_cpy ? b->env_cpy : b->env;
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
		unset_env_one(b, b->argv[i]);
		i++;
	}
}
