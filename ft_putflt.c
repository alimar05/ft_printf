/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putflt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 11:24:59 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/22 17:14:00 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_putflt(va_list arg, t_specifier *specifier)
{
	int			i;
	int			ipart;
	double		dpart;

	specifier->num_flt_d.num = va_arg(arg, double);
	ipart = (int)specifier->num_flt_d.num;
	dpart = specifier->num_flt_d.num - (double)ipart;
	printf("%d\n", ipart);
	printf("%f\n", dpart);
	if (!specifier->dot)
		specifier->precision = 6;
	i = specifier->precision;
	while (i-- != 0)
		dpart *= 10;
	printf("%d\n", (int)dpart);
//	printf("%x\n", specifier->num_flt_d.parts.sign);
//	printf("%x\n", specifier->num_flt_d.parts.exponenta);
//	printf("%lx\n", specifier->num_flt_d.parts.mantissa);
}
