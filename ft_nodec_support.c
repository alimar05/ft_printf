/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodec_support.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 13:29:07 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/15 15:28:21 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_no_dec_minus(t_specifier *specifier, char *ptr, int *i)
{
	int		j;

	j = *i;
	if (!specifier->dot)
	{
		if (specifier->sharp && *ptr != '0')
			specifier->width -= specifier->view_size;
		if (specifier->sharp && *ptr != '0')
		{
			write(1, specifier->view, specifier->view_size);
			specifier->num_bytes += specifier->view_size;
		}
		write(1, ptr, *i);
		specifier->num_bytes += *i;
		while (j++ < specifier->width)
		{
			write(1, " ", 1);
			specifier->num_bytes++;
		}
	}
	else
	{
		if (*ptr == '0' && specifier->base == 8 && specifier->sharp && !specifier->precision)
			specifier->width--;
		if (specifier->sharp && *ptr != '0')
			specifier->width -= specifier->view_size;
		if (specifier->sharp && *ptr != '0')
		{
			write(1, specifier->view, specifier->view_size);
			specifier->num_bytes += specifier->view_size;
		}
		while (j++ < specifier->precision)
		{
			write(1, "0", 1);
			specifier->num_bytes++;
		}
		if (*ptr == '0' && specifier->base == 8 && specifier->sharp && !specifier->precision)
		{
			write(1, "0", 1);
			specifier->num_bytes++;
		}
		else if (*ptr == '0' && !specifier->precision && specifier->width)
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
		j = *i;
		if (j < specifier->precision)
			specifier->width -= specifier->precision - j;
		while (j++ < specifier->width)
		{
			write(1, " ", 1);
			specifier->num_bytes++;
		}
	}
}

void		print_no_dec_no_minus(t_specifier *specifier, char *ptr, int *i)
{
	int		j;

	j = *i;
	if (!specifier->null && !specifier->dot)
	{
		if (specifier->sharp && *ptr != '0')
			specifier->width -= specifier->view_size;
		while (j++ < specifier->width)
		{
			write(1, " ", 1);
			specifier->num_bytes++;
		}
		if (specifier->sharp && *ptr != '0')
		{
			write(1, specifier->view, specifier->view_size);
			specifier->num_bytes += specifier->view_size;
		}
		write(1, ptr, *i);
		specifier->num_bytes += *i;
	}
	else if (specifier->null && !specifier->dot)
	{
		if (specifier->sharp && *ptr != 0)
			specifier->width -= specifier->view_size;
		if (specifier->sharp && *ptr != '0')
		{
			write(1, specifier->view, specifier->view_size);
			specifier->num_bytes += specifier->view_size;
		}
		while (j++ < specifier->width)
		{
			write(1, "0", 1);
			specifier->num_bytes++;
		}
		write(1, ptr, *i);
		specifier->num_bytes += *i;
	}
	else if (specifier->dot)
	{
		if (*ptr == '0' && specifier->base == 8 && specifier->sharp && !specifier->precision)
			specifier->width--;
		if (specifier->sharp && *ptr != '0')
			specifier->width -= specifier->view_size;
		if (j < specifier->precision)
			specifier->width -= specifier->precision - j;
		while (j++ < specifier->width)
		{
			write(1, " ", 1);
			specifier->num_bytes++;
		}
		if (specifier->sharp && *ptr != '0')
		{
			write(1, specifier->view, specifier->view_size);
			specifier->num_bytes += specifier->view_size;
		}
		j = *i;
		while (j++ < specifier->precision)
		{
			write(1, "0", 1);
			specifier->num_bytes++;
		}
		if (*ptr == '0' && specifier->base == 8 && specifier->sharp && !specifier->precision)
		{
			write(1, "0", 1);
			specifier->num_bytes++;
		}
		else if (*ptr == '0' && !specifier->precision && specifier->width)
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
}
