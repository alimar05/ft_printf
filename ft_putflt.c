/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putflt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 11:24:59 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/29 20:04:16 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_minus(t_specifier *specifier, size_t ipart, double dpart)
{
	int			len;
	char		buffer[21];

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
	write(1, rounding_ipart(specifier, ipart, dpart, buffer), specifier->i);
	while (specifier->null_count--)
		write(1, "0", 1);
	if (specifier->precision || (specifier->dot && specifier->sharp))
	{
		write(1, ".", 1);
		specifier->width--;
		specifier->num_bytes++;
	}
	write(1, rounding_dpart(specifier, dpart, buffer), specifier->j);
	len = specifier->i + specifier->j;
	padding(specifier, specifier->width, ' ', &len);
}

static void	null_or_space_padding(t_specifier *specifier)
{
	int			len;

	len = specifier->i + specifier->j;
	if (specifier->null)
	{
		if (specifier->sign < 0)
		{
			write(1, "-", 1);
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
}

static void	print_no_minus(t_specifier *specifier, size_t ipart, long double dpart)
{
	char		*ptr1;
	char		*ptr2;
	char		buffer1[21];
	char		buffer2[21];

	if (!specifier->dot)
		specifier->precision = 6;
	if (specifier->precision)
		dpart *= ft_pow(10, specifier->precision);
	ptr1 = rounding_ipart(specifier, ipart, dpart, buffer1);
	ptr2 = rounding_dpart(specifier, dpart, buffer2);
	if (specifier->precision || (specifier->dot && specifier->sharp))
		specifier->width--;
	if (specifier->sign < 0)
		specifier->width--;
	null_or_space_padding(specifier);
	write(1, ptr1, specifier->i);
	while (specifier->null_count--)
		write(1, "0", 1);
	if (specifier->precision || (specifier->dot && specifier->sharp))
	{
		write(1, ".", 1);
		specifier->num_bytes++;
	}
	write(1, ptr2, specifier->j);
}

void		ft_putflt(va_list arg, t_specifier *specifier)
{
	size_t		ipart;
	long double	dpart;

	specifier->base = 10;
	specifier->null_count = 0;
	if (specifier->size[0] == 'L' && specifier->size[1] == '\0')
	{
		specifier->num_flt_ld.num = va_arg(arg, long double);
		if (is_special_cases(specifier, specifier->num_flt_ld.parts.mantissa,
					specifier->num_flt_ld.parts.exponenta, MAX_LONG_DOUBLE_EXP))
			return ;
		if (specifier->num_flt_ld.parts.sign)
		{
			specifier->sign = -1;
			specifier->num_flt_ld.parts.sign = 0;
		}
		while (specifier->num_flt_ld.num > MAX_LONG_DOUBLE)
		{
			specifier->null_count++;
			specifier->num_flt_ld.num /= 10;
		}
		ipart = (size_t)(specifier->num_flt_ld.num + 1e-2);
		dpart = specifier->num_flt_ld.num - (long double)ipart + 1;
	}
	else
	{
		specifier->num_flt_d.num = va_arg(arg, double);
		if (is_special_cases(specifier, specifier->num_flt_d.parts.mantissa,
					specifier->num_flt_d.parts.exponenta, MAX_DOUBLE_EXP))
			return ;
		if (specifier->num_flt_d.parts.sign)
		{
			specifier->sign = -1;
			specifier->num_flt_d.parts.sign = 0;
		}
		while (specifier->num_flt_d.num > MAX_DOUBLE)
		{
			specifier->null_count++;
			specifier->num_flt_d.num /= 10;
		}
		ipart = (size_t)(specifier->num_flt_d.num + 1e-2);
		dpart = specifier->num_flt_d.num - (long double)ipart + 1;
	}
	flt_plus_or_space(specifier);
	specifier->width -= specifier->null_count;
	specifier->num_bytes += specifier->null_count;
	if (specifier->minus)
		print_minus(specifier, ipart, dpart);
	else
		print_no_minus(specifier, ipart, dpart);
}
