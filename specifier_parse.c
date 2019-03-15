/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:11:53 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/15 19:18:12 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*specifier_width(char *format, t_specifier *specifier, va_list arg)
{
	int				nbr;

	nbr = 0;
	if (*format == '*')
	{
		format++;
		nbr = va_arg(arg, int);
	}
	if (nbr < 0)
	{
		nbr *= -1;
		specifier->minus = 1;
	}
	while (*format >= '0' && *format <= '9')
		nbr = nbr * 10 + (*format++ - '0');
	specifier->width = nbr;
	return (format);
}

static char	*specifier_precision(char *format, t_specifier *specifier,
		va_list arg)
{
	unsigned int	nbr;

	nbr = 0;
	if (*format == '*')
	{
		format++;
		nbr = va_arg(arg, unsigned int);
	}
	while (*format >= '0' && *format <= '9')
		nbr = nbr * 10 + (*format++ - '0');
	specifier->precision = nbr;
	return (format);
}

static char	is_specifier_flags(char *format, t_specifier *specifier)
{
	if (*format == '#')
		specifier->sharp = 1;
	else if (*format == '0')
		specifier->null = 1;
	else if (*format == '-')
		specifier->minus = 1;
	else if (*format == '+')
		specifier->plus = 1;
	else if (*format == ' ')
		specifier->space = 1;
	else
		return (0);
	return (1);
}

char		*specifier_parse(char *format, t_specifier *specifier, va_list arg)
{
	while (is_specifier_flags(format, specifier))
		format++;
	format = specifier_width(format, specifier, arg);
	if (*format == '.')
	{
		specifier->dot = 1;
		format++;
		format = specifier_precision(format, specifier, arg);
	}
	format = specifier_size(format, specifier);
	format = specifier_type(format, specifier, arg);
	return (format);
}
