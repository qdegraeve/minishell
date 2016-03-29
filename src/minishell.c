/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:41:00 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/29 20:39:59 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	b->path = NULL;
	b->env_i = 0;
	b->env_p = 0;
	b->env_u = 0;
	b->env_v = 0;
	b->path_e = -1;
	b->home = -1;
	b->argv = get_argv(b);
	b->error = 0;
}

void	sig_handler(int sig)
{
	if (sig == 2)
	{
		ft_putendl("");
		prompt(1);
	}
}

void	loop_fork(t_builtin b)
{
	pid_t	parent;

	b.env_cpy = NULL;
	b.error = 0;
	while (42)
	{
		init_builtin(&b);
		if (b.argv[0])
			get_command(b.argv[0], &b);
		if (b.path)
		{
			parent = fork();
			if (parent > 0)
				wait(NULL);
			else if (parent == -1)
				exit(EXIT_FAILURE);
			else if (parent == 0)
			{
				if (execve(b.path, b.argv, b.env) == -1)
					b.error = 1;
			}
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
		b.env = ft_tab_strcpy(env);
	signal(SIGINT, sig_handler);
	loop_fork(b);
	return (0);
}
