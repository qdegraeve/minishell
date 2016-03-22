/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:41:00 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/22 18:32:31 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	init_builtin(t_builtin *b)
{
	if (b->env_cpy)
	{
		clear_tab(b->env);
		b->env = b->env_cpy;
		b->env_cpy = NULL;
	}
	if (b->path)
		ft_strdel(&b->path);
	if (b->argv)
		clear_tab(b->argv);
	b->error = 0;
	b->argv = get_argv();
	b->env_i = 0;
	b->env_p = 0;
	b->env_u = 0;
	b->env_v = 0;
	b->path_e = -1;
	b->home = -1;
	b->pwd = -1;
	b->oldpwd = -1;
}

void	loop_fork(t_builtin b)
{
	pid_t	parent;
	char	*path;

	path = NULL;
	b.env_cpy = NULL;
	while(42)
	{
		init_builtin(&b);
		if (b.argv[0])
			get_command(b.argv[0], &b);
		parent = fork();
		if (parent > 0)
			wait(NULL);
		else if (parent == -1)
			exit(EXIT_FAILURE);
		else if (parent == 0)
		{
			if (b.path)
			{
					execve(b.path, b.argv, b.env);
			}
			exit(EXIT_SUCCESS);
		}
	}
}

int		main(int ac, char **av, char **env)
{
	t_builtin b;

	b.env = NULL;
	if (ac != 1 || av[1])
		return (0);
	ft_bzero(&b, sizeof(b));
	if (env[0])
	{
		DEBUG
		b.env = ft_tab_strcpy(env);
	}
	loop_fork(b);
	return (0);
}
