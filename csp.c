/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 20:04:33 by rymuller          #+#    #+#             */
/*   Updated: 2019/02/24 20:06:29 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(va_list arg, t_specifier *specifier)
{
	int		c;

	c = va_arg(arg, int);
	if (specifier->minus)
	{
		write(1, &c, 1);
		while (specifier->width > 1)
		{
			write(1, " ", 1);
			specifier->width--;
		}
	}
	if (!specifier->minus)
	{
		while (specifier->width > 1)
		{
			write(1, " ", 1);
			specifier->width--;
		}
		write(1, &c, 1);
	}
}

void	ft_putstr(va_list arg, t_specifier *specifier)
{
	unsigned int	i;
	unsigned int	j;
	char			*str;

	i = 0;
	str = va_arg(arg, char *);
	while (str[i])
		i++;
	if (specifier->dot && !specifier->precision)
		while (specifier->width--)
			write(1, " ", 1);
	else if (specifier->minus)
	{
		if (specifier->dot && specifier->precision)
		{
			i = specifier->precision < i ? specifier->precision : i;
			write(1, str, i);
			while (i++ < specifier->width)
				write(1, " ", 1);
		}
		else
		{
			write(1, str, i);
			while (i++ < specifier->width)
				write(1, " ", 1);
		}
	}
	else if (!specifier->minus)
	{
		if (specifier->dot && specifier->precision)
		{
			i = specifier->precision < i ? specifier->precision : i;
			j = i;
			while (i++ < specifier->width)
				write(1, " ", 1);
			write(1, str, j);
		}
		else
		{
			while (i++ < specifier->width)
				write(1, " ", 1);
			write(1, str, i);
		}
	}

}
