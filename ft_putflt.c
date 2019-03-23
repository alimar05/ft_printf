/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putflt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 11:24:59 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/23 16:53:03 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	ft_pow(size_t num, size_t n)
{
	size_t	res;

	if (num == 1)
		return (1);
	res = 1;
	while (n)
	{
		if (n & 1)
			res *= num;
		num *= num;
		n >>= 1;
	}
	return (res);
}

void		ft_putflt(va_list arg, t_specifier *specifier)
{
	int			i;
	int			j;
	char		*ptr1;
	char		*ptr2;
	size_t		ipart;
	double		dpart;
	int			null_count;
	char		buffer1[21];
	char		buffer2[21];

	ptr1 = NULL;
	ptr2 = NULL;
	specifier->base = 10;
	specifier->num_flt_d.num = va_arg(arg, double);
	if (specifier->num_flt_d.parts.sign)
	{
		specifier->sign = -1;
		specifier->num_flt_d.parts.sign = 0;
	}
	null_count = 0;
	while (specifier->num_flt_d.num > 1e+17)
	{
		null_count++;
		specifier->num_flt_d.num /= 10;
	}
	specifier->num_bytes += null_count;
	ipart = (size_t)(specifier->num_flt_d.num + 1e-2);
	dpart = specifier->num_flt_d.num - (double)ipart + 1;
	ptr1 = ft_itoa_base_uns(specifier, ipart, buffer1);
	if (!specifier->dot)
		specifier->precision = 6;
	if (specifier->precision)
	   dpart *= ft_pow(10, specifier->precision);
	printf("%f\n", dpart);
	ptr2 = ft_itoa_base_uns(specifier, dpart + 1e-2, buffer2);
	STRLEN(ptr1, i);
	STRLEN(ptr2, j);
	if (specifier->sign < 0)
	{
		write(1, "-", 1);
		specifier->num_bytes++;
	}
	write(1, ptr1, i);
	while (null_count--)
		write(1, "0", 1);
	write(1, ".", 1);
	write(1, ptr2 + 1, j);
	specifier->num_bytes += i + j;
}
