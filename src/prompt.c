/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 16:47:58 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/25 16:54:03 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd_prompt(char *path)
{
	int		i;

	i = ft_strlen(path);
	while (path[i] != '/')
		i--;
	return (path + i + 1);
}

void	prompt(int error)
{
	char	*path;

	path = NULL;
	ft_putstr_fd("\033[1;36m", 1);
	if (error)
		ft_printf("⚰  %s \033[1;31m: > ", get_pwd_prompt(getcwd(path, 255)));
	else
		ft_printf("💸  %s \033[1;32m: > ", get_pwd_prompt(getcwd(path, 255)));
	ft_putstr_fd("\033[0m", 1);
}

char	**get_argv(t_builtin *b)
{
	char	*line;
	char	**argv;
	int		g;

	line = NULL;
	argv = NULL;
	g = 0;
	b->error ? prompt(1) : prompt(0);
	if (get_next_line(0, &line) == 0)
		exec_exit(b);
	while (line && line[g])
	{
		if (line[g] == '\t')
			line[g] = ' ';
		g++;
	}
	argv = ft_strsplit(line, ' ');
	if (line)
		ft_strdel(&line);
	return (argv);
}
