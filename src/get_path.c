/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 17:39:03 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/17 19:00:30 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env_index(t_builtin **b)
{
	int		i;

	i = 0;
	while ((*b)->envir[i])
	{
		if (!ft_strncmp((*b)->envir[i], "PATH=", 5))
			(*b)->path = i;
		else if (!ft_strncmp((*b)->envir[i], "HOME=", 5))
			(*b)->home = i;
		else if (!ft_strncmp((*b)->envir[i], "PWD=", 4))
			(*b)->pwd = i;
		else if (!ft_strncmp((*b)->envir[i], "OLDPWD=", 7))
			(*b)->oldpwd = i;
		i++;
	}

}

char	*get_command(char *command, t_builtin *b)
{
	if (!ft_strcmp(command, b->quit) || !ft_strcmp(command, b->exit))
		exit(EXIT_SUCCESS);
	get_env_index(&b);
	if (!ft_strcmp(command, b->cd))
		return (NULL);
	else
		return (get_path(command, b));
}

char	*get_path(char *command, t_builtin *b)
{
	char	*path;
	char	**test;
	int		i;

	test = ft_strsplit(b->envir[b->path] + 5, ':');
	i = 0;
	while (test[i])
	{
		test[i] = ft_cjoin(test[i], ft_strdup("/"));
		path = ft_strjoin(test[i], command);
		if (access(path, X_OK) == 0)
			return (path);
		else
			ft_strdel(&path);
		i++;
	}
	return (NULL);
}
