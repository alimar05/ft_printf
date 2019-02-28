/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   csp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 20:04:33 by rymuller          #+#    #+#             */
/*   Updated: 2019/02/27 13:45:10 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "ft_printf.h"

void	ft_putchar(va_list arg, t_specifier *specifier)
{
	int		c;

	c = va_arg(arg, int);
	if (specifier->minus)
	{
		write(1, &c, 1);
		specifier->num_bytes++;
		while (specifier->width > 1)
		{
			write(1, " ", 1);
			specifier->width--;
			specifier->num_bytes++;
		}
	}
	else if (!specifier->minus)
	{
		while (specifier->width > 1)
		{
			write(1, " ", 1);
			specifier->width--;
			specifier->num_bytes++;
		}
		write(1, &c, 1);
		specifier->num_bytes++;
	}
}

void	ft_putstr(va_list arg, t_specifier *specifier)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	str = va_arg(arg, char *);
	while (str[i])
		i++;
	if (specifier->dot && !specifier->precision)
		while (specifier->width--)
		{
			write(1, " ", 1);
			specifier->num_bytes++;
		}
	else if (specifier->minus)
	{
		if (specifier->dot && specifier->precision)
		{
			i = specifier->precision < i ? specifier->precision : i;
			write(1, str, i);
			specifier->num_bytes += i;
			while (i++ < specifier->width)
			{
				write(1, " ", 1);
				specifier->num_bytes++;
			}
		}
		else
		{
			write(1, str, i);
			specifier->num_bytes += i;
			while (i++ < specifier->width)
			{
				write(1, " ", 1);
				specifier->num_bytes++;
			}
		}
	}
	else if (!specifier->minus)
	{
		if (specifier->dot && specifier->precision)
		{
			i = specifier->precision < i ? specifier->precision : i;
			j = i;
			while (i++ < specifier->width)
			{
				write(1, " ", 1);
				specifier->num_bytes++;
			}
			write(1, str, j);
			specifier->num_bytes += j;
		}
		else
		{
			j = i;
			while (i++ < specifier->width)
			{
				write(1, " ", 1);
				specifier->num_bytes++;
			}
			write(1, str, j);
			specifier->num_bytes += j;
		}
	}
}

void	ft_putadr(va_list arg, t_specifier *specifier)
{
	int		i;
	int		j;
	size_t	num;
	char	*ptr;
	char	buffer[9];

	num = va_arg(arg, size_t);
	ptr = ft_itoa_base(num, 16, buffer);
	i = 0;
	while (*(ptr + i))
		i++;
	if (specifier->minus)
	{
		write(1, "0x", 2);
		write(1, ptr, i);
		specifier->num_bytes += i + 2;
		while (i++ < specifier->width - 2)
		{
			write(1, " ", 1);
			specifier->num_bytes++;
		}
	}
	else if (!specifier->minus)
	{
		j = i;
		if (specifier->null && !specifier->dot)
			write(1, "0x", 2);
		while (j++ < specifier->width - 2)
		{
			if (specifier->null && !specifier->dot)
				write(1, "0", 1);
			else
				write(1, " ", 1);
			specifier->num_bytes++;
		}
		if (!(specifier->null && !specifier->dot))
			write(1, "0x", 2);
		write(1, ptr, i);
		specifier->num_bytes += i + 2;
	}
}
