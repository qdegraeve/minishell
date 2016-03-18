/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:41:00 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/18 18:31:57 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

char	**get_argv()
{
	char *line;
	char **caca;

	line = NULL;
	ft_putstr_fd("\033[31m", 1);
	ft_putstr_fd("ecris sale batard : > ", 1);
	ft_putstr_fd("\033[0m", 1);
	get_next_line(0, &line);
	caca = ft_strsplit(line, ' ');
	if (line)
		ft_strdel(&line);
	return (caca);
}

void	init_builtin(t_builtin *b, char **env)
{
	b->env = env;
	b->error = 0;
}

void	loop_fork(char **env, t_builtin b)
{
	pid_t	parent;
	char	**argv;
	char	*path;


	argv = NULL;
	path = NULL;
	init_builtin(&b, env);
	while(42)
	{
		b.argv = get_argv();
		if (b.argv[0])
			path = get_command(b.argv[0], &b);
		parent = fork();
		if (parent > 0)
		{
			wait(NULL);
		}
		else if (parent == -1)
		{
			ft_printf("father = %d\n", parent);
			exit(EXIT_FAILURE);
		}
		else if (parent == 0)
		{
			if (path)
				execve(path, b.argv, b.env);
			exit(EXIT_SUCCESS);
		}
	}
}

int		main(int ac, char **av, char **env)
{
	t_builtin b;

	if (ac != 1 || av[1])
		return (0);
	ft_bzero(&b, sizeof(b));
	loop_fork(ft_tab_strcpy(env), b);
	return (0);
}
