/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:34:40 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/16 16:15:23 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "ft_printf/include/ft_printf.h"

#include <unistd.h>
#include <sys/stat.h>

typedef struct	s_builtin
{
	char		*cd;
	char		*quit;
	char		*env;
	char		*setenv;
	char		*unsetenv;
	char		*exit;
	char		**envir;
	char		**argv;
	char		path;
	char		home;
	char		pwd;
}				t_builtin;

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
char			**ft_tab_strcpy(char **to_copy);

/*
**		exec_cd
*/
void			exec_cd(t_builtin *b);

#endif
