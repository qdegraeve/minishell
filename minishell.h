/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/15 10:34:40 by qdegraev          #+#    #+#             */
/*   Updated: 2016/03/15 12:23:18 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "ft_printf/includes/ft_printf.h"

#include <unistd.h>

#define DEBUG ft_printf("\n--- file: %s; fonction: %s, line: [%d]\n", __FILE__, __FUNCTION__, __LINE__);

#endif
