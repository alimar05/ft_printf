/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putflt_support.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 17:20:12 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/30 18:44:41 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		ft_pow(size_t num, size_t n)
{
	size_t		res;

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

char		*rounding_ipart(t_specifier *specifier, size_t ipart,
		long double dpart, char *buffer)
{
	char		*ptr;
	long double	round;

	round = dpart - ft_pow(10, specifier->precision);
	if (specifier->dot && !specifier->precision && (((ipart % 2)
					&& round == 0.5) || round > 0.5))
		ptr = ft_itoa_base_uns(specifier, ipart + 1, buffer);
	else
		ptr = ft_itoa_base_uns(specifier, ipart, buffer);
	STRLEN(ptr, specifier->i);
	specifier->num_bytes += specifier->i;
	return (ptr);
}

char		*rounding_dpart(t_specifier *specifier, long double dpart,
		char *buffer)
{
	char		*ptr;
	long double	round;

	round = dpart - ft_pow(10, specifier->precision);
	if (((size_t)round % 2 && round - (size_t)round == 0.5)
			|| round - (size_t)round > 0.5)
		ptr = ft_itoa_base_uns(specifier, dpart + 1, buffer);
	else
		ptr = ft_itoa_base_uns(specifier, dpart, buffer);
	ptr++;
	STRLEN(ptr, specifier->j);
	specifier->num_bytes += specifier->j;
	return (ptr);
}

char		is_special_cases(t_specifier *specifier, size_t mnt,
		unsigned int exp, unsigned int exponenta)
{
	if (exp == exponenta && (mnt == LONG_DOUBLE_MNT_INF
				|| mnt == DOUBLE_MNT_INF))
	{
		if (specifier->sign > 0)
		{
			write(1, "inf", 3);
			specifier->num_bytes += 3;
		}
		else if (specifier->sign < 0)
		{
			write(1, "-inf", 4);
			specifier->num_bytes += 4;
		}
		return (1);
	}
	else if (exp == exponenta)
	{
		write(1, "nan", 3);
		specifier->num_bytes += 3;
		return (1);
	}
	return (0);
}

void		ft_putflt_long(va_list arg, t_specifier *specifier, size_t *ipart,
		long double *dpart)
{
	specifier->num_flt_ld.num = va_arg(arg, long double);
	if (specifier->num_flt_ld.parts.sign)
	{
		specifier->sign = -1;
		specifier->num_flt_ld.parts.sign = 0;
	}
	if (is_special_cases(specifier, specifier->num_flt_ld.parts.mantissa,
				specifier->num_flt_ld.parts.exponenta, LONG_DOUBLE_EXP))
		return ;
	while (specifier->num_flt_ld.num > MAX_LONG_DOUBLE)
	{
		specifier->null_count++;
		specifier->num_flt_ld.num /= 10;
	}
	*ipart = (size_t)(specifier->num_flt_ld.num + 1e-2);
	*dpart = specifier->num_flt_ld.num - (long double)(*ipart) + 1;
}
