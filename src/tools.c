/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 15:50:26 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/17 19:24:53 by qdegraev         ###   ########.fr       */
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
	copy = (char**)malloc(sizeof(copy) * i - 1);
	while (j < i - 1)
	{
		if (j == line)
			k++;
		else
			copy[j] = ft_strdup(tab[j + k]);
		j++;
	}
	copy[j] = NULL;
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
	copy = (char**)malloc(sizeof(copy) * i + 1);
	while (j < i)
	{
		copy[j] = ft_strdup(tab[j]);
		j++;
	}
	copy[j++] = var;
	copy[j] = NULL;
	return (copy);
}
