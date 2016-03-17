/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 17:46:23 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/17 19:26:23 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_setenv(t_builtin *b)
{
	int		i;
	char	*new;

	i = 0;
	while (b->argv[i])
		i++;
	if (i > 3)
		ft_putendl_fd("setenv: too many arguments", 2);
	else
	{
		new = ft_strjoin(b->argv[1], "=");
		if (i == 3)
			new = ft_cjoin(new, ft_strdup(b->argv[2]));
	}
	clear_tab(b->envir);
	b->envir = ft_tab_add(b->envir, new);
}
