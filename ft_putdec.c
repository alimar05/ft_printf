/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rymuller <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 15:18:49 by rymuller          #+#    #+#             */
/*   Updated: 2019/03/15 11:58:06 by rymuller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_minus(t_specifier *specifier, char *ptr, int *i)
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
	write(1, ptr, *i);
	specifier->num_bytes += *i;
	j = *i;
	while (j++ < specifier->width)
	{
		write(1, " ", 1);
		specifier->num_bytes++;
	}
}

static void	print_no_minus(t_specifier *specifier, char *ptr, int *i)
{
	int		j;

	j = *i;
	if (specifier->null && !specifier->dot && specifier->sign > 0)
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
		while (j++ < specifier->width)
		{
			write(1, "0", 1);
			specifier->num_bytes++;
		}
		write(1, ptr, *i);
		specifier->num_bytes += *i;
	}
	else if (!specifier->null && !specifier->dot && specifier->sign > 0)
	{
		if ((specifier->plus || specifier->space) && j < specifier->width)
			specifier->width--;
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
		write(1, ptr, *i);
		specifier->num_bytes += *i;
	}
	else if (specifier->null && !specifier->dot && specifier->sign < 0)
	{
		write(1, "-", 1);
		specifier->width--;
		specifier->num_bytes++;
		while (j++ < specifier->width)
		{
			write(1, "0", 1);
			specifier->num_bytes++;
		}
		write(1, ptr, *i);
		specifier->num_bytes += *i;
	}
	else if (!specifier->null && !specifier->dot && specifier->sign < 0)
	{
		specifier->width--;
		while (j++ < specifier->width)
		{
			write(1, " ", 1);
			specifier->num_bytes++;
		}
		write(1, "-", 1);
		specifier->num_bytes++;
		write(1, ptr, *i);
		specifier->num_bytes += *i;
	}
	else if (specifier->dot && specifier->sign > 0)
	{
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
	else if (specifier->dot && specifier->sign < 0)
	{
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
}

void		ft_putdec(va_list arg, t_specifier *specifier)
{
	int		i;
	char	*ptr;
	char	buffer[21];

	ptr = NULL;
	specifier->base = 10;
	if (specifier->size[0] == '\0' && specifier->size[1] == '\0')
		ptr = nul_and_nul_size(arg, specifier, buffer);
	else if (specifier->size[0] == 'h' && (specifier->size[1] == '\0'
				|| specifier->size[1] == 'h'))
		ptr = h_else_hh_size(arg, specifier, buffer);
	else if (specifier->size[0] == 'l' && (specifier->size[1] == '\0'
				|| specifier->size[1] == 'l'))
		ptr = l_else_ll_size(arg, specifier, buffer);
	STRLEN(ptr, i);
	if (specifier->minus)
		print_minus(specifier, ptr, &i);
	else
		print_no_minus(specifier, ptr, &i);
}
