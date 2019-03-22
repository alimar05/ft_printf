/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putflt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 11:24:59 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/22 14:35:46 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

void		ft_putflt(va_list arg, t_specifier *specifier)
{
	specifier->num_flt_d.num = va_arg(arg, double);
	if (!specifier->dot)
		specifier->precision = 6;
	printf("%x\n", specifier->num_flt_d.parts.sign);
	printf("%x\n", specifier->num_flt_d.parts.exponenta);
	printf("%lx\n", specifier->num_flt_d.parts.mantissa);
}
