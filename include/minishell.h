/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:34:40 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/18 18:28:10 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../ft_printf/include/ft_printf.h"

#include <unistd.h>
#include <sys/stat.h>

typedef struct	s_builtin
{
	char		**env;
	char		**argv;
	int			path;
	int			home;
	int			pwd;
	int			oldpwd;
	char		error;
}				t_builtin;

typedef struct	s_commands
{
	char		*id;
	void		(*f)(t_builtin*);
}				t_commands;

/*
**		get_path
*/
char			*get_path(char *command, t_builtin *b);
char			*get_command(char *command, t_builtin *b);
void			get_env_index(t_builtin **b);

/*
**		minishell
*/
void			loop_fork(char **env, t_builtin b);

/*
**		tools
*/
char			**ft_tab_strcpy(char **to_copy);
void			clear_tab(char **tab);
char			**ft_tab_remove(char **tab, int line);
char			**ft_tab_add(char **tab, char *var);

/*
**		exec_cd
*/
void			exec_cd(t_builtin *b);


/*
**		env
*/
void	exec_env	(t_builtin *b);
void	exec_setenv(t_builtin *b);
void	exec_unsetenv(t_builtin *b);

#endif
