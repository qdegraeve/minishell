/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:34:40 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/21 22:06:47 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/include/ft_printf.h"

#include <unistd.h>
#include <sys/stat.h>

typedef struct	s_builtin
{
	char		**env;
	char		**env_cpy;
	char		**argv;
	char		*path;
	int			path_e;
	int			home;
	int			pwd;
	int			oldpwd;
	char		error;
	char		env_i;
	char		env_p;
	char		env_v;
	char		env_u;
	char		env_or_cpy;
}				t_builtin;

typedef struct	s_commands
{
	char		*id;
	void		(*f)(t_builtin*);
}				t_commands;

/*
**		get_path
*/
void			get_path(char *command, t_builtin *b);
void			get_command(char *command, t_builtin *b);
void			get_env_index(t_builtin **b);

/*
**		minishell
*/
void			loop_fork(t_builtin b);

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
void	set_env_one(t_builtin *b, char *add, char **env, int j);
void	unset_env_one(char *remove, char ***env);
void	env_options(t_builtin *b, char *av);
void	exec_env	(t_builtin *b);
void	exec_setenv(t_builtin *b);
void	exec_unsetenv(t_builtin *b);

#endif
