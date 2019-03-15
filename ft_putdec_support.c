/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdec_support.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 12:21:47 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/15 20:49:30 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	dec_minus_sign_plus_space_dot(t_specifier *specifier, int *i)
{
	int		j;

	j = *i;
	if (specifier->sign < 0)
	{
		write(1, "-", 1);
		specifier->width--;
		specifier->num_bytes++;
	}
	else if (specifier->plus)
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
	if (specifier->dot)
		while (j++ < specifier->precision)
		{
			write(1, "0", 1);
			specifier->width--;
			specifier->num_bytes++;
		}
}

void	dec_no_minus_null(t_specifier *specifier, char *ptr, int *i)
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
	padding(specifier, specifier->width, '0', i);
	write(1, ptr, *i);
	specifier->num_bytes += *i;
}

void	dec_no_minus(t_specifier *specifier, char *ptr, int *i)
{
	if ((specifier->plus || specifier->space) && *i < specifier->width)
		specifier->width--;
	padding(specifier, specifier->width, ' ', i);
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
	write(1, ptr, *i);
	specifier->num_bytes += *i;
}

void	dec_no_minus_null_sign(t_specifier *specifier, char *ptr, int *i)
{
	write(1, "-", 1);
	specifier->width--;
	specifier->num_bytes++;
	padding(specifier, specifier->width, '0', i);
	write(1, ptr, *i);
	specifier->num_bytes += *i;
}

void	dec_no_minus_sign(t_specifier *specifier, char *ptr, int *i)
{
	specifier->width--;
	padding(specifier, specifier->width, ' ', i);
	write(1, "-", 1);
	specifier->num_bytes++;
	write(1, ptr, *i);
	specifier->num_bytes += *i;
}
