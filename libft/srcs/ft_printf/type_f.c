/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 20:27:45 by qdegraev          #+#    #+#             */
/*   Updated: 2016/02/22 10:46:32 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_f(t_arg *a)
{
	char *f;

	f = ft_dtoa_base(va_arg(a->ap, double), 10, a->p, a);
	a->ret = ft_strlen(f);
	ft_putstr(f);
}
