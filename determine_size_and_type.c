/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determine_size_and_type.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 15:06:05 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/08 15:09:42 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*specifier_size(char *format, t_specifier *specifier)
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

char	*specifier_type(char *format, t_specifier *specifier, va_list arg)
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
	if (*format == 'u')
		ft_putuns(arg, specifier);
	if (*format == 'x')
		ft_puthex(arg, specifier);
	if (*format == 'X')
		ft_puthex_upcase(arg, specifier);
	return (format + 1);
}
