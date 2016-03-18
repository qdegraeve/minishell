/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 17:46:23 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/18 18:28:31 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_env	(t_builtin *b)
{
	int		i;

	i = 0;
	while (b->argv[i])
		i++;
	if (i > 1)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(b->argv[1], 2);
		ft_putendl_fd(": no such file or directory", 2);
		return ;
	}
	else
	{
		i = 0;
		while (b->env[i])
			ft_printf("%s\n", b->env[i++]);
	}
}

void	exec_setenv(t_builtin *b)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (b->argv[i])
		i++;
	if (i > 3)
	{
		ft_putendl_fd("setenv: too many arguments", 2);
		return ;
	}
	else
	{
		new = ft_strjoin(b->argv[1], "=");
		if (i == 3)
			new = ft_cjoin(new, ft_strdup(b->argv[2]));
	}
	b->env = ft_tab_add(b->env, new);
}

void	exec_unsetenv(t_builtin *b)
{
	int		i;
	int		j;

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
		j = 0;
		while (b->env[j])
		{
			if (ft_strncmp(b->argv[i], b->env[j], ft_strlen(b->argv[i])) == 0)
			{
				b->env = ft_tab_remove(b->env, j);
				break ;
			}
			j++;
		}
		i++;
	}
}
