/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:50:26 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/21 18:42:01 by qdegraev         ###   ########.fr       */
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

void	clear_tab(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

char	**ft_tab_remove(char **tab, int line)
{
	int		i;
	int		j;
	int		k;
	char	**copy;

	i = 0;
	j = 0;
	k = 0;
	while (tab[i])
		i++;
	copy = (char**)malloc(sizeof(copy) * i);
	while (j < i)
	{
		if (j != line)
			copy[k++] = tab[j];
		else
			ft_strdel(&(tab[j]));
		j++;
	}
	free(tab);
	copy[k] = NULL;
	return (copy);
}

char	**ft_tab_add(char **tab, char *var)
{
	int		i;
	int		j;
	char	**copy;

	i = 0;
	j = 0;
	while (tab[i])
		i++;
	copy = (char**)malloc(sizeof(*copy) * (i + 2));
	ft_bzero(copy, sizeof(copy));
	while (j < i)
	{
		copy[j] = tab[j];
		j++;
	}
	free(tab);
	copy[j++] = var;
	copy[j] = NULL;
	return (copy);
}
