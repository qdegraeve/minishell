/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:41:00 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/15 20:31:45 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_tab_strcpy(char **to_copy)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	j = 0;
	while (to_copy[i])
		i++;
	copy = (char**)malloc(sizeof(copy) * i);
	while (j < i)
	{
		copy[j] = ft_strdup(to_copy[j]);
		j++;
	}
	copy[j] = NULL;
	return (copy);
}

char	*get_path(char *command, char **env)
{
	char	*path;
	char	**test;
	int		i;

	i = 0;
	while (env[i])
	{
		if (strstr(env[i], "PATH=") != NULL)
			break ;
		i++;
	}
	test = ft_strsplit(env[i] + 5, ':');
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

char	**get_argv()
{
	char *line;
	char **caca;

	line = NULL;
	ft_putstr_fd("ecris sale batard : > ", 1);
	get_next_line(0, &line);
	caca = ft_strsplit(line, ' ');
	if (line)
		ft_strdel(&line);
	return (caca);
}

void	loop_fork(char **env)
{
	pid_t	parent;
	char	**argv;
	char	*path;

	argv = NULL;
	while(42)
	{
		argv = get_argv();
		path = get_path(argv[0], env);
		parent = fork();
		if (parent > 0)
			wait(NULL);
		else if (parent == -1)
		{
			printf("father = %d\n", parent);
			exit(EXIT_FAILURE);
		}
		else if (parent == 0)
			execve(path, argv, env);
	}
}

int		main(int ac, char **av, char **env)
{
	loop_fork(ft_tab_strcpy(env));
	return (0);
}
