/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodec_support.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:29:07 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/17 16:34:18 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	minus_dot(t_specifier *specifier, char *ptr, int *i)
{
	int		j;

	if (*ptr == '0' && specifier->base == 8 && specifier->sharp
			&& !specifier->precision)
		specifier->width--;
	if (*ptr == '0' && specifier->type == 'p' && !specifier->precision)
		specifier->width++;
	if (specifier->sharp && *ptr != '0')
		specifier->width -= specifier->view_size;
	view(specifier, ptr);
	padding(specifier, specifier->precision, '0', i);
	null_value(specifier, ptr, i);
	j = *i;
	if (j < specifier->precision)
		specifier->width -= specifier->precision - j;
	padding(specifier, specifier->width, ' ', i);
}

static void	no_minus_dot(t_specifier *specifier, char *ptr, int *i)
{
	int		j;

	j = *i;
	if (*ptr == '0' && specifier->base == 8 && specifier->sharp
			&& !specifier->precision)
		specifier->width--;
	if (*ptr == '0' && specifier->type == 'p' && !specifier->precision)
		specifier->width++;
	if (specifier->sharp && *ptr != '0')
		specifier->width -= specifier->view_size;
	if (j < specifier->precision)
		specifier->width -= specifier->precision - j;
	padding(specifier, specifier->width, ' ', i);
	view(specifier, ptr);
	padding(specifier, specifier->precision, '0', i);
	null_value(specifier, ptr, i);
}

void		print_no_dec_minus(t_specifier *specifier, char *ptr, int *i)
{
	if (!specifier->dot)
	{
		if (specifier->sharp && *ptr != '0')
			specifier->width -= specifier->view_size;
		view(specifier, ptr);
		write(1, ptr, *i);
		specifier->num_bytes += *i;
		padding(specifier, specifier->width, ' ', i);
	}
	else
		minus_dot(specifier, ptr, i);
}

void		print_no_dec_no_minus(t_specifier *specifier, char *ptr, int *i)
{
	if (!specifier->null && !specifier->dot)
	{
		if (specifier->sharp && *ptr != '0')
			specifier->width -= specifier->view_size;
		padding(specifier, specifier->width, ' ', i);
		view(specifier, ptr);
		write(1, ptr, *i);
		specifier->num_bytes += *i;
	}
	else if (specifier->null && !specifier->dot)
	{
		if (specifier->sharp && *ptr != '0')
			specifier->width -= specifier->view_size;
		view(specifier, ptr);
		padding(specifier, specifier->width, '0', i);
		write(1, ptr, *i);
		specifier->num_bytes += *i;
	}
	else if (specifier->dot)
		no_minus_dot(specifier, ptr, i);
}
