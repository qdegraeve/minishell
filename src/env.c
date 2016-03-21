/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 17:46:23 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/21 22:11:52 by qdegraev         ###   ########.fr       */
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
		env_options(b, b->argv[i]);
		b->argv = ft_tab_remove(b->argv, i);
	}
	if (!b->env_i)
		b->env_cpy = ft_tab_strcpy(b->env);
	if (b->env_u)
	{
		unset_env_one(b->argv[0], &b->env_cpy);
		b->argv = ft_tab_remove(b->argv, 0);
	}
	else
	{
		b->env_or_cpy = 1;
		exec_setenv(b);
	}
	if (b->argv[0])
	{
		get_path(b->argv[0], b);
		return ;
	}
	else
	{
		while (b->env_cpy[i])
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

void	unset_env_one(char *remove, char ***env)
{
	int		j;

	j = 0;
	while (*env[j])
	{
		if (ft_strncmp(remove, *env[j], ft_strlen(remove)) == 0)
		{
			*env = ft_tab_remove(*env, j);
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
		unset_env_one(b->argv[i], &b->env);
		i++;
	}
}
