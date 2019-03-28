/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putflt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 11:24:59 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/28 13:24:48 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t		ft_pow(size_t num, size_t n)
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

char		*rounding_ipart(t_specifier *specifier, size_t ipart, double dpart)
{
	char		*ptr;
	double		round;
	char		buffer[21];

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

char		*rounding_dpart(t_specifier *specifier, double dpart)
{
	char		*ptr;
	double		round;
	char		buffer[21];

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

static void	print_minus(t_specifier *specifier, size_t ipart, double dpart,
		int null_count)
{
	int			len;

	if (!specifier->dot)
		specifier->precision = 6;
	if (specifier->precision)
		dpart *= ft_pow(10, specifier->precision);
	if (specifier->sign < 0)
	{
		write(1, "-", 1);
		specifier->width--;
		specifier->num_bytes++;
	}
	write(1, rounding_ipart(specifier, ipart, dpart), specifier->i);
	while (null_count--)
		write(1, "0", 1);
	if (specifier->precision || (specifier->dot && specifier->sharp))
	{
		write(1, ".", 1);
		specifier->width--;
		specifier->num_bytes++;
	}
	write(1, rounding_dpart(specifier, dpart), specifier->j);
	len = specifier->i + specifier->j;
	padding(specifier, specifier->width, ' ', &len);
}

static void	print_no_minus(t_specifier *specifier, size_t ipart, double dpart,
		int null_count)
{
	int			len;
	char		*ptr1;
	char		*ptr2;

	if (!specifier->dot)
		specifier->precision = 6;
	if (specifier->precision)
		dpart *= ft_pow(10, specifier->precision);
	ptr1 = rounding_ipart(specifier, ipart, dpart);
	ptr2 = rounding_dpart(specifier, dpart);
	len = specifier->i + specifier->j;
	if (specifier->null)
	{
		if (specifier->sign < 0)
		{
			write(1, "-", 1);
			specifier->width--;
			specifier->num_bytes++;
		}
		padding(specifier, specifier->width, '0', &len);
	}
	else
	{
		padding(specifier, specifier->width, ' ', &len);
		if (specifier->sign < 0)
		{
			write(1, "-", 1);
			specifier->width--;
			specifier->num_bytes++;
		}
	}
	write(1, ptr1, specifier->i);
	while (null_count--)
		write(1, "0", 1);
	if (specifier->precision || (specifier->dot && specifier->sharp))
	{
		write(1, ".", 1);
		specifier->width--;
		specifier->num_bytes++;
	}
	write(1, ptr2, specifier->j);
}

void		ft_putflt(va_list arg, t_specifier *specifier)
{
	size_t		ipart;
	double		dpart;
	int			null_count;

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
	specifier->width -= null_count;
	specifier->num_bytes += null_count;
	ipart = (size_t)(specifier->num_flt_d.num + 1e-2);
	dpart = specifier->num_flt_d.num - (double)ipart + 1;
	if (specifier->minus)
		print_minus(specifier, ipart, dpart, null_count);
	else
		print_no_minus(specifier, ipart, dpart, null_count);
}
