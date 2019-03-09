/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:11:53 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/09 18:09:14 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*specifier_width(char *format, t_specifier *specifier)
{
	unsigned int	nbr;

	nbr = 0;
	while (*format >= '0' && *format <= '9')
		nbr = nbr * 10 + (*format++ - '0');
	specifier->width = nbr;
	return (format);
}

static char	*specifier_precision(char *format, t_specifier *specifier)
{
	unsigned int	nbr;

	nbr = 0;
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
	format = specifier_width(format, specifier);
	if (*format == '.')
	{
		specifier->dot = 1;
		format++;
		format = specifier_precision(format, specifier);
	}
	format = specifier_size(format, specifier);
	format = specifier_type(format, specifier, arg);
	return (format);
}
