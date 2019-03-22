/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determine_size_and_type.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:06:05 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/21 11:23:35 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*setup_size(t_specifier *specifier, char *format)
{
	if (*format == *(format + 1))
	{
		specifier->size[0] = *format;
		specifier->size[1] = *format;
		return (format + 2);
	}
	else
	{
		specifier->size[0] = *format;
		return (format + 1);
	}
}

char		*specifier_size(char *format, t_specifier *specifier)
{
	if (*format == 'h' && *(format + 1) == 'h')
		return (setup_size(specifier, format));
	else if (*format == 'h')
		return (setup_size(specifier, format));
	else if (*format == 'l' && *(format + 1) == 'l')
		return (setup_size(specifier, format));
	else if (*format == 'l')
		return (setup_size(specifier, format));
	else if (*format == 'L')
		return (setup_size(specifier, format));
	return (format);
}

static char	*without_specifier(char *format, t_specifier *specifier)
{
	int		j;

	j = 0;
	if (*format == '%' && specifier->minus)
	{
		write(1, "%", 1);
		specifier->num_bytes++;
	}
	if (specifier->width)
	{
		if (specifier->null && !specifier->minus)
			padding(specifier, specifier->width - 1, '0', &j);
		else
			padding(specifier, specifier->width - 1, ' ', &j);
	}
	if (*format == '%' && !specifier->minus)
	{
		write(1, "%", 1);
		specifier->num_bytes++;
	}
	else
		return (format - 1);
	return (format);
}

char		*specifier_type(char *format, t_specifier *specifier, va_list arg)
{
	if (*format == '\0')
		return (format);
	else if (*format == 'c')
		ft_putchar(arg, specifier);
	else if (*format == 's')
		ft_putstr(arg, specifier);
	else if (*format == 'p')
		ft_putadr(arg, specifier);
	else if (*format == 'd' || *format == 'i')
		ft_putdec(arg, specifier);
	else if (*format == 'o')
		ft_putoct(arg, specifier);
	else if (*format == 'u')
		ft_putuns(arg, specifier);
	else if (*format == 'x')
		ft_puthex(arg, specifier);
	else if (*format == 'X')
		ft_puthex_upcase(arg, specifier);
	else if (*format == 'b')
		ft_putbin(arg, specifier);
	else if (*format == 'f')
		ft_putflt(arg, specifier);
	else
		format = without_specifier(format, specifier);
	return (format + 1);
}
