/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putflt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 11:24:59 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/28 20:34:38 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_minus(t_specifier *specifier, size_t ipart, double dpart,
		int null_count)
{
	int			len;
	__int128	idpart;
	char		buffer[21];

	idpart = 0;
	if (!specifier->dot)
		specifier->precision = 6;
	if (specifier->precision)
		idpart = dpart * ft_pow(10, specifier->precision);
	if (specifier->sign < 0)
	{
		write(1, "-", 1);
		specifier->width--;
		specifier->num_bytes++;
	}
	write(1, rounding_ipart(specifier, ipart, idpart, buffer), specifier->i);
	while (null_count--)
		write(1, "0", 1);
	if (specifier->precision || (specifier->dot && specifier->sharp))
	{
		write(1, ".", 1);
		specifier->width--;
		specifier->num_bytes++;
	}
	write(1, rounding_dpart(specifier, idpart, buffer), specifier->j);
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

static void	print_no_minus(t_specifier *specifier, size_t ipart, double dpart,
		int null_count)
{
	__int128	idpart;
	char		*ptr1;
	char		*ptr2;
	char		buffer1[21];
	char		buffer2[21];

	idpart = 0;
	if (!specifier->dot)
		specifier->precision = 6;
	if (specifier->precision)
		idpart = dpart * ft_pow(10, specifier->precision);
	ptr1 = rounding_ipart(specifier, ipart, idpart, buffer1);
	ptr2 = rounding_dpart(specifier, idpart, buffer2);
	if (specifier->precision || (specifier->dot && specifier->sharp))
		specifier->width--;
	if (specifier->sign < 0)
		specifier->width--;
	null_or_space_padding(specifier);
	write(1, ptr1, specifier->i);
	while (null_count--)
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
	if (specifier->minus)
		print_minus(specifier, ipart, dpart, null_count);
	else
		print_no_minus(specifier, ipart, dpart, null_count);
}
