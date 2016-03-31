/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:41:00 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/31 14:46:19 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_builtin(t_builtin *b, char *command)
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
	b->env_i = 0;
	b->env_p = 0;
	b->env_u = 0;
	b->env_v = 0;
	b->path_e = -1;
	b->home = -1;
	b->error = 0;
	b->argv = get_argv(b, command);
}

void	sig_handler(int sig)
{
	if (sig == 2)
	{
		ft_putchar('\n');
		prompt(1);
	}
}

void	loop_fork(t_builtin b)
{
	int		i;

	i = 0;
	b.env_cpy = NULL;
	b.error = 0;
	while (42)
	{
		i = 0;
		b.commands = get_commands(&b);
		while (b.commands && b.commands[i])
		{
			init_builtin(&b, b.commands[i]);
			if (b.argv[0])
				get_command(b.argv[0], &b);
			if (b.path)
				do_fork(&b);
			i++;
		}
		if (b.commands)
			clear_tab(b.commands);
	}
}

void	sh_level(t_builtin *b)
{
	char	*level;
	char	*tmp;

	level = NULL;
	tmp = NULL;
	level = ft_getenv("SHLVL", b->env);
	if (level == NULL)
		tmp = ft_strdup("1");
	else
		tmp = ft_itoa(ft_atoi(level) + 1);
	set_env_one(b, ft_strjoin("SHLVL=", tmp), 6);
	ft_strdel(&tmp);
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
	sh_level(&b);
	signal(SIGINT, sig_handler);
	loop_fork(b);
	return (0);
}
