/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 14:56:32 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/29 15:11:32 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char	*var, char **env)
{
	int i;
	int len;
	char *tmp;

	i = 0;
	tmp = ft_strjoin(var, "=");
	len = ft_strlen(tmp);
	while (env && env[i])
	{
		if (!ft_strncmp(tmp, env[i], len))
		{
			ft_strdel(&tmp);
			return (env[i] + len);
		}
		i++;
	}
	ft_strdel(&tmp);
	return (NULL);
}
