/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 14:49:11 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/08 15:49:10 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_putchar(va_list arg, t_specifier *specifier)
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

static void	print_minus(t_specifier *specifier, char *str, int *i)
{
	if (specifier->dot && specifier->precision)
	{
		*i = specifier->precision < *i ? specifier->precision : *i;
		write(1, str, *i);
		specifier->num_bytes += *i;
		while ((*i)++ < specifier->width)
		{
			write(1, " ", 1);
			specifier->num_bytes++;
		}
	}
	else
	{
		write(1, str, *i);
		specifier->num_bytes += *i;
		while ((*i)++ < specifier->width)
		{
			write(1, " ", 1);
			specifier->num_bytes++;
		}
	}
}

static void	print_no_minus(t_specifier *specifier, char *str, int *i)
{
	int		j;

	if (specifier->dot && specifier->precision)
	{
		*i = specifier->precision < *i ? specifier->precision : *i;
		j = *i;
		while ((*i)++ < specifier->width)
		{
			if (specifier->null)
				write(1, "0", 1);
			else
				write(1, " ", 1);
			specifier->num_bytes++;
		}
		write(1, str, j);
		specifier->num_bytes += j;
	}
	else
	{
		j = *i;
		while ((*i)++ < specifier->width)
		{
			if (specifier->null)
				write(1, "0", 1);
			else
				write(1, " ", 1);
			specifier->num_bytes++;
		}
		write(1, str, j);
		specifier->num_bytes += j;
	}
}

void		ft_putstr(va_list arg, t_specifier *specifier)
{
	int		i;
	char	*str;

	str = va_arg(arg, char *);
	STRLEN(str, i);
	if (specifier->dot && !specifier->precision)
		while (specifier->width--)
		{
			write(1, " ", 1);
			specifier->num_bytes++;
		}
	else if (specifier->minus)
		print_minus(specifier, str, &i);
	else
		print_no_minus(specifier, str, &i);
}
