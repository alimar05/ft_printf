/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 16:46:02 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/01 15:55:45 by rymuller         ###   ########.fr       */
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

static char	*specifier_size(char *format, t_specifier *specifier)
{
	if (*format == 'h' && *(format + 1) == 'h')
	{
		specifier->size[0] = 'h';
		specifier->size[1] = 'h';
		return (format + 2);
	}
	else if (*format == 'h')
	{
		specifier->size[0] = 'h';
		return (format + 1);
	}
	else if (*format == 'l' && *(format + 1) == 'l')
	{
		specifier->size[0] = 'l';
		specifier->size[1] = 'l';
		return (format + 2);
	}
	else if (*format == 'l')
	{
		specifier->size[0] = 'l';
		return (format + 1);
	}
	else if (*format == 'L')
	{
		specifier->size[0] = 'L';
		return (format + 1);
	}
	return (format);
}

static char	*specifier_type(char *format, t_specifier *specifier, va_list arg)
{
	if (*format == 'c')
		ft_putchar(arg, specifier);
	if (*format == 's')
		ft_putstr(arg, specifier);
	if (*format == 'p')
		ft_putadr(arg, specifier);
	if (*format == 'd' || *format == 'i')
		ft_putdec(arg, specifier);
	if (*format == 'o')
		ft_putoct(arg, specifier);
	return (format + 1);
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
