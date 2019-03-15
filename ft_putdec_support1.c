/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdec_support1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:09:32 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/15 13:38:44 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	width_plus_space(t_specifier *specifier, int *i)
{
	int		j;

	j = *i;
	if ((specifier->plus || specifier->space) && j < specifier->width)
		specifier->width--;
	if (j < specifier->precision)
		specifier->width -= specifier->precision - j;
	j = *i;
	while (j++ < specifier->width)
	{
		write(1, " ", 1);
		specifier->num_bytes++;
	}
	if (specifier->plus)
	{
		write(1, "+", 1);
		specifier->num_bytes++;
	}
	else if (specifier->space)
	{
		write(1, " ", 1);
		specifier->num_bytes++;
	}
}

void		dec_no_minus_dot(t_specifier *specifier, char *ptr, int *i)
{
	int		j;

	width_plus_space(specifier, i);
	j = *i;
	while (j++ < specifier->precision)
	{
		write(1, "0", 1);
		specifier->num_bytes++;
	}
	if (*ptr == '0' && !specifier->precision && specifier->width)
	{
		write(1, " ", 1);
		specifier->num_bytes += *i;
	}
	else if (*ptr == '0' && !specifier->precision && !specifier->width)
		write(1, "", 0);
	else
	{
		write(1, ptr, *i);
		specifier->num_bytes += *i;
	}
}

void		dec_no_minus_dot_sign(t_specifier *specifier, char *ptr, int *i)
{
	int		j;

	j = *i;
	if (j < specifier->width)
		specifier->width--;
	if (j < specifier->precision)
		specifier->width -= specifier->precision - j;
	j = *i;
	while (j++ < specifier->width)
	{
		write(1, " ", 1);
		specifier->num_bytes++;
	}
	write(1, "-", 1);
	specifier->num_bytes++;
	j = *i;
	while (j++ < specifier->precision)
	{
		write(1, "0", 1);
		specifier->num_bytes++;
	}
	write(1, ptr, *i);
	specifier->num_bytes += *i;
}
