/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putflt_support.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 17:20:12 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/29 20:02:32 by rymuller         ###   ########.fr       */
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

char		*rounding_ipart(t_specifier *specifier, size_t ipart, long double dpart,
		char *buffer)
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

char		is_special_cases(t_specifier *specifier, unsigned int mnt,
		unsigned int exp, unsigned int exponenta)
{
	if (exp == exponenta && !mnt && !specifier->num_flt_d.parts.sign)
	{
		write(1, "inf", 3);
		specifier->num_bytes += 3;
		return (1);
	}
	else if (exp == exponenta && !mnt && specifier->num_flt_d.parts.sign)
	{
		write(1, "-inf", 4);
		specifier->num_bytes += 4;
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

void		flt_plus_or_space(t_specifier *specifier)
{
	if (specifier->sign > 0)
	{
		if (specifier->plus)
		{
			write(1, "+", 1);
			specifier->width--;
			specifier->num_bytes++;
		}
		else if (specifier->space)
		{
			write(1, " ", 1);
			specifier->width--;
			specifier->num_bytes++;
		}
	}
}
